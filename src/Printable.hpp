#ifndef PRINTABLE_H
#define PRINTABLE_H

#include "Interfaces/IString.hpp"

class Printable : IString
{
private:

public:

	Printable()=default;
	~Printable()=default;
	
	virtual std::string toString() const noexcept = 0;
	friend std::ostream& operator<< (std::ostream& out, const Printable& printable);

};

#endif