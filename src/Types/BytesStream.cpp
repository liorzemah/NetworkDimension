#include "BytesStream.hpp"  
#include <stdexcept>

BytesStream::BytesStream(uint32_t size) : _size(size),
                                          _stream(std::shared_ptr<uint8_t>(new uint8_t[size], std::default_delete<uint8_t>{}))
{
    std::fill(_stream.get(), _stream.get() + _size, 0);
}

BytesStream::BytesStream(const BytesStream& other) 
{
    if (this != &other)
    {
        this->_size = other._size;
        this->_stream = other._stream;
    }
}

uint8_t& BytesStream::operator[] (uint32_t index)
{
    if (index >= _size)
    {
        throw std::out_of_range("try to access memory that out of range, the index must be between 0 to " + std::to_string(_size));
    }
    return _stream.get()[index];
}

BytesStream& BytesStream::operator=(const BytesStream& other) noexcept
{
    if (this == &other)
        return *this;

    this->_size = other._size;
    this->_stream = other._stream;
    return *this;
}

bool BytesStream::operator==(const BytesStream& other) const
{
    if (this == &other)
        return true;

    if (this->_size != other._size)
        return false;

    for (uint32_t i=0; i < _size; ++i)
    {
        if (this->_stream.get()[i] != other._stream.get()[i])
            return false;
    }
    return true;
}

BytesStream BytesStream::toCopy()
{
    BytesStream copyOfByteStream(_size);
    for (uint32_t i=0; i<_size; ++i)
    {
        copyOfByteStream[i] = (*this)[i];
    }
    return copyOfByteStream;
}