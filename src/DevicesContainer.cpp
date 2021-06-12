#include <time.h>
#include "DevicesContainer.hpp"
#include "DeviceAddress.hpp"

DevicesContainer::DevicesContainer(filter loopback, filter up, filter running) : _loopbackFilter(loopback), _upFilter(up), _runningFilter(running){
    updateList();
}

DevicesContainer& DevicesContainer::instance(filter loopback, filter up, filter running) 
{
    static DevicesContainer _instance;
    _instance.setFlags(loopback,up,running);
    return _instance;
}

void DevicesContainer::updateList() 
{
    char errorBuffer[PCAP_ERRBUF_SIZE];
    pcap_if_t *devicesList;
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    _lastUpdateTime = std::string(asctime(timeinfo));
    std::cout << "Update time: " <<_lastUpdateTime << std::endl;

    if (pcap_findalldevs(&devicesList, errorBuffer) != 0) 
    {
        std::cout << "Error finding _devices: " << std::string(errorBuffer) << std::endl;
        return;
    }
    while (devicesList != nullptr) 
    {
        Device device(*devicesList);
        if ((_loopbackFilter == ANY ||
            (_loopbackFilter == FALSE && !device.isLoopback()) ||
            (_loopbackFilter == TRUE && device.isLoopback())) &&
            (_upFilter == ANY ||
            (_upFilter == FALSE && !device.isUp()) ||
            (_upFilter == TRUE && device.isUp())) &&
            (_runningFilter == ANY ||
            (_runningFilter == FALSE && !device.isRunning()) ||
            (_runningFilter == TRUE && device.isRunning()))) 
        {
            _devices.push_back(device);
            _mapDevicesByName[device.getName()] = device;
            _mapDevicesByMac[device.getMacAddress()] = device;
            for (auto& deviceAddress : device.getDeviceAddresses())
            {
                if (!deviceAddress.ipIsEmpty()){
                    _mapDevicesByIp[deviceAddress.getIp()] = device;
                }
            }
        }
        devicesList = devicesList->next;
    }
}

void DevicesContainer::setFlags(filter loopback, filter up, filter running) {
    _loopbackFilter = loopback;
    _upFilter = up;
    _runningFilter = running;
}

const Device &DevicesContainer::operator[](uint64_t index) {
    if (!(index < _devices.size() && index >= 0))
    {
        std::cerr << "Device index out of bound, exiting" << std::endl;
        throw std::out_of_range("Device index out of bound, exiting");
    }
    return _devices[index];
}

const Device& DevicesContainer::getDeviceByName(const std::string &name) const {
    
    if (_mapDevicesByName.find(name) == _mapDevicesByName.end()) {
        // The given name is not of any device
        return Device::empty();
    }
    return _mapDevicesByName.at(name);
}

const Device& DevicesContainer::getDeviceByMac(const std::string &mac) const {
    try
    {
        MacAddress macKey(mac);
        if (_mapDevicesByMac.find(macKey) == _mapDevicesByMac.end()) 
        {
            // The given mac address is not of any device
            return Device::empty();
        }

        return _mapDevicesByMac.at(macKey);
    }
    catch(const std::invalid_argument& e)
    {
        // Invalid mac address
        return Device::empty();
    }
}

const Device& DevicesContainer::getDeviceByMac(const MacAddress& macKey) const
{
    if (_mapDevicesByMac.find(macKey) == _mapDevicesByMac.end()) 
    {
        // The given mac address is not of any device
        return Device::empty();
    }

    return _mapDevicesByMac.at(macKey);
}

const Device& DevicesContainer::getDeviceByIp(const std::string &ip) const {
    try
    {
        std::shared_ptr<IpAddress> ipKey = IpAddress::makeIpFromString(ip);
        if (_mapDevicesByIp.find(ipKey) == _mapDevicesByIp.end()) {
            // The given ip is not of any device
            return Device::empty();
        }
        return _mapDevicesByIp.at(ipKey);
    }
    catch(const std::invalid_argument& e)
    {
        // Invalid ip address
        return Device::empty();
    }
}

const Device& DevicesContainer::getDeviceByIp(const std::shared_ptr<IpAddress>& ipKey) const
{
    if (_mapDevicesByIp.find(ipKey) == _mapDevicesByIp.end()) {
        // The given ip is not of any device
        return Device::empty();
    }
    return _mapDevicesByIp.at(ipKey);    
}


