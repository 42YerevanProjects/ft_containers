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
    vector<T, Alloc>::vector(const allocator_type& alloc) :  _alloc(alloc), _vct(NULL), _size(0), _cap(0)
    { 

    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(size_type n, const value_type& val, const allocator_type& alloc) : _alloc(alloc)
    {
        check_size(static_cast<size_type>(n));
        _vct = (n ? _alloc.allocate(n) : pointer()); 
        _size = n;
        _cap = n;
        this->fill(n, val, _vct);
    }
    
    template <class T, class Alloc>
    template<typename InputIterator>
    vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type& alloc,
    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
    {
        difference_type n = ft::distance(first, last);

        _alloc = alloc;
        _vct = _alloc.allocate(n);
        _size = 0;
        _cap = n;
        this->range_fill(first, last);
    }
    
    template <class T, class Alloc>
    vector<T, Alloc>::vector(const vector& other) 
    {
       this->_alloc = other._alloc;
       this->_size = 0;
       this->_cap = other._cap;
       this->_vct = _alloc.allocate(_cap);
       this->range_fill(other.begin(), other.end());
    }

    template <class T, class Alloc>
    vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& other) 
    {
        if (this != &other)
        {
            this->clear();

            if (other._size > _cap)
            {
                _alloc.deallocate(_vct, _cap);
                _cap = other._size;
                _vct = _alloc.allocate(_cap);
            }
            
            _size = 0;
            this->range_fill(other.begin(), other.end());
        }

        return (*this);
    }

    template <class T, class Alloc>
    vector<T, Alloc>::~vector() 
    {
        this->clear();

        if (_vct)
            _alloc.deallocate(_vct, _cap);
    }


    /*
    ========================== 
        Iterator Functions
    ==========================
    */
    
    template<class T, class Alloc>
    typename vector<T, Alloc>::iterator                 vector<T, Alloc>::begin()
    { 
        return iterator(this->_vct); 
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::const_iterator           vector<T, Alloc>::begin() const
    { 
        return const_iterator(this->_vct);
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::iterator                 vector<T, Alloc>::end() 
    {
        return iterator(_vct + _size);
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::const_iterator           vector<T, Alloc>::end() const
    {
        return const_iterator(_vct + _size);
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::reverse_iterator         vector<T, Alloc>::rbegin()
    {
        return reverse_iterator(this->end());
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::const_reverse_iterator   vector<T, Alloc>::rbegin() const
    {
        return const_reverse_iterator(this->end());
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::reverse_iterator         vector<T, Alloc>::rend()
    {
        return reverse_iterator(this->begin());
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::const_reverse_iterator   vector<T, Alloc>::rend() const
    {
        return const_reverse_iterator(this->begin());
    }


    /*
    ========================== 
        Capacity Functions
    ==========================
    */

    template<class T, class Alloc>
    typename vector<T, Alloc>::size_type                vector<T, Alloc>::size() const
    {
        return (this->_size);
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::size_type                vector<T, Alloc>::max_size() const
    {
        return (this->_alloc.max_size());
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::size_type                vector<T, Alloc>::capacity() const
    {
        return (this->_cap);
    }

    template<class T, class Alloc>
    bool                                                vector<T, Alloc>::empty() const
    {
        return (this->_size == 0);
    }

    template<class T, class Alloc>
    void                                                vector<T, Alloc>::reserve(size_type n) 
    {
        if (n > this->max_size())
            throw std::length_error("vector::reserve");
        else if (this->capacity() < n)
        {
            pointer new_vct = this->deep_copy(n, _vct, (_vct + _size));

            for (size_type i = 0 ; i < _size && i < n ; i++)
                _alloc.destroy(_vct + i);

            if (_vct)
                _alloc.deallocate(_vct, _cap);

            _cap = n;
            this->_vct = new_vct;
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
                _alloc.destroy(_vct + _size);
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
    typename vector<T, Alloc>::reference                vector<T, Alloc>::operator[](size_type n)
    {
        return _vct[n];
    }

    template<class T, class Alloc> 
    typename vector<T, Alloc>::const_reference          vector<T, Alloc>::operator[](size_type n) const
    {
        return _vct[n];
    }

    template<class T, class Alloc> 
    typename vector<T, Alloc>::reference                vector<T, Alloc>::at(size_type n)
    {
        check_range(n);
        return _vct[n];
    }

    template<class T, class Alloc> 
    typename vector<T, Alloc>::const_reference          vector<T, Alloc>::at(size_type n) const
    {
        check_range(n);
        return _vct[n];
    }

    template<class T, class Alloc> 
    typename vector<T, Alloc>::reference                vector<T, Alloc>::front()
    {
        return _vct[0];
    } 

    template<class T, class Alloc> 
    typename vector<T, Alloc>::reference                vector<T, Alloc>::back()
    {
        return _vct[_size - 1];
    }  

    template<class T, class Alloc> 
    typename vector<T, Alloc>::const_reference          vector<T, Alloc>::front() const
    {
        return _vct[0];
    } 

    template<class T, class Alloc> 
    typename vector<T, Alloc>::const_reference          vector<T, Alloc>::back() const
    {
        return _vct[_size - 1];
    } 


    /*
    ========================== 
        Modifier Functions
    ========================== 
    */

    /* Assignment */

    template <class T, class Alloc>
    template<typename InputIterator>
    void    vector<T, Alloc>::assign(InputIterator first, InputIterator last, 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
    {
        difference_type n = ft::distance(first, last);

        if ((size_type) n > _cap)
            this->reserve(n);

        for (size_type i = 0; i < _size; i++)
            _alloc.destroy(_vct + i);

        for (difference_type i = 0; i < n; i++)
            _alloc.construct(_vct + i, *first++);
        
        _size = n;
    }

    template<class T, class Alloc> 
    void                                                vector<T, Alloc>::assign(size_type n, const value_type& val) 
    {  
        if (n > _cap)
        {
            vector temp_vct(n, val, this->_alloc);
            this->swap(temp_vct);
        }
        else if (n > _size)
        {
            for (size_type i = 0; i < _size; i++)
                _vct[i] = val;

            this->fill((n - _size), val, (_vct + _size));
        }
        else
        {
            for (size_type i = 0; i < n; i++)
                _vct[i] = val;

            for (size_type i = n; i < _size; i++)
                _alloc.destroy(_vct + i);
        }

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
        _alloc.construct(_vct + _size,  val);
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
    void    vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last, 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
    {
        if (position < begin() || position > end())
            throw std::logic_error("vector::insert");
        
        size_type start = static_cast<size_type>(position - begin());
        size_type n = static_cast<size_type>(ft::distance(first, last));
        if (_size + n > _cap)
        {
            size_type cap = _cap * 2 >= _size + n ? _cap * 2 : _size + n;
            pointer arr = _alloc.allocate(cap);
            std::uninitialized_copy(begin(), position, arr);
            try 
            {
                for (size_type i = 0; i < static_cast<size_type>(n); i++, first++)
                    _alloc.construct(arr + start + i, *first);
            } catch (...) 
            {
                for (size_type i = 0; i < n + start; ++i)
                    _alloc.destroy(arr + i);

                _alloc.deallocate(arr, cap);
                throw;
            }

            std::uninitialized_copy(position, end(), (arr + start + n));
            for (size_type i = 0; i < _size; i++)
                _alloc.destroy(_vct + i);

            _alloc.deallocate(_vct, _cap);
            _size += n;
            _cap = cap;
            _vct = arr;
        }
        else
        {
            for (size_type i = _size; i > static_cast<size_type>(start); i--)
            {
                _alloc.destroy(_vct + i + n - 1);
                _alloc.construct(_vct + i + n - 1, *(_vct + i - 1));
            }
            for (size_type i = 0; i < static_cast<size_type>(n); i++, first++)
            {
                _alloc.destroy(_vct + i + n);
                _alloc.construct(_vct + start + i, *first);
            }
            _size += n;
        }
    }

    template<class T, class Alloc>
    void                                                vector<T, Alloc>::insert(iterator position, size_type n, const value_type& val)
    {
        if (n == 0)
            return ;
        else if (max_size() - _size < n)
            throw std::length_error("vector::insert");
        
        difference_type start = position - begin();
        if (_size + n > _cap)
        {
            size_type cap = _cap * 2 >= _size + n ? _cap * 2 : _size + n;
            pointer arr = _alloc.allocate(cap);
            std::uninitialized_copy(begin(), position, arr);
            
            for (size_type i = 0; i < n; i++)
                _alloc.construct(arr + start + i, val);

            std::uninitialized_copy(position, end(), (arr + start + n));
            for (size_type i = 0; i < _size; i++)
                _alloc.destroy(_vct + i);
            
            _alloc.deallocate(_vct, _cap);
            _size += n;
            _cap = cap;
            _vct = arr;
        }
        else
        {
            for (size_type i = _size; i > static_cast<size_type>(start); i--)
            {
                _alloc.destroy(_vct + i + n - 1);
                _alloc.construct(_vct + i + n - 1, *(_vct + i - 1));
            }
            for (size_type i = 0; i < n; i++)
            {
                _alloc.destroy(_vct + i + start);
                _alloc.construct(_vct + i + start, val);
            }
            _size += n;
        }
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::iterator                 vector<T, Alloc>::insert(iterator position, const value_type& val)
    {
        if (position < begin() || position > end())
            throw std::logic_error("vector::insert");
        
        difference_type start = position - begin();
        if (_size == _cap)
        {
            _cap = _cap * 2 + (_cap == 0);
            pointer arr = _alloc.allocate(_cap);
            std::uninitialized_copy(begin(), position, arr);
            _alloc.construct(arr + start, val);
            std::uninitialized_copy(position, end(), arr + start + 1);
            
            for (size_type i = 0; i < _size; i++)
                _alloc.destroy(_vct + i);
            if (_size)
                _alloc.deallocate(_vct, _size);
            _size++;
            _vct = arr;
        }
        else
        {
            for (size_type i = _size; i > static_cast<size_type >(start); i--)
            {
                _alloc.destroy(_vct + i);
                _alloc.construct(_vct + i, *(_vct + i - 1));
            }
            _alloc.destroy(&(*position));
            _alloc.construct(&(*position), val);
            _size++;
        }

        return (begin() + start);
    }

    /* Swapping */

    template < typename T, typename Alloc >
    void                                                vector<T, Alloc>::swap(vector& x)
    {
        ft::swap(this->_vct, x._vct);
        ft::swap(this->_alloc, x._alloc);
        ft::swap(this->_size, x._size);
        ft::swap(this->_cap, x._cap);
    }

    /* Clear and Erase */
    
    template < typename T, typename Alloc >
    void                                                vector<T, Alloc>::clear()
    {
        for (size_type i = 0; i < _size; i++)
            _alloc.destroy(_vct + i);
        _size = 0;
    }

    template < typename T, typename Alloc>
    typename vector<T, Alloc>::iterator                 vector<T, Alloc>::erase(iterator position)
    {
        for (size_type i = position - this->begin(); i < _size - 1; i++)
            _vct[i] = _vct[i + 1];

        _size--;
        _alloc.destroy(_vct + _size);

        return (position);
    }

    template < typename T, typename Alloc>
    typename vector<T, Alloc>::iterator                 vector<T, Alloc>::erase(iterator first, iterator last)
    {
        difference_type left = ft::distance(begin(), first);
        difference_type right = ft::distance(last, end());

        for (; first != last; first++)
            _alloc.destroy(&(*first));
        
        size_type i = left;
        while (last < end())
        {
            if (this->_vct + left)
                _alloc.destroy(_vct + i);

            _alloc.construct(_vct + i, *last);
            i++;
            last++;
        }
        
        for (size_type i = left + right; i < _size; i++)
            _alloc.destroy(_vct + i);
        _size = left + right;
        
        return (last == end()) ? end() : iterator(_vct + left);
    }


    /*
    ======================== 
        Allocator Object
    ========================
    */

    template < typename T, typename Alloc>
    typename vector<T, Alloc>::allocator_type          vector<T, Alloc>::get_allocator() const
    {
        return this->_alloc;
    }


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
        x.swap(y);
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
    void                                                vector<T, Alloc>::fill(size_type n, const value_type& val, pointer start)
    {
        size_type i;
        try
        {
            for (i = 0; i < n; i++)
                _alloc.construct(start + i, val);
        }
        catch(...)
        {
            for (size_type j = 0; j < i; j++)
                _alloc.destroy(start + j);
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
