#ifndef MACHINEENDIANNESS_H
#define MACHINEENDIANNESS_H

#include "Interfaces/IEquitable.hpp"

/*
    Class implement Singlethon Desing Pattern
*/
class MachineEndianness final : public IEquitable<bool>
{
public:
	static constexpr bool BIG_ENDIAN_TYPE = false;
	static constexpr bool LITTLE_ENDIAN_TYPE = true;

private:
	bool _endianType; 

public:
	MachineEndianness();
	~MachineEndianness()=default;
    static MachineEndianness& instance();
	bool operator==(const bool& other) const override;
	inline const bool getEndianType() const noexcept { return _endianType; }
};
#endif