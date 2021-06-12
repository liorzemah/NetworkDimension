#include "Printable.hpp"
#include <ostream>

std::ostream& operator<< (std::ostream& out, const Printable& printable)
{
	out << printable.toString();
	return out;
}