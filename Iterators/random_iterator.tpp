#pragma once

#include <cstddef>

namespace ft
{

    template<typename T>
    random_iterator<T>::random_iterator() : data_ptr(NULL) {}
    
    template<typename T>
    random_iterator<T>::random_iterator(pointer ptr) : data_ptr(ptr) {}
    
    template<typename T>
    random_iterator<T>::random_iterator(const random_iterator& other) { *this = other; }
    
    template<typename T>
    random_iterator<T>::~random_iterator() {}
    
    template<typename T>
    random_iterator<T>&   random_iterator<T>::operator=(const random_iterator& other)
    {
        this->data_ptr = other.data_ptr;
        return (*this);
    }

    template<typename T>
    random_iterator<T>::operator random_iterator<const T> () const
    {
        return (random_iterator<const T>(this->data_ptr));
    }
    
    template<typename T>
    random_iterator<T>   random_iterator<T>::operator++(int)
    {
        random_iterator<T> temp = *this;
        this->data_ptr++;
        return temp;
    }
    
    template<typename T>
    random_iterator<T>&   random_iterator<T>::operator++()
    {
        ++this->data_ptr;
        return (*this);
    }
    
    template<typename T>
    random_iterator<T>   random_iterator<T>::operator+(size_t n) const
    {
        random_iterator<T> temp = *this;
        temp.data_ptr += n;
        return temp;
    }
    
    template<typename T>
    random_iterator<T>&   random_iterator<T>::operator+=(size_t n)
    {
        this->data_ptr += n;
        return (*this);
    }
    
    template<typename T>
    random_iterator<T>   random_iterator<T>::operator--(int)
    {
        random_iterator<T> temp = *this;
        temp.data_ptr--;
        return temp;
    }
    
    template<typename T>
    random_iterator<T>&   random_iterator<T>::operator--()
    {
        --this->data_ptr;
        return (*this);
    }
    
    template<typename T>
    random_iterator<T>   random_iterator<T>::operator-(size_t n) const
    {
        random_iterator<T> temp = *this;
        temp.data_ptr -= n;
        return temp;
    }
    
    template<typename T>
    typename random_iterator<T>::difference_type  random_iterator<T>::operator-(random_iterator<T> it) const
    {
        return (this->data_ptr - it.data_ptr);
    }
    
    template<typename T>
    random_iterator<T>&   random_iterator<T>::operator-=(size_t n)
    {
        this->data_ptr -= n;
        return (*this);
    }
    
    template<typename T>
    typename random_iterator<T>::reference   random_iterator<T>::operator*()
    {
        return (*this->data_ptr);
    }
    
    template<typename T>
    typename random_iterator<T>::pointer   random_iterator<T>::operator->()
    {
        return (this->data_ptr);
    }
    
    template<typename T>
    typename random_iterator<T>::reference   random_iterator<T>::operator[](size_t n)
    {
        return (*(this->data_ptr + n));
    }
    
    template<typename T>
    bool    random_iterator<T>::operator==(const random_iterator<T> &other) const
    {
        return (this->data_ptr == other.data_ptr);
    }
    
    template<typename T>
    bool    random_iterator<T>::operator!=(const random_iterator<T> &other) const
    {
        return (this->data_ptr != other.data_ptr);
    }
    
    
    template<typename T>
    bool    random_iterator<T>::operator>=(const random_iterator<T> &other) const
    {
        return (this->data_ptr >= other.data_ptr);
    }
    
    template<typename T>
    bool    random_iterator<T>::operator<=(const random_iterator<T> &other) const
    {
        return (this->data_ptr <= other.data_ptr);
    }
    
    template<typename T>
    bool    random_iterator<T>::operator>(const random_iterator<T> &other) const
    {
        return (this->data_ptr > other.data_ptr);
    }
    
    template<typename T>
    bool    random_iterator<T>::operator<(const random_iterator<T> &other) const
    {
        return (this->data_ptr < other.data_ptr);
    }
}
