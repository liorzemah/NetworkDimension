#ifndef IHASH_H
#define IHASH_H

#include <memory>

template <class DerivedClass>	
class IHash  
{
public:

	virtual std::size_t toHash() const noexcept = 0;

	class Hash
	{
	public:
		std::size_t operator()(const DerivedClass& obj) const noexcept
        {
            return obj.toHash();
        }
	};

	class HashForSharedPtr
	{
	public:
		std::size_t operator()(const std::shared_ptr<DerivedClass>& obj) const noexcept
        {
            return obj->toHash();
        }
	};

	class EqualForSharePtr
	{
	public:
		bool operator()(const std::shared_ptr<DerivedClass>&a, const std::shared_ptr<DerivedClass>&b) const noexcept
		{
			if(a == b) return true;
			if(a && b) return *a == *b;
			return false;
		}
	};
};

#endif