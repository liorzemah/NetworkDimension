#ifndef DATALINK_H
#define DATALINK_H

#include <pcap.h>
#include <vector>
#include <string>
#include "Interfaces/IValidExpression.hpp"

class DataLink : IValidExpression<DataLink, int>
{
private:
	typedef int DataLinkType;
	static constexpr DataLinkType DLT_NOT_INITIALIZED = -1;
	DataLinkType _type = DLT_NOT_INITIALIZED;
	pcap_t* _deviceDescriptor = nullptr;
	std::vector<DataLinkType> _possibleTypes;

	DataLink()=default;
	DataLink(pcap_t* deviceDescriptor);
	DataLink& operator=(const DataLink& other) noexcept;
	~DataLink()=default;
	
	DataLink::DataLinkType get() const noexcept;
	const std::string getName() const;
	const std::string getDescription() const;
	const std::vector<DataLink::DataLinkType> possibleTypes() const noexcept;
	bool isValidDataLinkType(DataLinkType type) const noexcept;
	void set(DataLinkType type);
	std::string toString() const noexcept;

	friend class Device;
};
#endif