#ifndef DEVICESMANAGER_DEVICEADDRESS_H
#define DEVICESMANAGER_DEVICEADDRESS_H

#include <string>
#include <pcap.h>
#include <memory>
#include "Types/IpAddressTypes/IpAddress.hpp"

class DeviceAddress : public Printable {
private:
    std::shared_ptr<IpAddress> _ip;
    std::shared_ptr<IpAddress> _subnetmask;
    std::shared_ptr<IpAddress> _broadcast;
    std::shared_ptr<IpAddress> _destination;

    std::shared_ptr<IpAddress> getSockAddr(struct sockaddr *sockAddr); /* Casting address from sockaddr structure to IpAddress */

public:
    explicit DeviceAddress(struct pcap_addr address);
    DeviceAddress(std::string ip, std::string subnetmask, std::string broadcast, std::string destination);
    bool ipIsEmpty() const noexcept { return !_ip->isSpecified(); }
    bool subnetmaskIsEmpty() const noexcept { return !_subnetmask->isSpecified(); }
    bool broadcastIsEmpty() const noexcept { return !_broadcast->isSpecified(); }
    bool destinationIsEmpty() const noexcept { return !_destination->isSpecified(); }
    bool isEmpty() const noexcept { return !(_ip->isSpecified() || _subnetmask->isSpecified() || _broadcast->isSpecified() || _destination->isSpecified()); }
    const std::shared_ptr<IpAddress> getIp() const noexcept { return _ip; }
    const std::shared_ptr<IpAddress> getSubnetmask() const noexcept { return _subnetmask; }
    const std::shared_ptr<IpAddress> getBroadcast() const noexcept { return _broadcast; }
    const std::shared_ptr<IpAddress> getDestination() const noexcept { return _destination; };
    virtual std::string toString() const noexcept;
};


#endif //DEVICESMANAGER_DEVICEADDRESS_H
