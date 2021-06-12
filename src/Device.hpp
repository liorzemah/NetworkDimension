#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <experimental/filesystem>
#include "DeviceAddress.hpp"
#include "Packet.hpp"
#include "DataLink.hpp"
#include "Types/MacAddress.hpp"


class Device : public Printable,
               public IEmpty<Device>            
{
private:
    constexpr static bool PROMISCUOUS_MODE = true;          /* Capture all traffic on the wire */
    constexpr static bool NON_PROMISCUOUS_MODE = false;     /* Capture only traffic that is directly related to the device. 
                                                               Only traffic to, from, or routed through the device will be picked up. */
    constexpr static int NON_TIMEOUT = -1;                  /* open device for capturing to unlimited time */
    constexpr static int ANY_TRAFFIC = -1;                  /* for capture all the traffic pass through the device */

    std::string _name;                                      /* name of device */
    std::string _description;                               /* textual description of interface, or empty string */
    MacAddress _macAddress;                                 /* device mac address */
    std::vector<DeviceAddress> _deviceAddresses;            /* List of device addresses */
    bool _isLoopback = false;
    bool _isUp = false;
    bool _isRunning = false;
    pcap_t* _capturingDescriptor = nullptr;
    DataLink _datalink;
    std::queue<std::shared_ptr<Packet>> _packetsPool;                         /* Captured packets pool, store captured packets */

public:
    explicit Device(struct pcap_if pcapDevice);
    Device()= default;
    virtual ~Device();
    std::string getName() const;
    std::string getDescription() const;
    MacAddress getMacAddress() const;
    const std::vector<DeviceAddress> &getDeviceAddresses() const;
    bool isLoopback() const;
    bool isUp() const;
    bool isRunning() const;
    bool operator==(const Device& other) const;
    std::string toString() const noexcept override;
    void open(bool promiscuous_mode = PROMISCUOUS_MODE, int timeout = NON_TIMEOUT); /* open device for live capturing */
    void close();
    void stopCapture();
    void startCapture(int numOfPackets = ANY_TRAFFIC);
    static void packetProcess(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer);
    std::shared_ptr<Packet> popPacket() noexcept;

private:
    std::string getWholeFileContent(const std::experimental::filesystem::path& filePath);
    void readMacAddress(const std::string& name); /* Read MacAddress string from device system file and convert and fill _macAddress */
};

#endif //DEVICE_HPP
