#pragma once

#include <memory>
#include <stdexcept>

namespace ft
{

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
    vector<T, Alloc>::~vector() 
    {
        for (size_t i = 0; i < _size; i++)
            _alloc.destroy(_data + i);
        _alloc.deallocate(_data, _cap);
    }


    /*
    ========================== 
        Iterator Functions
    ==========================
    */
    
    template<class T, class Alloc>
    typename vector<T, Alloc>::iterator                 vector<T, Alloc>::begin() { return (iterator(_data)); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::iterator                 vector<T, Alloc>::end() { return (iterator(_data + _size)); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::reverse_iterator         vector<T, Alloc>::rbegin() { return (reverse_iterator(this->end())); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::reverse_iterator         vector<T, Alloc>::rend() { return (reverse_iterator(this->begin())); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::const_iterator           vector<T, Alloc>::begin() const { return (iterator(_data)); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::const_iterator           vector<T, Alloc>::end() const { return (iterator(_data + _size)); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::const_reverse_iterator   vector<T, Alloc>::rbegin() const { return (reverse_iterator(this->end())); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::const_reverse_iterator   vector<T, Alloc>::rend() const { return (reverse_iterator(this->begin())); }

    /*
    ========================== 
        Capacity Functions
    ==========================
    */

    template<class T, class Alloc>
    typename vector<T, Alloc>::size_type                vector<T, Alloc>::size() const { return (this->_size); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::size_type                vector<T, Alloc>::max_size() const { return (_alloc.max_size()); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::size_type                vector<T, Alloc>::capacity() const { return (this->_cap); }

    template<class T, class Alloc>
    bool                                                vector<T, Alloc>::empty() const { return (this->_size == 0); }

    template<class T, class Alloc>
    void                                                vector<T, Alloc>::reserve(size_type n) 
    {
        if (n > this->max_size())
            throw std::length_error("vector::reserve");
        else if (n > this->capacity())
        {   
            pointer temp_data = _alloc.allocate(n);

            for (size_t i = 0; i < _size && i < n; i++)
            {
                _alloc.construct(temp_data + i, *(_data + i));
                _alloc.destroy(_data + i);
            }
            _alloc.deallocate(_data, _cap);

            _cap = n;
            _data = temp_data;
        }
    }

    template<class T, class Alloc> 
    void                                                vector<T, Alloc>::resize(size_type n, value_type val)
    {
        if (n > this->max_size())
            throw std::length_error("vector::resize");
        else if (n < _size)
        {
            while (_size > n)
            {
                _size--;
                _alloc.destroy(_data + _size);
            }
        }
        else
            return;// insert n - _size elements at the end: After I implement insert function
    }

    /*
    ================================ 
        Element Access Functions
    ================================
    */

    template<class T, class Alloc> 
    typename vector<T, Alloc>::reference                vector<T, Alloc>::operator[](size_type n) { return *(_data + n); }

    template<class T, class Alloc> 
    typename vector<T, Alloc>::const_reference          vector<T, Alloc>::operator[](size_type n) const { return *(_data + n); }

    template<class T, class Alloc> 
    typename vector<T, Alloc>::reference                vector<T, Alloc>::at(size_type n) 
    { 
        if (n >= _size)
            throw std::out_of_range("vector::_M_range_check: __n (which is " + std::to_string(n) + ") >= this->size() (which is " + std::to_string(_size) + ")");

        return _data[n];
    }

    template<class T, class Alloc> 
    typename vector<T, Alloc>::const_reference          vector<T, Alloc>::at(size_type n) const 
    { 
        if (n >= _size)
            throw std::out_of_range("vector::_M_range_check: __n (which is " + std::to_string(n) + ") >= this->size() (which is " + std::to_string(_size) + ")");

        return _data[n];
    }

    template<class T, class Alloc> 
    typename vector<T, Alloc>::reference                vector<T, Alloc>::front() { return _data[0]; } 

    template<class T, class Alloc> 
    typename vector<T, Alloc>::reference                vector<T, Alloc>::back() { return _data[_size - 1]; } 

    template<class T, class Alloc> 
    typename vector<T, Alloc>::const_reference          vector<T, Alloc>::front() const { return _data[0]; } 

    template<class T, class Alloc> 
    typename vector<T, Alloc>::const_reference          vector<T, Alloc>::back() const { return _data[_size - 1]; } 

    /*
    ========================== 
        Modifier Functions
    ========================== 
    */

    template <class T, class Alloc>
    template<typename InputIterator>
    void                                                vector<T, Alloc>::assign(InputIterator first, InputIterator last, 
                                                                                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
    {
        if (!ft::is_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value)
            throw (ft::InvalidIteratorException<typename ft::is_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::type>());

        typename ft::iterator_traits<InputIterator>::difference_type n = ft::distance(first, last);

        if (n > _cap)
            this->reserve(n);

        for (size_t i = 0; i < _size; i++)
            _alloc.destroy(_data + i);
        for (size_t = 0; i < n; i++)
            _alloc.construct(_data + i, *first++);
        
        _size = n;
    }

    template<class T, class Alloc> 
    void                                                vector<T, Alloc>::assign(size_type n, value_type& val) 
    {  
        if (n > _cap)
            this->reserve(n);

        for (size_t i = 0; i < _size; i++)
            _alloc.destroy(_data + i);
        for (size_t = 0; i < n; i++)
            _alloc.construct(_data + i, val);
        
        _size = n;
    }


}
