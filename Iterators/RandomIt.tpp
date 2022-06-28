#pragma once

#include <cstdlib>

template<typename T, typename Pointer, typename Reference>
RandomIt<T, Pointer, Reference>::RandomIt() : data_ptr(NULL) {}

template<typename T, typename Pointer, typename Reference>
RandomIt<T, Pointer, Reference>::RandomIt(const Pointer ptr) : data_ptr(ptr) {}

template<typename T, typename Pointer, typename Reference>
RandomIt<T, Pointer, Reference>::RandomIt(const iterator &other) { *this = other; }

template<typename T, typename Pointer, typename Reference>
RandomIt<T, Pointer, Reference>::~RandomIt() {}

template<typename T, typename Pointer, typename Reference>
RandomIt<T, Pointer, Reference>&   RandomIt<T, Pointer, Reference>::operator=(const iterator& other)
{
    this->data_ptr = other.data_ptr;
    return (*this);
}

template<typename T, typename Pointer, typename Reference>
RandomIt<T, Pointer, Reference>   RandomIt<T, Pointer, Reference>::operator++(int)
{
    RandomIt<T, Pointer, Reference> temp = *this;
    this->data_ptr++;
    return temp;
}

template<typename T, typename Pointer, typename Reference>
RandomIt<T, Pointer, Reference>&   RandomIt<T, Pointer, Reference>::operator++()
{
    ++this->data_ptr;
    return (*this);
}

template<typename T, typename Pointer, typename Reference>
RandomIt<T, Pointer, Reference>   RandomIt<T, Pointer, Reference>::operator+(size_t n) const
{
    RandomIt<T, Pointer, Reference> temp = *this;
    temp.data_ptr += n;
    return temp;
}

template<typename T, typename Pointer, typename Reference>
RandomIt<T, Pointer, Reference>&   RandomIt<T, Pointer, Reference>::operator+=(size_t n)
{
    this->data_ptr += n;
    return (*this);
}

template<typename T, typename Pointer, typename Reference>
RandomIt<T, Pointer, Reference>   RandomIt<T, Pointer, Reference>::operator--(int)
{
    RandomIt<T, Pointer, Reference> temp = *this;
    temp.data_ptr--;
    return temp;
}

template<typename T, typename Pointer, typename Reference>
RandomIt<T, Pointer, Reference>&   RandomIt<T, Pointer, Reference>::operator--()
{
    --this->data_ptr;
    return (*this);
}

template<typename T, typename Pointer, typename Reference>
RandomIt<T, Pointer, Reference>   RandomIt<T, Pointer, Reference>::operator-(size_t n) const
{
    RandomIt<T, Pointer, Reference> temp = *this;
    temp.data_ptr -= n;
    return temp;
}

template<typename T, typename Pointer, typename Reference>
size_t   RandomIt<T, Pointer, Reference>::operator-(RandomIt<T, Pointer, Reference> it) const
{
    return (this->data_ptr - it.data_ptr);
}

template<typename T, typename Pointer, typename Reference>
RandomIt<T, Pointer, Reference>&   RandomIt<T, Pointer, Reference>::operator-=(size_t n)
{
    this->data_ptr -= n;
    return (*this);
}

template<typename T, typename Pointer, typename Reference>
Reference   RandomIt<T, Pointer, Reference>::operator*()
{
    return (*this->data_ptr);
}

template<typename T, typename Pointer, typename Reference>
Pointer   RandomIt<T, Pointer, Reference>::operator->()
{
    return (this->data_ptr);
}

template<typename T, typename Pointer, typename Reference>
Reference   RandomIt<T, Pointer, Reference>::operator[](size_t n)
{
    return (*(this->data_ptr + n));
}

template<typename T, typename Pointer, typename Reference>
bool    RandomIt<T, Pointer, Reference>::operator==(const RandomIt<T, Pointer, Reference> &other) const
{
    return (this->data_ptr == other.data_ptr);
}

template<typename T, typename Pointer, typename Reference>
bool    RandomIt<T, Pointer, Reference>::operator!=(const RandomIt<T, Pointer, Reference> &other) const
{
    return (this->data_ptr != other.data_ptr);
}
