#pragma once

#include <cstdint>
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
        std::cout << "done\n";
    }
    
    template <class T, class Alloc>
    vector<T, Alloc>::~vector() {}
}
