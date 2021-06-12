#ifndef IPV4ADDRESS_H
#define IPV4ADDRESS_H

#include <string>
#include <iostream>
#include "Types/BytesStream.hpp"
#include "Printable.hpp"
#include "Interfaces/IValidExpression.hpp"
#include "Interfaces/IEmpty.hpp"
#include "MachineEndianness.hpp"
#include "IpAddress.hpp"
	
class Ipv4Address : public IpAddress,
					public IValidExpression<Ipv4Address, std::string>,
					public IEmpty<Ipv4Address>
{
private:
	constexpr static uint8_t IPV4_ADDRESS_SIZE = 4;

public:
	Ipv4Address() : IpAddress(IpAddressType::IP4, IPV4_ADDRESS_SIZE){}
	Ipv4Address(uint8_t stream[]);
	Ipv4Address(uint8_t firstOctet, uint8_t secondOctet,uint8_t thirdOctet,uint8_t fourthOctet);
	Ipv4Address(uint32_t ipv4AsUint32, const bool endianess = MachineEndianness::instance().getEndianType()); /* endianess - endianess of the uint32 input variable */
	Ipv4Address(const std::string& ipv4AddressAsString);
	virtual ~Ipv4Address()=default;
	std::string toString() const noexcept override;
	static bool isValid(const std::string& ipv4AddressAsString);
	Ipv4Address& operator=(const Ipv4Address& other) noexcept;
};
	
#endif