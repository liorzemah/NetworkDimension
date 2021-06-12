#ifndef IEMPTY_H
#define IEMPTY_H

// Implement The Curiously Recurring Template Pattern (CRTP)
template<class T>
class IEmpty
{
public:
    static const T& empty()
    {
        static const T instance;
        return instance;
    }

    bool isEmpty() const noexcept {  return *(static_cast<const T*>(this)) == empty(); }
};

#endif