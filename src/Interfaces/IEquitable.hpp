#ifndef IEQUITABLE_H
#define IEQUITABLE_H

// Implement The Curiously Recurring Template Pattern (CRTP)
template<class T>	
class IEquitable  
{
public:
	virtual bool operator==(const T& other) const = 0;
	virtual bool operator!=(const T& other) const { return !(*this == other); }
};

#endif