#pragma once

#include <memory>
#include <iostream>

namespace ft{

    /*
    ===================================
        Constructors and Destructor
    ===================================
    */

    template <class T, class Alloc>
    vector<T, Alloc>::vector(const allocator_type& alloc)
    {
        _alloc = alloc;
        _data = _alloc.allocate(0);
        _size = 0;
        _cap = 0;
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(size_t n, const value_type& val, const allocator_type& alloc)
    {
        _alloc = alloc;
        _data = _alloc.allocate(n);
        _size = n;
        _cap = n;

        for (size_type i = 0; i < n; i++)
            _alloc.construct(_data + i, val);
    }
    
    template <class T, class Alloc>
    template<typename InputIterator>
    vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type& alloc,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
    {
        _alloc = alloc;
        if (!ft::is_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value)
            throw (ft::InvalidIteratorException<typename ft::is_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::type>());
        
        typename ft::iterator_traits<InputIterator>::difference_type n = ft::distance(first, last);
        _data = _alloc.allocate(n);
        _size = n;
        _cap = n;

        for (size_t i = 0; i < n; i++)
            _alloc.construct(_data + i, *first++);

    }
    
    template <class T, class Alloc>
    vector<T, Alloc>::vector(const vector& other) 
    {
       // To be implemented after I implement insert function 
    }

    template <class T, class Alloc>
    vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& other) 
    {
       // To be implemented after I implement insert function 
    }

    template <class T, class Alloc>
    vector<T, Alloc>::~vector() {}


    /*
    ========================= 
        Iterator Functions
    =========================
    */
    
    template<class T, class Alloc>
    typename ft::vector<T, Alloc>::iterator                 vector<T, Alloc>::begin() { return (iterator(_data)); }

    template<class T, class Alloc>
    typename ft::vector<T, Alloc>::iterator                 vector<T, Alloc>::end() { return (iterator(_data + _size)); }

    template<class T, class Alloc>
    typename ft::vector<T, Alloc>::reverse_iterator         vector<T, Alloc>::rbegin() { return (reverse_iterator(this->end())); }

    template<class T, class Alloc>
    typename ft::vector<T, Alloc>::reverse_iterator         vector<T, Alloc>::rend() { return (reverse_iterator(this->begin())); }

    template<class T, class Alloc>
    typename ft::vector<T, Alloc>::const_iterator           vector<T, Alloc>::begin() const { return (iterator(_data)); }

    template<class T, class Alloc>
    typename ft::vector<T, Alloc>::iterator                 vector<T, Alloc>::end() const { return (iterator(_data + _size)); }

    template<class T, class Alloc>
    typename ft::vector<T, Alloc>::const_reverse_iterator   vector<T, Alloc>::rbegin() const { return (reverse_iterator(this->end())); }

    template<class T, class Alloc>
    typename ft::vector<T, Alloc>::reverse_iterator         vector<T, Alloc>::rend() const { return (reverse_iterator(this->begin())); }

}
