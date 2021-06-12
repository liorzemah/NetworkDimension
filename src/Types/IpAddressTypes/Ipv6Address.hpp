#ifndef IPV6ADDRESS_H
#define IPV6ADDRESS_H
	
#include <string>
#include <iostream>
#include "Types/BytesStream.hpp"
#include "Printable.hpp"
#include "Interfaces/IValidExpression.hpp"
#include "Interfaces/IEmpty.hpp"
#include "IpAddress.hpp"

class Ipv6Address : public IpAddress,
					public IValidExpression<Ipv6Address, std::string>,
					public IEmpty<Ipv6Address> 
{
private:
	constexpr static uint8_t IPV6_ADDRESS_SIZE = 16;

public:
	Ipv6Address() : IpAddress(IpAddressType::IP6, IPV6_ADDRESS_SIZE){}
	Ipv6Address(const BytesStream& other) : IpAddress(other){}
	Ipv6Address(uint8_t stream[]);
	Ipv6Address(const std::string& ipv6AddressAsString);
	virtual ~Ipv6Address()=default;
	std::string toString() const noexcept override;
	static bool isValid(const std::string& ipv6AddressAsString);
	Ipv6Address& operator=(const Ipv6Address& other) noexcept;
};

#endif