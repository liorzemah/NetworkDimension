#include "MachineEndianness.hpp"  
	
MachineEndianness::MachineEndianness()
{
	unsigned int temp = 1; 
    char *tempAddr = (char*)&temp; 
    if (*tempAddr) 
        _endianType = LITTLE_ENDIAN_TYPE; 
    else
        _endianType = BIG_ENDIAN_TYPE; 
}

MachineEndianness& MachineEndianness::instance() 
{
    static MachineEndianness _instance;
    return _instance;
}

bool MachineEndianness::operator==(const bool& other) const 
{
    return _endianType == other;
}

