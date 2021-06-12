#ifndef IPADDRESS_H
#define IPADDRESS_H
	
#include <string>
#include <iostream>
#include "Types/BytesStream.hpp"
#include "Printable.hpp"
#include "Interfaces/IValidExpression.hpp"
#include "Interfaces/IEmpty.hpp"

enum class IpAddressType { UNSPECIFIED, IP4, IP6 };

class IpAddress : public BytesStream,
				  public Printable
{
private:
	IpAddressType _type;

public:
	IpAddress(IpAddressType type = IpAddressType::UNSPECIFIED, uint32_t streamSize = 0) : BytesStream(streamSize) ,_type(type){}
	IpAddress(const BytesStream& other) : BytesStream(other){}
	virtual ~IpAddress()=default;
	virtual std::string toString() const noexcept = 0;
	static std::shared_ptr<IpAddress> makeIpFromType(IpAddressType type); /* Factory method */
	static std::shared_ptr<IpAddress> makeIpFromString(const std::string& ipAddressAsString); /* Factory method */
	bool isSpecified() const noexcept { return _type != IpAddressType::UNSPECIFIED; }
	IpAddressType getType() const noexcept { return _type; }
	IpAddress& operator=(const IpAddress& other) noexcept;
	IpAddress(const IpAddress &other) : BytesStream(other) {  _type = other._type; }
};

#endif