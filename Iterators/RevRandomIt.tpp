#pragma once

#include <cstdlib>

template<typename T, typename Pointer, typename Reference>
RevRandomIt<T, Pointer, Reference>::RevRandomIt() : data_ptr(NULL) {}

template<typename T, typename Pointer, typename Reference>
RevRandomIt<T, Pointer, Reference>::RevRandomIt(const Pointer ptr) : data_ptr(ptr) {}

template<typename T, typename Pointer, typename Reference>
RevRandomIt<T, Pointer, Reference>::RevRandomIt(const iterator &other) { *this = other; }

template<typename T, typename Pointer, typename Reference>
RevRandomIt<T, Pointer, Reference>::~RevRandomIt() {}

template<typename T, typename Pointer, typename Reference>
RevRandomIt<T, Pointer, Reference>&   RevRandomIt<T, Pointer, Reference>::operator=(const iterator& other)
{
    this->data_ptr = other.data_ptr;
    return (*this);
}

template<typename T, typename Pointer, typename Reference>
RevRandomIt<T, Pointer, Reference>   RevRandomIt<T, Pointer, Reference>::operator++(int)
{
    RevRandomIt<T, Pointer, Reference> temp = *this;
    this->data_ptr--;
    return temp;
}

template<typename T, typename Pointer, typename Reference>
RevRandomIt<T, Pointer, Reference>&   RevRandomIt<T, Pointer, Reference>::operator++()
{
    --this->data_ptr;
    return (*this);
}

template<typename T, typename Pointer, typename Reference>
RevRandomIt<T, Pointer, Reference>   RevRandomIt<T, Pointer, Reference>::operator+(size_t n) const
{
    RevRandomIt<T, Pointer, Reference> temp = *this;
    temp.data_ptr -= n;
    return temp;
}

template<typename T, typename Pointer, typename Reference>
RevRandomIt<T, Pointer, Reference>&   RevRandomIt<T, Pointer, Reference>::operator+=(size_t n)
{
    this->data_ptr -= n;
    return (*this);
}

template<typename T, typename Pointer, typename Reference>
RevRandomIt<T, Pointer, Reference>   RevRandomIt<T, Pointer, Reference>::operator--(int)
{
    RevRandomIt<T, Pointer, Reference> temp = *this;
    temp.data_ptr++;
    return temp;
}

template<typename T, typename Pointer, typename Reference>
RevRandomIt<T, Pointer, Reference>&   RevRandomIt<T, Pointer, Reference>::operator--()
{
    ++this->data_ptr;
    return (*this);
}

template<typename T, typename Pointer, typename Reference>
RevRandomIt<T, Pointer, Reference>   RevRandomIt<T, Pointer, Reference>::operator-(size_t n) const
{
    RevRandomIt<T, Pointer, Reference> temp = *this;
    temp.data_ptr -= n;
    return temp;
}

template<typename T, typename Pointer, typename Reference>
size_t   RevRandomIt<T, Pointer, Reference>::operator-(RevRandomIt<T, Pointer, Reference> it) const
{
    return (this->data_ptr - it.data_ptr);
}

template<typename T, typename Pointer, typename Reference>
RevRandomIt<T, Pointer, Reference>&   RevRandomIt<T, Pointer, Reference>::operator-=(size_t n)
{
    this->data_ptr -= n;
    return (*this);
}

template<typename T, typename Pointer, typename Reference>
Reference   RevRandomIt<T, Pointer, Reference>::operator*()
{
    return (*this->data_ptr);
}

template<typename T, typename Pointer, typename Reference>
Pointer   RevRandomIt<T, Pointer, Reference>::operator->()
{
    return (this->data_ptr);
}

template<typename T, typename Pointer, typename Reference>
Reference   RevRandomIt<T, Pointer, Reference>::operator[](size_t n)
{
    return (*(this->data_ptr - n));
}

template<typename T, typename Pointer, typename Reference>
bool    RevRandomIt<T, Pointer, Reference>::operator==(const RevRandomIt<T, Pointer, Reference> &other) const
{
    return (this->data_ptr == other.data_ptr);
}

template<typename T, typename Pointer, typename Reference>
bool    RevRandomIt<T, Pointer, Reference>::operator!=(const RevRandomIt<T, Pointer, Reference> &other) const
{
    return (this->data_ptr != other.data_ptr);
}

