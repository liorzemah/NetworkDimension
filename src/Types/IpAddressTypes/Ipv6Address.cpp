#include "Ipv6Address.hpp"  
#include <sstream>
#include <iomanip>
#include <regex>

Ipv6Address::Ipv6Address(uint8_t stream[]) : Ipv6Address()
{
    std::copy(stream, stream + IPV6_ADDRESS_SIZE, _stream.get());
}

Ipv6Address::Ipv6Address(const std::string& ipv6AddressAsString) : Ipv6Address()
{
    if (isValid(ipv6AddressAsString))
	{
		std::stringstream stringstream(ipv6AddressAsString);
		char seprator;
		int twoOctets;

		for (int i = 0; i < IPV6_ADDRESS_SIZE; i+=2)
		{			
			stringstream >> std::hex >> twoOctets >> seprator;
			_stream.get()[i] = twoOctets >> 8;
            _stream.get()[i+1] = twoOctets;
		}
	}	
}

std::string Ipv6Address::toString() const noexcept 
{
    std::stringstream stringstream;

	for (int i=0; i<IPV6_ADDRESS_SIZE - 2;i+=2)
	{
        stringstream << std::setfill('0') << std::setw(4) << std::hex << +(_stream.get()[i + 1] + (_stream.get()[i] << 8)) << ":";
	}
    stringstream << std::setfill('0') << std::setw(4) << std::hex << +(_stream.get()[IPV6_ADDRESS_SIZE - 1] + (_stream.get()[IPV6_ADDRESS_SIZE - 2] << 8));
	return stringstream.str();
}

bool Ipv6Address::isValid(const std::string& ipv6AddressAsString) 
{
    // Regex expression for validating IPv4 address
    const std::regex pattern("((([0-9a-fA-F]){1,4})\\:){7}([0-9a-fA-F]){1,4}");
 
    // If the IPv4 address is empty return false
    if (ipv6AddressAsString.empty())
    {
        return false;
    }
 
    // Return true if the IPv6 address matched the Regex
	return regex_match(ipv6AddressAsString, pattern);	
}

Ipv6Address& Ipv6Address::operator=(const Ipv6Address& other) noexcept
{
	if (this == &other)
        return *this;

	IpAddress::operator=(other);
    return *this;
}
