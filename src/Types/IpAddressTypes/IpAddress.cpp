#include "IpAddress.hpp"  
#include "Ipv4Address.hpp"  
#include "Ipv6Address.hpp"  
#include "UnspecifiedIpAddress.hpp" 

std::shared_ptr<IpAddress> IpAddress::makeIpFromType(IpAddressType type) 
{
    if (type == IpAddressType::IP4)
        return std::make_shared<Ipv4Address>();
    if (type == IpAddressType::IP6)
        return std::make_shared<Ipv6Address>();
    return std::make_shared<UnspecifiedIpAddress>();
}

std::shared_ptr<IpAddress> IpAddress::makeIpFromString(const std::string& ipAddressAsString) 
{
    if (Ipv4Address::isValid(ipAddressAsString))
        return std::make_shared<Ipv4Address>(ipAddressAsString);
    if (Ipv6Address::isValid(ipAddressAsString))
        return std::make_shared<Ipv6Address>(ipAddressAsString);
    return std::make_shared<UnspecifiedIpAddress>();
}

IpAddress& IpAddress::operator=(const IpAddress& other) noexcept
{
    std::cout << "ip op = used" << std::endl;
    if (this == &other)
        return *this;

    BytesStream::operator=(other);
    this->_type = other._type;
    return *this;
}
