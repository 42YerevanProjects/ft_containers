#pragma once

#include <cstdlib>

template<typename T, bool isConst>
RevRandomIt<T, isConst>::RevRandomIt() : data_ptr(NULL) {}

template<typename T, bool isConst>
RevRandomIt<T, isConst>::RevRandomIt(const pointer ptr) : data_ptr(ptr) {}

template<typename T, bool isConst>
RevRandomIt<T, isConst>::RevRandomIt(const RevRandomIt<T, isConst>& other) { *this = other; }

template<typename T, bool isConst>
RevRandomIt<T, isConst>::~RevRandomIt() {}

template<typename T, bool isConst>
RevRandomIt<T, isConst>&   RevRandomIt<T, isConst>::operator=(const RevRandomIt<T, isConst>& other)
{
    this->data_ptr = other.data_ptr;
    return (*this);
}

template<typename T, bool isConst>
RevRandomIt<T, isConst>   RevRandomIt<T, isConst>::operator++(int)
{
    RevRandomIt<T, isConst> temp = *this;
    this->data_ptr--;
    return temp;
}

template<typename T, bool isConst>
RevRandomIt<T, isConst>&   RevRandomIt<T, isConst>::operator++()
{
    --this->data_ptr;
    return (*this);
}

template<typename T, bool isConst>
RevRandomIt<T, isConst>   RevRandomIt<T, isConst>::operator+(size_t n) const
{
    RevRandomIt<T, isConst> temp = *this;
    temp.data_ptr -= n;
    return temp;
}

template<typename T, bool isConst>
RevRandomIt<T, isConst>&   RevRandomIt<T, isConst>::operator+=(size_t n)
{
    this->data_ptr -= n;
    return (*this);
}

template<typename T, bool isConst>
RevRandomIt<T, isConst>   RevRandomIt<T, isConst>::operator--(int)
{
    RevRandomIt<T, isConst> temp = *this;
    temp.data_ptr++;
    return temp;
}

template<typename T, bool isConst>
RevRandomIt<T, isConst>&   RevRandomIt<T, isConst>::operator--()
{
    ++this->data_ptr;
    return (*this);
}

template<typename T, bool isConst>
RevRandomIt<T, isConst>   RevRandomIt<T, isConst>::operator-(size_t n) const
{
    RevRandomIt<T, isConst> temp = *this;
    temp.data_ptr -= n;
    return temp;
}

template<typename T, bool isConst>
typename RevRandomIt<T, isConst>::difference_type   RevRandomIt<T, isConst>::operator-(RevRandomIt<T, isConst> it) const
{
    return (this->data_ptr - it.data_ptr);
}

template<typename T, bool isConst>
RevRandomIt<T, isConst>&   RevRandomIt<T, isConst>::operator-=(size_t n)
{
    this->data_ptr -= n;
    return (*this);
}

template<typename T, bool isConst>
typename RevRandomIt<T, isConst>::reference   RevRandomIt<T, isConst>::operator*()
{
    return (*this->data_ptr);
}

template<typename T, bool isConst>
typename RevRandomIt<T, isConst>::pointer   RevRandomIt<T, isConst>::operator->()
{
    return (this->data_ptr);
}

template<typename T, bool isConst>
typename RevRandomIt<T, isConst>::reference   RevRandomIt<T, isConst>::operator[](size_t n)
{
    return (*(this->data_ptr - n));
}

template<typename T, bool isConst>
bool    RevRandomIt<T, isConst>::operator==(const RevRandomIt<T, isConst> &other) const
{
    return (this->data_ptr == other.data_ptr);
}

template<typename T, bool isConst>
bool    RevRandomIt<T, isConst>::operator!=(const RevRandomIt<T, isConst> &other) const
{
    return (this->data_ptr != other.data_ptr);
}

template<typename T, bool isConst>
bool    RevRandomIt<T, isConst>::operator>=(const RevRandomIt<T, isConst> &other) const
{
    return (this->data_ptr >= other.data_ptr);
}

template<typename T, bool isConst>
bool    RevRandomIt<T, isConst>::operator<=(const RevRandomIt<T, isConst> &other) const
{
    return (this->data_ptr <= other.data_ptr);
}

template<typename T, bool isConst>
bool    RevRandomIt<T, isConst>::operator>(const RevRandomIt<T, isConst> &other) const
{
    return (this->data_ptr > other.data_ptr);
}

template<typename T, bool isConst>
bool    RevRandomIt<T, isConst>::operator<(const RevRandomIt<T, isConst> &other) const
{
    return (this->data_ptr < other.data_ptr);
}

