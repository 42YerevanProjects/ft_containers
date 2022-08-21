#pragma once

#include <cstddef>

namespace ft
{

    template<typename T>
    random_iterator<T>::random_iterator() : _elem(NULL) {}
    
    template<typename T>
    random_iterator<T>::random_iterator(pointer ptr) : _elem(ptr) {}
    
    template<typename T>
    random_iterator<T>::random_iterator(const random_iterator& other) { *this = other; }
    
    template<typename T>
    random_iterator<T>::~random_iterator() {}
    
    template<typename T>
    random_iterator<T>&   random_iterator<T>::operator=(const random_iterator& other)
    {
        this->_elem = other._elem;
        return (*this);
    }

    template<typename T>
    random_iterator<T>::operator random_iterator<const T> () const
    {
        return (random_iterator<const T>(this->_elem));
    }
    
    template<typename T>
    random_iterator<T>      random_iterator<T>::operator++(int)
    {
        random_iterator<T> temp = *this;
        operator++();
        return temp;
    }
    
    template<typename T>
    random_iterator<T>&     random_iterator<T>::operator++()
    {
        this->_elem++;
        return (*this);
    }
    
    template<typename T>
    random_iterator<T>      random_iterator<T>::operator+(difference_type n) const
    {
        random_iterator<T> temp = *this;
        temp._elem += n;
        return temp;
    }
    
    template<typename T>
    random_iterator<T>&   random_iterator<T>::operator+=(difference_type n)
    {
        this->_elem += n;
        return (*this);
    }
    
    template<typename T>
    random_iterator<T>   random_iterator<T>::operator--(int)
    {
        random_iterator<T> temp = *this;
        operator--();
        return temp;
    }
    
    template<typename T>
    random_iterator<T>&   random_iterator<T>::operator--()
    {
        --this->_elem;
        return (*this);
    }
    
    template<typename T>
    random_iterator<T>   random_iterator<T>::operator-(difference_type n) const
    {
        random_iterator<T> temp = *this;
        temp._elem -= n;
        return temp;
    }
    
    template<typename T>
    typename random_iterator<T>::difference_type  random_iterator<T>::operator-(random_iterator<T> it) const
    {
        return (this->_elem - it._elem);
    }
    
    template<typename T>
    random_iterator<T>&   random_iterator<T>::operator-=(difference_type n)
    {
        this->_elem -= n;
        return (*this);
    }
    
    template<typename T>
    typename random_iterator<T>::reference   random_iterator<T>::operator*()
    {
        return (*this->_elem);
    }
    
    template<typename T>
    typename random_iterator<T>::pointer   random_iterator<T>::operator->()
    {
        return (&(operator*()));
    }
    
    template<typename T>
    typename random_iterator<T>::reference   random_iterator<T>::operator[](difference_type n)
    {
        return (*(operator+(n)));
    }

    template<typename T>
    typename random_iterator<T>::pointer   random_iterator<T>::base() const
    {
        return (this->_elem);
    }
    
    /* Comparison Operator Functions*/
    
    template<typename T>
    bool    random_iterator<T>::operator==(const random_iterator& other) const
    {
        return (this->_elem == other._elem);
    }
    
    template<typename T>
    bool    random_iterator<T>::operator!=(const random_iterator& other) const
    {
        return (this->_elem != other._elem);
    }
    
    
    template<typename T>
    bool    random_iterator<T>::operator>=(const random_iterator& other) const
    {
        return (this->_elem >= other._elem);
    }
    
    template<typename T>
    bool    random_iterator<T>::operator<=(const random_iterator& other) const
    {
        return (this->_elem <= other._elem);
    }
    
    template<typename T>
    bool    random_iterator<T>::operator>(const random_iterator& other) const
    {
        return (this->_elem > other._elem);
    }
    
    template<typename T>
    bool    random_iterator<T>::operator<(const random_iterator& other) const
    {
        return (this->_elem < other._elem);
    }

    /* Non-member operator overloads */

    template <typename T>
    typename random_iterator<T>::difference_type    operator==(const random_iterator<T>& lhs, const random_iterator<T>& rhs)
    {
        return (lhs.base() == rhs.base());
    }

    // For iterator == const_iterator 
    template<typename T_L, typename T_R>
    typename random_iterator<T_L>::difference_type  operator==(const random_iterator<T_L>& lhs, const random_iterator<T_R>& rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T>
    typename random_iterator<T>::difference_type    operator!=(const random_iterator<T>& lhs, const random_iterator<T>& rhs)
    {
        return (lhs.base() != rhs.base());
    }

    // For iterator != const_iterator
    template<typename T_L, typename T_R>
    typename random_iterator<T_L>::difference_type  operator!=(const random_iterator<T_L>& lhs, const random_iterator<T_R>& rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename T>
    typename random_iterator<T>::difference_type    operator<(const random_iterator<T>& lhs, const random_iterator<T>& rhs)
    {
        return (lhs.base() < rhs.base());
    }

    /* For iterator < const_iterator */
    template<typename T_L, typename T_R>
    typename random_iterator<T_L>::difference_type  operator<(const random_iterator<T_L>& lhs, const random_iterator<T_R>& rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T>
    typename random_iterator<T>::difference_type    operator>(const random_iterator<T>& lhs, const random_iterator<T>& rhs)
    {
        return (lhs.base() > rhs.base());
    }

    // For iterator > const_iterator
    template<typename T_L, typename T_R>
    typename random_iterator<T_L>::difference_type  operator>(const random_iterator<T_L>& lhs, const random_iterator<T_R>& rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T>
    typename random_iterator<T>::difference_type    operator<=(const random_iterator<T>& lhs, const random_iterator<T>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    // For iterator <= const_iterator 
    template<typename T_L, typename T_R>
    typename random_iterator<T_L>::difference_type  operator<=(const random_iterator<T_L>& lhs, const random_iterator<T_R>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T>
    typename random_iterator<T>::difference_type    operator>=(const random_iterator<T>& lhs, const random_iterator<T>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    // For iterator >= const_iterator
    template<typename T_L, typename T_R>
    typename random_iterator<T_L>::difference_type  operator>=(const random_iterator<T_L>& lhs, const random_iterator<T_R>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template<typename T>
    random_iterator<T>  operator+(typename random_iterator<T>::difference_type n, random_iterator<T>& rai)
    {
        return (rai + n);
    }

    template <typename T>
    typename random_iterator<T>::difference_type    operator-(const random_iterator<T>& lhs, const random_iterator<T>& rhs)
    {
        return (lhs.base() - rhs.base());
    }

    // For iterator - const_iterator
    template<typename T_L, typename T_R>
    typename random_iterator<T_L>::difference_type  operator-(const random_iterator<T_L>& lhs, const random_iterator<T_R>& rhs)
    {
        return (lhs.base() - rhs.base());
    }
}
