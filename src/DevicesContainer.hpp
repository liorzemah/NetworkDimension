#ifndef DEVICESMANAGER_DEVICESCONTAINER_HPP
#define DEVICESMANAGER_DEVICESCONTAINER_HPP

#include <vector>
#include <unordered_map>
#include "Device.hpp"

enum filter 
{ 
    FALSE = 0,
    TRUE  = 1,
    ANY   = 2
};

/*
    Create container of devices
    Class implement Singlethon Desing Pattern
    This container wraps std::vector
*/
class DevicesContainer final{
private:

    std::string _lastUpdateTime;
    std::vector<Device> _devices;                                                   /* hold all devices in vector */
    filter _loopbackFilter = ANY, _upFilter = ANY, _runningFilter = ANY;
    std::unordered_map<std::string ,Device> _mapDevicesByName;
    std::unordered_map<MacAddress ,Device, MacAddress::Hash> _mapDevicesByMac;
    std::unordered_map<std::shared_ptr<IpAddress> ,Device, IpAddress::HashForSharedPtr, IpAddress::EqualForSharePtr> _mapDevicesByIp;

    explicit DevicesContainer(filter loopback = ANY, filter up = ANY, filter running = ANY); 

public:

    static DevicesContainer& instance(filter loopback = ANY, filter up = ANY, filter running = ANY);
    void updateList();
    void setFlags(filter loopback = ANY, filter up = ANY, filter running = ANY);
    const Device &operator[] (uint64_t); /* Overloading [] operator to access elements in array style */
    auto const getSize() { return _devices.size(); };
    const std::string getLastUpdateTime() { return _lastUpdateTime; } 
    const Device& getDeviceByName(const std::string&) const;
    const Device& getDeviceByMac(const std::string&) const;
    const Device& getDeviceByMac(const MacAddress&) const;
    const Device& getDeviceByIp(const std::string&) const;
    const Device& getDeviceByIp(const std::shared_ptr<IpAddress>&) const;

    std::vector<Device>::iterator begin() { return _devices.begin(); }
    std::vector<Device>::iterator end()   { return _devices.end(); }  
    std::vector<Device>::const_iterator cbegin() const { return _devices.cbegin(); }
    std::vector<Device>::const_iterator cend()   const { return _devices.cend(); } 
};
#endif
