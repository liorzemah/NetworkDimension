#include "DataLink.hpp"
#include <iostream>
#include <sstream>
#include <iomanip> 

DataLink::DataLink(pcap_t* deviceDescriptor) :
     _deviceDescriptor(deviceDescriptor),
     _possibleTypes({})
{
    if (!_deviceDescriptor)
        throw std::runtime_error("device descriptor not initialized");

    int* listOfDataLinks, listSize;
    if ((listSize = pcap_list_datalinks(_deviceDescriptor, &listOfDataLinks)) == PCAP_ERROR)
        throw std::runtime_error(pcap_geterr(_deviceDescriptor));
    else
    {
        for (int i=0;i<listSize; ++i)
            _possibleTypes.emplace_back(listOfDataLinks[i]);

        pcap_free_datalinks(listOfDataLinks);
    }
    _type = pcap_datalink(_deviceDescriptor);
}

DataLink& DataLink::operator=(const DataLink& other) noexcept
{
    if (this == &other)
        return *this;

    this->_deviceDescriptor = other._deviceDescriptor;
    this->_type = other._type;
    this->_possibleTypes = other._possibleTypes;
    return *this;   
}

DataLink::DataLinkType DataLink::get() const noexcept
{
    return _type;
}

const std::string DataLink::getName() const
{
    if (_type == DLT_NOT_INITIALIZED)
        throw std::runtime_error("type not initialized");

    return std::string(pcap_datalink_val_to_name(_type));
}

const std::string DataLink::getDescription() const
{
    if (!_deviceDescriptor)
        throw std::runtime_error("type not initialized");
    
    return std::string(pcap_datalink_val_to_description(_type));
}

const std::vector<DataLink::DataLinkType> DataLink::possibleTypes() const noexcept
{
    return _possibleTypes;
}

bool DataLink::isValidDataLinkType(DataLinkType type) const noexcept
{
    for (auto& possibleType : _possibleTypes)
    {
        if (possibleType == type)
            return true;
    }
    return false;
}

void DataLink::set(DataLinkType type)
{
    if (!_deviceDescriptor)
        throw std::runtime_error("device descriptor not initialized");

    if (!isValidDataLinkType(type))
        throw std::invalid_argument("given data-link type not one of the types that this device support");
    
    if (pcap_set_datalink(_deviceDescriptor, type) == PCAP_ERROR)
        throw std::runtime_error(pcap_geterr(_deviceDescriptor));
}

std::string DataLink::toString() const noexcept
{
    std::stringstream stringstream;
    stringstream << "DataLink:" << std::endl; 
    if (!_deviceDescriptor){
        stringstream << "Device descriptor not initialized" << std::endl;
        return stringstream.str();
    }

    if (!_type){
        stringstream << "Type not initialized" << std::endl;
        return stringstream.str();
    }

    stringstream << "Possible types suppoted by device:" << std::endl;

    for (auto& possibleType : _possibleTypes)
    {
        stringstream << pcap_datalink_val_to_name(possibleType) << " (" <<
            pcap_datalink_val_to_description(possibleType) << ")"<< std::endl;
    }

	stringstream << "DataLink used: " << getName() << " (" <<
        getDescription() << ")"<< std::endl;

	return stringstream.str();
}