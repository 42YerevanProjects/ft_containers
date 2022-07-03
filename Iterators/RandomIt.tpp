#pragma once

#include <cstdlib>

template<typename T, bool isConst>
RandomIt<T, isConst>::RandomIt() : data_ptr(NULL) {}

template<typename T, bool isConst>
RandomIt<T, isConst>::RandomIt(const pointer ptr) : data_ptr(ptr) {}

template<typename T, bool isConst>
RandomIt<T, isConst>::RandomIt(const RandomIt<T, isConst> &other) { *this = other; }

template<typename T, bool isConst>
RandomIt<T, isConst>::~RandomIt() {}

template<typename T, bool isConst>
RandomIt<T, isConst>&   RandomIt<T, isConst>::operator=(const RandomIt<T, isConst>& other)
{
    this->data_ptr = other.data_ptr;
    return (*this);
}

template<typename T, bool isConst>
RandomIt<T, isConst>   RandomIt<T, isConst>::operator++(int)
{
    RandomIt<T, isConst> temp = *this;
    this->data_ptr++;
    return temp;
}

template<typename T, bool isConst>
RandomIt<T, isConst>&   RandomIt<T, isConst>::operator++()
{
    ++this->data_ptr;
    return (*this);
}

template<typename T, bool isConst>
RandomIt<T, isConst>   RandomIt<T, isConst>::operator+(size_t n) const
{
    RandomIt<T, isConst> temp = *this;
    temp.data_ptr += n;
    return temp;
}

template<typename T, bool isConst>
RandomIt<T, isConst>&   RandomIt<T, isConst>::operator+=(size_t n)
{
    this->data_ptr += n;
    return (*this);
}

template<typename T, bool isConst>
RandomIt<T, isConst>   RandomIt<T, isConst>::operator--(int)
{
    RandomIt<T, isConst> temp = *this;
    temp.data_ptr--;
    return temp;
}

template<typename T, bool isConst>
RandomIt<T, isConst>&   RandomIt<T, isConst>::operator--()
{
    --this->data_ptr;
    return (*this);
}

template<typename T, bool isConst>
RandomIt<T, isConst>   RandomIt<T, isConst>::operator-(size_t n) const
{
    RandomIt<T, isConst> temp = *this;
    temp.data_ptr -= n;
    return temp;
}

template<typename T, bool isConst>
typename RandomIt<T, isConst>::difference_type  RandomIt<T, isConst>::operator-(RandomIt<T, isConst> it) const
{
    return (this->data_ptr - it.data_ptr);
}

template<typename T, bool isConst>
RandomIt<T, isConst>&   RandomIt<T, isConst>::operator-=(size_t n)
{
    this->data_ptr -= n;
    return (*this);
}

template<typename T, bool isConst>
typename RandomIt<T, isConst>::reference   RandomIt<T, isConst>::operator*()
{
    return (*this->data_ptr);
}

template<typename T, bool isConst>
typename RandomIt<T, isConst>::pointer   RandomIt<T, isConst>::operator->()
{
    return (this->data_ptr);
}

template<typename T, bool isConst>
typename RandomIt<T, isConst>::reference   RandomIt<T, isConst>::operator[](size_t n)
{
    return (*(this->data_ptr + n));
}

template<typename T, bool isConst>
bool    RandomIt<T, isConst>::operator==(const RandomIt<T, isConst> &other) const
{
    return (this->data_ptr == other.data_ptr);
}

template<typename T, bool isConst>
bool    RandomIt<T, isConst>::operator!=(const RandomIt<T, isConst> &other) const
{
    return (this->data_ptr != other.data_ptr);
}


template<typename T, bool isConst>
bool    RandomIt<T, isConst>::operator>=(const RandomIt<T, isConst> &other) const
{
    return (this->data_ptr >= other.data_ptr);
}

template<typename T, bool isConst>
bool    RandomIt<T, isConst>::operator<=(const RandomIt<T, isConst> &other) const
{
    return (this->data_ptr <= other.data_ptr);
}

template<typename T, bool isConst>
bool    RandomIt<T, isConst>::operator>(const RandomIt<T, isConst> &other) const
{
    return (this->data_ptr > other.data_ptr);
}

template<typename T, bool isConst>
bool    RandomIt<T, isConst>::operator<(const RandomIt<T, isConst> &other) const
{
    return (this->data_ptr < other.data_ptr);
}
