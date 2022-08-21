#pragma once

#include <stdexcept>
#include <iostream>

namespace ft
{
    /*
    ===================================
        Constructors and Destructor
    ===================================
    */

    template <class T, class Alloc>
    vector<T, Alloc>::vector(const allocator_type& alloc) :  _alloc(alloc), _data(NULL), _size(0), _cap(0)
    {  }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(size_type n, const value_type& val, const allocator_type& alloc) : _alloc(alloc), _data(NULL)
    {
        check_size(static_cast<size_type>(n));
        _data = (n ? _alloc.allocate(n) : pointer()); 
        _size = n;
        _cap = n;
        this->fill(n, val);
    }
    
    template <class T, class Alloc>
    template<typename InputIterator>
    vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type& alloc,
    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
    {
        typename ft::iterator_traits<InputIterator>::difference_type n = ft::distance(first, last);

        _alloc = alloc;
        _data = _alloc.allocate(n);
        _size = 0;
        _cap = n;
        this->range_fill(first, last);
    }
    
    template <class T, class Alloc>
    vector<T, Alloc>::vector(const vector& other) 
    {
       _alloc = other._alloc;
       _data = 0;
       _cap = 0;
       _size = 0;
       this->range_fill(other.begin(), other.end());
    }

    template <class T, class Alloc>
    vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& other) 
    {
        if (other == *this)
            return (*this);

        clear();
        this->range_fill(other.begin(), other.end());
        return (*this);
    }

    template <class T, class Alloc>
    vector<T, Alloc>::~vector() 
    {
        this->clear();
        _alloc.deallocate(_data, _cap);
    }


    /*
    ========================== 
        Iterator Functions
    ==========================
    */
    
    template<class T, class Alloc>
    typename vector<T, Alloc>::iterator                 vector<T, Alloc>::begin() { return (this->_data); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::const_iterator           vector<T, Alloc>::begin() const { return (this->_data); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::iterator                 vector<T, Alloc>::end() { return (_data + _size); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::const_iterator           vector<T, Alloc>::end() const { return (_data + _size); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::reverse_iterator         vector<T, Alloc>::rbegin() { return reverse_iterator(this->end()); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::const_reverse_iterator   vector<T, Alloc>::rbegin() const { return const_reverse_iterator(this->end()); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::reverse_iterator         vector<T, Alloc>::rend() { return reverse_iterator(this->begin()); }

    template<class T, class Alloc>
    typename vector<T, Alloc>::const_reverse_iterator   vector<T, Alloc>::rend() const { return const_reverse_iterator(this->begin()); }


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
        else if (this->capacity() < n)
        {  
            pointer new_vct = this->deep_copy(n, _data, (_data + _size));

			for (size_type i = 0 ; i < _size && i < n ; i++)
				_alloc.destroy(_data + i);

            if (_data)
			    _alloc.deallocate(_data, _cap);

			_cap = n;
            this->_data = new_vct;
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
            this->insert(this->end(), n - this->size(), val);
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
    typename vector<T, Alloc>::reference                vector<T, Alloc>::at(size_type n) { check_range(n); return _data[n]; }

    template<class T, class Alloc> 
    typename vector<T, Alloc>::const_reference          vector<T, Alloc>::at(size_type n) const { check_range(n); return _data[n]; }

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

    /* Assignment */

    template <class T, class Alloc>
    template<typename InputIterator>
    void        vector<T, Alloc>::assign(InputIterator first, InputIterator last, 
    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
    {
        typename ft::iterator_traits<InputIterator>::difference_type n = ft::distance(first, last);

        if ((size_type) n > _cap)
            this->reserve(n);

        for (size_type i = 0; i < _size; i++)
            _alloc.destroy(_data + i);
        for (ptrdiff_t i = 0; i < n; i++)
            _alloc.construct(_data + i, *first++);
        
        _size = n;
    }

    template<class T, class Alloc> 
    void                                                vector<T, Alloc>::assign(size_type n, const value_type& val) 
    {  
        if (n > _cap)
            this->reserve(n);

        for (size_type i = 0; i < _size; i++)
            _alloc.destroy(_data + i);
        for (size_type i = 0; i < n; i++)
            _alloc.construct(_data + i, val);
        
        _size = n;
    }
    
    /* Push and Pop*/

    template<class T, class Alloc> 
    void                                                vector<T, Alloc>::push_back(const value_type& val)
    {
        if (_size + 1 > _cap)
        {
            size_type new_cap = (_size > 0) ? (2 * _size) : 1;
            this->reserve(new_cap);
        }
        _alloc.construct(_data + _size + 1,  val);
        _size++;
    }

    template<class T, class Alloc> 
    void                                                vector<T, Alloc>::pop_back()
    {
        _alloc.destroy(&this->back());
        _size--;
    }
    
    /* Insertion */

    template <class T, class Alloc>
    template<typename InputIterator>
    void        vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last, 
    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
    {
        vector<T, Alloc> temp(position, this->end());
	    this->_size -= (this->end() - position);

	    while (first != last)
	    {
		    push_back(*first);
		    ++first;
	    }

	    iterator it_begin = temp.begin();
	    iterator it_end = temp.end();
	    while (it_begin != it_end)
	    {
		    this->push_back(*it_begin);
		    ++it_begin;
	    }
    }

    template<class T, class Alloc>
    void                                                vector<T, Alloc>::insert(iterator position, size_type n, const value_type& val)
    {
        vector<T, Alloc> temp(position, this->end());
	    this->_size -= (this->end() - position);

	    for (size_type i = 0; i < n; i++)
		    this->push_back(val);

	    iterator it_begin = temp.begin();
	    iterator it_end = temp.end();
	    while (it_begin != it_end)
	    {
		    this->push_back(*it_begin);
		    ++it_begin;
	    }
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::iterator                 vector<T, Alloc>::insert(iterator position, const value_type& val)
    {
	    size_type n = (position - this->begin());
	    insert(position, 1, val);
	    return (iterator(&this->_data[n]));
    }

    /* Swapping */

    template < typename T, typename Alloc >
    void                                                vector<T, Alloc>::swap(vector& x)
    {
	    vector<T, Alloc> temp = *this;
	    *this = x;
	    x = temp;
    }

    /* Clear and Erase */
    
    template < typename T, typename Alloc >
    void                                                vector<T, Alloc>::clear()
    {
        for (size_type i = 0; i < _size; i++)
            _alloc.destroy(_data + i);
        _size = 0;
    }

    template < typename T, typename Alloc>
    typename vector<T, Alloc>::iterator                 vector<T, Alloc>::erase(iterator position)
    {
        for (size_type i = position - this->begin(); i < _size - 1; i++)
			_data[i] = _data[i + 1];

		_size--;
		_alloc.destroy(_data + _size);

		return (position);
    }

    template < typename T, typename Alloc>
    typename vector<T, Alloc>::iterator                 vector<T, Alloc>::erase(iterator first, iterator last)
    {
        size_t n = last - first;

        while (n-- > 0)
            this->erase(first);

        return (first);
    }


    /*
    ======================== 
        Allocator Object
    ========================
    */

    template < typename T, typename Alloc>
    typename vector<T, Alloc>::allocator_type          vector<T, Alloc>::get_allocator() const { return this->_alloc;; }


    /*
    ============================ 
        Non-Member Functions
    ============================ 
    */

    template <class T, class Alloc>
    bool    operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <class T, class Alloc>
    bool    operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <class T, class Alloc>
    bool    operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) 
    { 
        return (!(lhs == rhs)); 
    }

    template <class T, class Alloc>
    bool    operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    { 
        return (!(rhs < lhs)); 
    }

    template <class T, class Alloc>
    bool    operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    { 
        return (rhs < lhs);
    }

	template <class T, class Alloc>
    bool    operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(lhs < rhs));
    }

    template <class T, class Alloc>
    void    swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
    {
        vector<T, Alloc>    temp = x;
        x = y;
        y = temp;
    }


    /*
    ====================== 
        Util Functions
    ====================== 
    */

    template<class T, class Alloc> 
    template<typename InputIterator> 
    void                                                vector<T, Alloc>::range_fill(InputIterator first, InputIterator last)
    {
        try
        {
            for (; first != last; ++first)
                this->push_back(*first);
        }
        catch (...)
        {
            this->clear();
            throw ;
        }
    }

    template<class T, class Alloc> 
    template<typename InputIterator> 
    typename vector<T, Alloc>::pointer                  vector<T, Alloc>::deep_copy(size_type n, InputIterator first, InputIterator last)
    {
        std::cout << "why god" << std::endl;
        pointer     copy = (n ? _alloc.allocate(n) : pointer());
        size_type   i;

        try
        {
            for (i = 0; (first != last and i < n); first++, i++)
                _alloc.construct(copy + i, *first);

            return (copy);
        }
        catch(...)
        { 
            for (size_type j = 0; j < i; j++)
                _alloc.destroy(copy + j);
            _alloc.deallocate(copy, n);

            throw ;
        }
    }

    template<class T, class Alloc> 
    void                                                vector<T, Alloc>::fill(size_type n, const value_type& val)
    {
        size_type i;
        try
        {
            for (i = 0; i < n; i++)
                _alloc.construct(_data + i, val);
        }
        catch(...)
        {
            for (size_type j = 0; j < i; j++)
                _alloc.destroy(_data + j);
            throw ;
        }
    }

    template<class T, class Alloc> 
    void                                                vector<T, Alloc>::check_range(size_type n) const
    {
        if (n >= _size)
            throw std::out_of_range("vector::at: n (which is " 
                    + ft::to_string(n) 
                    + ") >= this->size() (which is " 
                    + ft::to_string(this->_size) + ")");
    }

    template<class T, class Alloc> 
    typename vector<T, Alloc>::size_type                vector<T, Alloc>::check_size(size_type n) const
    {
        if (max_size() - this->_size < n)
            throw std::length_error("vector::vector");
		
        size_type	new_size;

        if (this->_size > n)
            new_size = 2 * this->_size;
        else
            new_size = n + this->_size;

        // in case of overflow
        return ((new_size > max_size()) ? max_size() : new_size);
    }
}
