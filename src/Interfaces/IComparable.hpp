#ifndef ICOMPARABLE_H
#define ICOMPARABLE_H

// Implement The Curiously Recurring Template Pattern (CRTP)
template<class T>	
class IComparable  
{
public:
    virtual bool operator<(const T& other) const = 0;
    virtual bool operator>(const T& other) const = 0;	
};

#endif