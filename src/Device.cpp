#include <fstream> /* for open file and read his content */
#include <exception>
#include "Device.hpp"

Device::Device(struct pcap_if device) {
    _name = std::string(device.name);

    if (device.description != nullptr)
        _description = std::string(device.description);

    _isLoopback =   (device.flags & PCAP_IF_LOOPBACK)   != 0;
    _isUp =         (device.flags & PCAP_IF_UP)         != 0;
    _isRunning =    (device.flags & PCAP_IF_RUNNING)    != 0;

    /* Get mac address */
    readMacAddress(_name);

    /* Get IP Addresses */
    auto address = device.addresses;
    while(address != nullptr)
    {
        _deviceAddresses.emplace_back(*address);
        address = address->next;
    }
}

Device::~Device()
{
    close(); /* safe destroy for _captureDescriptor */
}

std::string Device::getName() const {
    return _name;
}

std::string Device::getDescription() const {
    return _description;
}

MacAddress Device::getMacAddress() const {
    return _macAddress;
}

const std::vector<DeviceAddress> &Device::getDeviceAddresses() const {
    return _deviceAddresses;
}

bool Device::isLoopback() const {
    return _isLoopback;
}

bool Device::isUp() const {
    return _isUp;
}

bool Device::isRunning() const {
    return _isRunning;
}

bool Device::operator==(const Device &other) const {
    return _name == other._name && _macAddress == other._macAddress && _description == other._description;
}

std::string Device::toString() const noexcept{
    std::stringstream stringstream;

    stringstream << "Device properties:" << std::endl << "Name: " << _name << std::endl;

    if (!_description.empty())
        stringstream << "Description: " << _description << std::endl;

    if (!_macAddress.isEmpty())
        stringstream << "Mac address: " << _macAddress.toString() << std::endl;

    for (const auto& deviceAddress : _deviceAddresses)
    {
        if (!deviceAddress.isEmpty())
            stringstream << deviceAddress.toString() << std::endl;
    }

    if (_isLoopback)
        stringstream << "Link is Loopback" << std::endl;

    if (_isUp)
        stringstream << "Link is up" << std::endl;
    else
        stringstream << "Link is down" << std::endl;

    if (_isRunning)
        stringstream << "Link is running" << std::endl;
    else
        stringstream << "Link is not running" << std::endl;

    stringstream << _datalink.toString();

    return stringstream.str();
}

void Device::open(bool promiscuous_mode, int timeout) {
    if (isEmpty())
        throw std::invalid_argument("Device not initialized!!");

    char errbuf[PCAP_ERRBUF_SIZE];
    /* open device for reading */
    _capturingDescriptor = pcap_open_live(_name.c_str(),BUFSIZ, promiscuous_mode, timeout, errbuf);
    if(!_capturingDescriptor)
    { 
        throw std::runtime_error(errbuf);
    }
    _datalink = DataLink(_capturingDescriptor);
}

void Device::close()
{
    if(_capturingDescriptor){
        pcap_close(_capturingDescriptor);
        _capturingDescriptor = nullptr;
    }
}

/* callback function that is passed to pcap_loop(..) and called each time 
 * a packet is recieved */
void Device::packetProcess(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer) 
{
    if (args == NULL)
    {
        throw std::invalid_argument("missing arguments");
    }
    try
    {
        Device* device = reinterpret_cast<Device*>(args);
        device->_packetsPool.emplace(std::make_shared<Packet>(header, buffer));
    }
    catch(std::exception &e)
    {
        std::cerr << "error:" << e.what() << std::endl;
    }
}

std::shared_ptr<Packet> Device::popPacket() noexcept
{
    if (_packetsPool.empty())
        return nullptr; 

    std::shared_ptr<Packet> packet = _packetsPool.front();
    _packetsPool.pop();
    return packet;
}

void Device::startCapture(int numOfPackets){
    /* allright here we call pcap_loop(..) and pass in our callback function */
    /* int pcap_loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user)*/
    /* If you are wondering what the user argument is all about, so am I!!   */
    if (_capturingDescriptor)
        pcap_loop(_capturingDescriptor, numOfPackets, packetProcess, reinterpret_cast<u_char*>(this));
}

void Device::stopCapture(){
    if (_capturingDescriptor)
        pcap_breakloop(_capturingDescriptor);
}

std::string Device::getWholeFileContent(const std::experimental::filesystem::path& filePath) {
    // Open the stream to 'lock' the file.
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Can't open file " << filePath << std::endl;
        return {};
    }
    
    // Obtain the size of the file.
    const auto fileSize = std::experimental::filesystem::file_size(filePath);

    // Create a buffer.
    std::string buffer(fileSize, '\0');
    // Read the whole file into the buffer.
    file.read(&buffer[0], fileSize+1);
    //Remove tail of '\0' 
    buffer = buffer.substr(0,buffer.find('\0')); 
    return buffer;
}

void Device::readMacAddress(const std::string& name)
{
    std::experimental::filesystem::path deviceMacAddressFilePath = "/sys/class/net/";
    deviceMacAddressFilePath += name;
    deviceMacAddressFilePath += "/address";
    std::string macAddressAsString = getWholeFileContent(deviceMacAddressFilePath);
    macAddressAsString = macAddressAsString.substr(0, macAddressAsString.size()-1); /* remove last character (unwanted '\n') */
    
    /* Convert string to MacAddress */
    try
    {
        _macAddress = MacAddress(macAddressAsString);
    } 
    catch(std::invalid_argument::exception& e)
    {
        _macAddress = MacAddress::empty();
        std::cerr << e.what() << std::endl;
    }
}