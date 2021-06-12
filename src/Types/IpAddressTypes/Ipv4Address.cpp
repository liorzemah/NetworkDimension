#include "Ipv4Address.hpp"  
#include <sstream>
#include <iomanip>
#include <regex>
#include "MachineEndianness.hpp"

Ipv4Address::Ipv4Address(uint8_t stream[]) : Ipv4Address()
{
	std::copy(stream, stream + IPV4_ADDRESS_SIZE, _stream.get());
}

Ipv4Address::Ipv4Address(uint8_t firstOctet, uint8_t secondOctet,uint8_t thirdOctet,uint8_t fourthOctet) : Ipv4Address()
{
	_stream.get()[0] = firstOctet;
	_stream.get()[1] = secondOctet;
	_stream.get()[2] = thirdOctet;
	_stream.get()[3] = fourthOctet;
}

Ipv4Address::Ipv4Address(uint32_t ipv4AsUint32, const bool endianess) : Ipv4Address()
{
	if (endianess == MachineEndianness::instance().getEndianType())
	{
		/* in ordered reading */
		_stream.get()[0] = ipv4AsUint32;
		_stream.get()[1] = ipv4AsUint32 >> 8;
		_stream.get()[2] = ipv4AsUint32 >> 16;
		_stream.get()[3] = ipv4AsUint32 >> 24;
	}
	else
	{
		/* reversed reading */
		_stream.get()[0] = ipv4AsUint32 >> 24;
		_stream.get()[1] = ipv4AsUint32 >> 16;
		_stream.get()[2] = ipv4AsUint32 >> 8;
		_stream.get()[3] = ipv4AsUint32;
	}
}

Ipv4Address::Ipv4Address(const std::string& ipv4AddressAsString) : Ipv4Address()
{
	if (isValid(ipv4AddressAsString))
	{
		std::stringstream stringstream(ipv4AddressAsString);
		char seprator;
		int octet;

		for (int i = 0; i < IPV4_ADDRESS_SIZE; ++i)
		{			
			stringstream >> octet >> seprator;
			_stream.get()[i] = octet;
		}
	}	
}

std::string Ipv4Address::toString() const noexcept
{
	std::stringstream stringstream;

	for (int i=0; i<IPV4_ADDRESS_SIZE - 1;++i)
	{
		stringstream << +_stream.get()[i] << ".";
	}
	stringstream << +_stream.get()[IPV4_ADDRESS_SIZE - 1];
	return stringstream.str();
}

bool Ipv4Address::isValid(const std::string& ipv4AddressAsString)
{
	// Regex expression for validating IPv4 address
    const std::regex pattern("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
 
    // If the IPv4 address is empty return false
    if (ipv4AddressAsString.empty())
    {
        return false;
    }
 
    // Return true if the IPv4 address matched the Regex
	return regex_match(ipv4AddressAsString, pattern);	
}

Ipv4Address& Ipv4Address::operator=(const Ipv4Address& other) noexcept
{
	if (this == &other)
        return *this;

	IpAddress::operator=(other);
    return *this;
}
