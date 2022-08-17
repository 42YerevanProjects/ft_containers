#pragma once

#include <iostream>

namespace ft
{
    /*
    ===================================
        Constructors and Destructor
    ===================================
    */

    template <typename Key, typename T, typename Compare, typename Alloc>
    map<Key, T, Compare, Alloc>::map(const key_compare& comp, const allocator_type& alloc) : _tree(comp, alloc) {}

    template <typename Key, typename T, typename Compare, typename Alloc>
    template <typename InputIt>
    map<Key, T, Compare, Alloc>::map(InputIt first, InputIt last, const key_compare& comp, const allocator_type& alloc,
                                        typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type*) 
    : _tree(first, last, comp, alloc) {}

    template <typename Key, typename T, typename Compare, typename Alloc>
    map<Key, T, Compare, Alloc>::map(const map& other) : _tree(other._tree) {}

    template <typename Key, typename T, typename Compare, typename Alloc>
    map<Key, T, Compare, Alloc>&    map<Key, T, Compare, Alloc>::operator=(const map& other)
    {
        this->_tree = other._tree;
        return (*this);
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    map<Key, T, Compare, Alloc>::~map()
    {
        _tree.clear();
    }


    /*
    ==========================
        Iterator Functions
    ==========================
    */

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::iterator                          map<Key, T, Compare, Alloc>::begin() { return (_tree.begin()); }

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator                    map<Key, T, Compare, Alloc>::begin() const { return (_tree.begin()); }

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::iterator                          map<Key, T, Compare, Alloc>::end() { return (_tree.end()); }

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator                    map<Key, T, Compare, Alloc>::end() const { return (_tree.end()); }

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::reverse_iterator                  map<Key, T, Compare, Alloc>::rbegin() { return (_tree.rbegin()); }

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::const_reverse_iterator            map<Key, T, Compare, Alloc>::rbegin() const { return (_tree.rbegin()); }

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::reverse_iterator                  map<Key, T, Compare, Alloc>::rend() { return (_tree.rend()); }

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::const_reverse_iterator            map<Key, T, Compare, Alloc>::rend() const { return (_tree.rend()); }


    /*
    ==========================
        Capacity Functions
    ==========================
    */

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::size_type                         map<Key, T, Compare, Alloc>::size() const { return (_tree.size()); }

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::size_type                         map<Key, T, Compare, Alloc>::max_size() const { return (_tree.max_size()); }
 
    template <typename Key, typename T, typename Compare, typename Alloc>
    bool                                                                    map<Key, T, Compare, Alloc>::empty() const { return (_tree.empty()); }


    /*
    ================================
        Element Access Functions
    ================================
    */

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::mapped_type&                      map<Key, T, Compare, Alloc>::at(const key_type& k)
    { 
        iterator pos = _tree.find(k);

        if (pos == end())
            throw std::out_of_range("map::at");
        
        return (pos->second);
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::mapped_type&                      map<Key, T, Compare, Alloc>::operator[](const key_type& k)
    {
        if (_tree.count(k))
            return _tree.find(k)->second;

        return (_tree.insert(ft::make_pair(k, T()))->second);
    }


    /*
    ==========================
        Modifier Functions
    ==========================
    */

    template <typename Key, typename T, typename Compare, typename Alloc>
    ft::pair<typename map<Key, T, Compare, Alloc>::iterator, bool>          map<Key, T, Compare, Alloc>::insert(const value_type& val)
    {
        iterator pos;

        if (_tree.count(val.first))
        {
            pos = _tree.find(val.first);
            return (ft::make_pair(pos, false));
        }
        else
        {
            pos = _tree.insert(val);
            return (ft::make_pair(pos, true));
        }
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::iterator                          map<Key, T, Compare, Alloc>::insert(iterator position, const value_type& val)
    {
        iterator result;

        if (_tree.count(val.first))
            result = _tree.find(val.first);
        else
            result = _tree.insert(position, val);
        
        return (result);
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    template <typename InputIt>
    void        map<Key, T, Compare, Alloc>::insert(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type*)
    {
        while (first != last)
        {
            this->insert(*first);
            first++;
        }
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::size_type                          map<Key, T, Compare, Alloc>::erase(const key_type& k)
    {
        if (_tree.count(k))
        {
            _tree.erase(_tree.find(k));
            return (1);
        }
        return (0);
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    void                                                                     map<Key, T, Compare, Alloc>::erase(iterator position)
    {
        _tree.erase(position);
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    void                                                                     map<Key, T, Compare, Alloc>::erase(iterator first, iterator last)
    {
        _tree.erase(first, last);
    }

    // TODO: Have to fix the bug created by  rb_tree::swap which messeds up the erase process 
    //
    //template <typename Key, typename T, typename Compare, typename Alloc>
    //void                                                                     map<Key, T, Compare, Alloc>::swap(map& x)
    //{
    //    _tree.swap(x._tree);
    //}
 
    template <typename Key, typename T, typename Compare, typename Alloc>
    void                                                                     map<Key, T, Compare, Alloc>::clear()
    {
        _tree.clear();
    }


    /*
    ==========================
        Observer Functions
    ==========================
    */

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::key_compare                        map<Key, T, Compare, Alloc>::key_comp() const
    {
        return (_tree.key_comp());
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::value_compare                        map<Key, T, Compare, Alloc>::value_comp() const
    {
        return (value_compare(key_comp()));
    }
}
