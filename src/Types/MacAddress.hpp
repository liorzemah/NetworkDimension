#ifndef MACADDRESS_H
#define MACADDRESS_H

#include <string>
#include <iostream>
#include "Types/BytesStream.hpp"
#include "Printable.hpp"
#include "Interfaces/IValidExpression.hpp"
#include "Interfaces/IEmpty.hpp"
#include "Interfaces/IHash.hpp"
	
class MacAddress : public BytesStream,
				   public Printable,
				   public IValidExpression<MacAddress, std::string>,
				   public IEmpty<MacAddress>
{
private:
	constexpr static uint8_t MAC_ADDRESS_SIZE = 6;

public:
	constexpr static uint8_t MAC_ADDRESS_STRING_SIZE = 17;

	MacAddress() : BytesStream(MAC_ADDRESS_SIZE){}
	MacAddress(uint8_t stream[]);
	MacAddress(uint8_t firstOctet, uint8_t secondOctet,uint8_t thirdOctet,uint8_t fourthOctet,uint8_t fifthOctet,uint8_t sixthOctet);
	MacAddress(const std::string& macAddressAsString);
	virtual ~MacAddress()=default;
	std::string toString() const noexcept override;
	static bool isValid(const std::string& macAddressAsString);
};

#endif