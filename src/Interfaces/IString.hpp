#ifndef ISTRING_H
#define ISTRING_H

#include <string>
	
class IString
{
public:
    virtual std::string toString() const noexcept = 0;
};

#endif