#include "MacAddress.hpp"  
#include <sstream>
#include <iomanip>
#include <iostream>
#include <regex>

MacAddress::MacAddress(uint8_t stream[]) : MacAddress()
{
	std::copy(stream, stream + MAC_ADDRESS_SIZE, _stream.get());
}

MacAddress::MacAddress(uint8_t firstOctet, uint8_t secondOctet,uint8_t thirdOctet,uint8_t fourthOctet,uint8_t fifthOctet,uint8_t sixthOctet) : MacAddress()
{
	_stream.get()[0] = firstOctet;
	_stream.get()[1] = secondOctet;
	_stream.get()[2] = thirdOctet;
	_stream.get()[3] = fourthOctet;
	_stream.get()[4] = fifthOctet;
	_stream.get()[5] = sixthOctet;
}

MacAddress::MacAddress(const std::string& macAddressAsString) : MacAddress()
{
	if (isValid(macAddressAsString))
	{
		std::stringstream stringstream(macAddressAsString);
		char seprator;
		int octet;

		for (int i = 0; i < MAC_ADDRESS_SIZE; ++i)
		{		
			stringstream >> std::hex >> octet >> seprator;
			_stream.get()[i] = octet;
		}
	}
	else
	{
		throw std::invalid_argument("MacAddress cot' get invalid mac address string");
	}
}

std::string MacAddress::toString() const noexcept
{
	std::stringstream stringstream;
	constexpr static char MAC_ADDRESS_SEPARATOR = ':';
	
	for (int i=0; i<MAC_ADDRESS_SIZE - 1; ++i)
	{
		stringstream << std::setfill('0') << std::setw(2) << std::hex << +_stream.get()[i] << MAC_ADDRESS_SEPARATOR;
	}
	stringstream << std::setfill('0') << std::setw(2) << std::hex << +_stream.get()[MAC_ADDRESS_SIZE - 1];
	return stringstream.str();
}

bool MacAddress::isValid(const std::string& macAddressAsString)
{
	// Regex expression for validating Mac address
    const std::regex pattern("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
 
    // If the MAC address is empty return false
    if (macAddressAsString.empty())
    {
        return false;
    }
 
    // Return true if the MAC address matched the Regex
	return regex_match(macAddressAsString, pattern);	
}