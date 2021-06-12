#ifndef BYTESSTREAM_H
#define BYTESSTREAM_H

#include <stdint-gcc.h>
#include <algorithm>
#include <memory>
#include "Interfaces/IEquitable.hpp"
#include "Interfaces/IHash.hpp"

class BytesStream : public IEquitable<BytesStream>,
					public IHash<BytesStream>
{
protected:
	uint32_t _size;
	std::shared_ptr<uint8_t> _stream;

public:
	BytesStream(uint32_t size);
	BytesStream(const BytesStream& other); /* copy _stream by pointer */
	virtual ~BytesStream()=default;
	uint8_t& operator[] (uint32_t index);
	BytesStream& operator=(const BytesStream& other) noexcept; /* copy _stream by pointer */
	bool operator==(const BytesStream& other) const;
	//void getStream(std::shared_ptr<uint8_t>& outputStream) const { std::memcpy(outputStream.get(), _stream.get(), _size); }
	/* copy stream (by value) to outputStream and retrun outputStream, outputStream array alrady allocated */
	inline void getStream(std::shared_ptr<uint8_t>& outputStream) const { std::copy(_stream.get(), _stream.get() + _size, outputStream.get()); } 
	/* copy _stream by value */
	BytesStream toCopy(); 
	inline uint32_t byteStreamSize() const noexcept { return _size; }

    virtual std::size_t toHash() const noexcept
    {
		/* boost hash_combine implement */
		std::size_t hash = 0;
		for (uint32_t i=0; i < _size; ++i)
		{
			hash ^= std::hash<uint8_t>{}(_stream.get()[i]) + +0x9e3779b9 + (hash << 6) + (hash >> 2);
		}

        return hash;
    }
};
#endif