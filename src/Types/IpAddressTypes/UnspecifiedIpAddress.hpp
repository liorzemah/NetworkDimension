#ifndef UNSPECIFIEDIPADDRESS_H
#define UNSPECIFIEDIPADDRESS_H

#include "IpAddress.hpp"

/* Implementation of Null-Object design pattern */	
class UnspecifiedIpAddress : public IpAddress
{
public:
	UnspecifiedIpAddress() : IpAddress(IpAddressType::UNSPECIFIED, 0){}
	~UnspecifiedIpAddress()=default;
	std::string toString() const noexcept override { return {};/*"Unspecified ip address!!";*/ }
};

#endif