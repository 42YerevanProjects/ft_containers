#pragma once

#include "iterator.hpp"

namespace ft
{
    template<typename It>
    reverse_iterator<It>::reverse_iterator() : _base(iterator_type()) {}

    template<typename It>
    reverse_iterator<It>::reverse_iterator(iterator_type it) : _base(it) {}

    template<typename It> 
    template<typename Iter>
    reverse_iterator<It>::reverse_iterator(const reverse_iterator<Iter>& rev_it) : _base(rev_it.base()) {}

    template<typename It>
    reverse_iterator<It>::~reverse_iterator() {}

    template<typename It>
    reverse_iterator<It>&    reverse_iterator<It>::operator=(const reverse_iterator& other)
    {
        _base = other._base;
        return (*this);
    }

    template<typename It>
    reverse_iterator<It>    reverse_iterator<It>::operator++(int)
    {
        reverse_iterator<It> temp = *this;
        ++(*this);
        return temp;
    }

    template<typename It>
    reverse_iterator<It>&    reverse_iterator<It>::operator++()
    {
        --_base;
        return (*this);
    }

    template<typename It>
    reverse_iterator<It>    reverse_iterator<It>::operator--(int)
    {
        reverse_iterator<It> temp = *this;
        --(*this);
        return temp;
    }

    template<typename It>
    reverse_iterator<It>&    reverse_iterator<It>::operator--()
    {
        ++_base;
        return (*this);
    }

    template<typename It>
    reverse_iterator<It>    reverse_iterator<It>::operator+(difference_type n) const
    {
            return reverse_iterator(_base - n);
    }

    template<typename It>
    reverse_iterator<It>    reverse_iterator<It>::operator-(difference_type n) const
    {
            return reverse_iterator(_base + n);
    } 

    template<typename It>
    reverse_iterator<It>&    reverse_iterator<It>::operator+=(difference_type n)
    {
        _base -= n;
        return (*this);
    }

    template<typename It>
    reverse_iterator<It>&    reverse_iterator<It>::operator-=(difference_type n)
    {
        _base += n;
        return (*this);
    }

    template<typename It>
    typename reverse_iterator<It>::reference    reverse_iterator<It>::operator*() const
    { 
        iterator_type temp = _base;
        return (*(--temp)); 
    }

    template<typename It>
    typename reverse_iterator<It>::pointer   reverse_iterator<It>::operator->() const
    { 
        return (&(*_base)); 
    }

    template<typename It>
    typename reverse_iterator<It>::reference    reverse_iterator<It>::operator[](difference_type n) const
    { 
        return (this->base()[-n - 1]); 
    }

    
    template<typename It>
    It   reverse_iterator<It>::base() const { return _base; }

    /* Comparison Operator Functions*/

    template <class Iterator>
    bool    operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
    { 
        return (lhs.base() == rhs.base()); 
    }

    template <class Iterator_L, class Iterator_R>
    bool    operator==(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) 
    { 
        return (lhs.base() == rhs.base());
    }

    template <class Iterator>
    bool    operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
    { 
        return (lhs.base() != rhs.base()); 
    }

    template <class Iterator_L, class Iterator_R>
    bool    operator!=(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) 
    { 
        return (lhs.base() != rhs.base()); 
    }

    template <class Iterator>
    bool    operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
    { 
        return (lhs.base() > rhs.base());
    }

    template <class Iterator_L, class Iterator_R>
    bool    operator<(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) 
    { 
        return (lhs.base() > rhs.base()); 
    }

    template <class Iterator>
    bool    operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
    { 
        return (lhs.base() >= rhs.base()); 
    }

    template <class Iterator_L, class Iterator_R>
    bool    operator<=(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) 
    { 
        return (lhs.base() >= rhs.base()); 
    }

    template <class Iterator>
    bool    operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
    { 
        return (lhs.base() < rhs.bash()); 
    }

    template <class Iterator_L, class Iterator_R>
    bool    operator>(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) 
    { 
        return (lhs.base() < rhs.base()); 
    }
    template <class Iterator>
    bool    operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
    { 
        return (lhs.base() <= rhs.base()); 
    }
    template <class Iterator_L, class Iterator_R>
    bool    operator>=(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) 
    { 
        return (lhs.base() <= rhs.base()); 
    }

    template <class Iterator>
    reverse_iterator<Iterator>  operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
    { 
        return (rev_it + n); 
    }

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type    operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
    { 
        return (lhs.base() - rhs.base()); 
    }

    template <class Iterator_L, class Iterator_R>
    bool    operator-(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) 
    { 
        return (lhs.base() - rhs.base()); 
    }

}
