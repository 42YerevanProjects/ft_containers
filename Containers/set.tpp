#pragma once


namespace ft
{
    /*
    ===================================
        Constructors and Destructor
    ===================================
    */

    template <typename Key, typename Compare, typename Alloc>
    set<Key, Compare, Alloc>::set(const key_compare& comp, const allocator_type& alloc) : _tree(comp, alloc) {}

    template <typename Key, typename Compare, typename Alloc>
    template <typename InputIt>
    set<Key, Compare, Alloc>::set(InputIt first, InputIt last, const key_compare& comp, const allocator_type& alloc,
                                        typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type*)
    : _tree(first, last, comp, alloc) {}

    template <typename Key, typename Compare, typename Alloc>
    set<Key, Compare, Alloc>::set(const set& other) : _tree(other._tree) {}

    template <typename Key, typename Compare, typename Alloc>
    set<Key, Compare, Alloc>&    set<Key, Compare, Alloc>::operator=(const set& other)
    {
        this->_tree = other._tree;
        return (*this);
    }

    template <typename Key, typename Compare, typename Alloc>
    set<Key, Compare, Alloc>::~set()
    {
        _tree.clear();
    }

    /*
    ==========================
        Iterator Functions
    ==========================
    */

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::iterator                          set<Key, Compare, Alloc>::begin() { return (_tree.begin()); }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::const_iterator                    set<Key, Compare, Alloc>::begin() const { return (_tree.begin()); }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::iterator                          set<Key, Compare, Alloc>::end() { return (_tree.end()); }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::const_iterator                    set<Key, Compare, Alloc>::end() const { return (_tree.end()); }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::reverse_iterator                  set<Key, Compare, Alloc>::rbegin() { return (_tree.rbegin()); }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::const_reverse_iterator            set<Key, Compare, Alloc>::rbegin() const { return (_tree.rbegin()); }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::reverse_iterator                  set<Key, Compare, Alloc>::rend() { return (_tree.rend()); }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::const_reverse_iterator            set<Key, Compare, Alloc>::rend() const { return (_tree.rend()); }


    /*
    ==========================
        Capacity Functions
    ==========================
    */

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::size_type                         set<Key, Compare, Alloc>::size() const { return (_tree.size()); }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::size_type                         set<Key, Compare, Alloc>::max_size() const { return (_tree.max_size()); }
 
    template <typename Key, typename Compare, typename Alloc>
    bool                                                                 set<Key, Compare, Alloc>::empty() const { return (_tree.empty()); }


    /*
    ==========================
        Modifier Functions
    ==========================
    */

    template <typename Key, typename Compare, typename Alloc>
    ft::pair<typename set<Key, Compare, Alloc>::iterator, bool>          set<Key, Compare, Alloc>::insert(const value_type& val)
    {
        iterator pos;

        if (_tree.count(val))
        {
            pos = _tree.find(val);
            return (ft::make_pair(pos, false));
        }
        else
        {
            pos = _tree.insert(val);
            return (ft::make_pair(pos, true));
        }
    }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::iterator                       set<Key, Compare, Alloc>::insert(iterator position, const value_type& val)
    {
        iterator result;

        if (_tree.count(val))
            result = _tree.find(val);
        else
            result = _tree.insert(position, val);
        
        return (result);
    }

    template <typename Key, typename Compare, typename Alloc>
    template <typename InputIt>
    void        set<Key, Compare, Alloc>::insert(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type*)
    {
        while (first != last)
        {
            this->insert(*first);
            first++;
        }
    }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::size_type                         set<Key, Compare, Alloc>::erase(const key_type& k)
    {
        if (_tree.count(k))
        {
            _tree.erase(_tree.find(k));
            return (1);
        }
        return (0);
    }

    template <typename Key, typename Compare, typename Alloc>
    void                                                                 set<Key, Compare, Alloc>::erase(iterator position)
    {
        _tree.erase(position);
    }

