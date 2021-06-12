#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include "DeviceAddress.hpp"
#include "Types/IpAddressTypes/Ipv4Address.hpp"
#include "Types/IpAddressTypes/Ipv6Address.hpp"
#include "Types/IpAddressTypes/UnspecifiedIpAddress.hpp"


std::shared_ptr<IpAddress> DeviceAddress::getSockAddr(struct sockaddr *sockAddr) {
    if (sockAddr == nullptr)
        return std::make_shared<UnspecifiedIpAddress>();

    switch (sockAddr->sa_family) {
        case AF_INET: {
            auto addr_in = reinterpret_cast<struct sockaddr_in*> (sockAddr);
            return std::make_shared<Ipv4Address>(addr_in->sin_addr.s_addr);
        }
        case AF_INET6: {
            auto addr_in6 = reinterpret_cast<struct sockaddr_in6 *> (sockAddr);
            return std::make_shared<Ipv6Address>(addr_in6->sin6_addr.__in6_u.__u6_addr8);
        }
        default:
            return std::make_shared<UnspecifiedIpAddress>();
    }
}

std::string DeviceAddress::toString() const noexcept {
    if (isEmpty())
        return {};

    std::stringstream stringstream;

    if (_ip->getType() == IpAddressType::IP4)
        stringstream << "Inet address: ";
    else if (_ip->getType() == IpAddressType::IP6)
        stringstream << "Inet6 address: ";
    else
        return "Device Address not specified!!";

    if (!ipIsEmpty())
        stringstream << _ip->toString() << " ";
    if (!broadcastIsEmpty())
        stringstream << "Broadcast: " << _broadcast->toString() << " ";
    if (!subnetmaskIsEmpty())
        stringstream << "Mask: " << _subnetmask->toString() << " ";
    if (!destinationIsEmpty())
        stringstream <<"Destination: " << _destination->toString() << " ";
    return stringstream.str();
}

DeviceAddress::DeviceAddress(struct pcap_addr address) : _ip(getSockAddr(address.addr)),
                                                         _subnetmask(getSockAddr(address.netmask)),
                                                         _broadcast(getSockAddr(address.broadaddr)), 
                                                         _destination(getSockAddr(address.dstaddr)) 
{}

DeviceAddress::DeviceAddress(std::string ip, std::string subnetmask, std::string broadcast, std::string destination) : 
        _ip(IpAddress::makeIpFromString(ip)), 
        _subnetmask(IpAddress::makeIpFromString(subnetmask)), 
        _broadcast(IpAddress::makeIpFromString(broadcast)), 
        _destination(IpAddress::makeIpFromString(destination))
{}