    template <typename Key, typename Compare, typename Alloc>
    void                                                                 set<Key, Compare, Alloc>::erase(iterator first, iterator last)
    {
        _tree.erase(first, last);
    }

    template <typename Key, typename Compare, typename Alloc>
    void                                                                 set<Key, Compare, Alloc>::swap(set& x)
    {
        _tree.swap(x._tree);
    }
 
    template <typename Key, typename Compare, typename Alloc>
    void                                                                 set<Key, Compare, Alloc>::clear()
    {
        _tree.clear();
    }


    /*
    ==========================
        Observer Functions
    ==========================
    */

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::key_compare                       set<Key, Compare, Alloc>::key_comp() const
    {
        return (_tree.key_comp());
    }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::key_compare                       set<Key, Compare, Alloc>::value_comp() const
    {
        return (_tree.key_comp());
    }


    /*
    =================================
        Lookup Operator Functions
    =================================
    */
    
    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::iterator                          set<Key, Compare, Alloc>::find(const key_type& k)
    {
        return (_tree.find(k));
    }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::const_iterator                    set<Key, Compare, Alloc>::find(const key_type& k) const
    {
        return (_tree.find(k));
    }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::size_type                         set<Key, Compare, Alloc>::count(const key_type& k) const
    {
        return (_tree.count(k));
    }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::iterator                          set<Key, Compare, Alloc>::lower_bound(const key_type& k)
    {
        return (_tree.lower_bound(k));
    }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::const_iterator                    set<Key, Compare, Alloc>::lower_bound(const key_type& k) const
    {
        return (_tree.lower_bound(k));
    }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::iterator                          set<Key, Compare, Alloc>::upper_bound(const key_type& k)
    {
        return (_tree.upper_bound(k));
    }

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::const_iterator                    set<Key, Compare, Alloc>::upper_bound(const key_type& k) const
    {
        return (_tree.upper_bound(k));
    }

    template <typename Key, typename Compare, typename Alloc>
    ft::pair<typename set<Key, Compare, Alloc>::iterator, typename set<Key, Compare, Alloc>::iterator>              set<Key, Compare, Alloc>::equal_range(const key_type& k)
    {
        return _tree.equal_range(k);
    }
    
    template <typename Key, typename Compare, typename Alloc>
    ft::pair<typename set<Key, Compare, Alloc>::const_iterator, typename set<Key, Compare, Alloc>::const_iterator>  set<Key, Compare, Alloc>::equal_range(const key_type& k) const
    {
        return _tree.equal_range(k);
    }


    /*
    =============================
        Allocator Object Copy
    =============================
    */

    template <typename Key, typename Compare, typename Alloc>
    typename set<Key, Compare, Alloc>::allocator_type                    set<Key, Compare, Alloc>::get_allocator() const
    {
        return (_tree.get_allocator());
    }


    /*
    =====================================
        Non-Member Operator Overloads
    =====================================
    */

    template <typename Key, typename Compare, typename Alloc>
    bool    operator==(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
    {
        return (lhs._tree == rhs._tree);
    }

    template <typename Key, typename Compare, typename Alloc>
    bool    operator<(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
    {
        return (lhs._tree < rhs._tree);
    }

    template <typename Key, typename Compare, typename Alloc>
    bool    operator!=(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
    {
        return (!(lhs == rhs));
    }
	
    template <typename Key, typename Compare, typename Alloc>
    bool    operator<=(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
    {
        return (!(rhs < lhs));
    }

    template <typename Key, typename Compare, typename Alloc>
    bool    operator>(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
    {
        return (rhs < lhs);
    }

    template <typename Key, typename Compare, typename Alloc>
    bool    operator>=(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
    {
        return (!(lhs < rhs));
    }

    template <typename Key, typename Compare, typename Alloc>
    void    swap(set<Key, Compare, Alloc> &lhs, set<Key, Compare, Alloc> &rhs)
    {
        lhs.swap(rhs);
    }
}
