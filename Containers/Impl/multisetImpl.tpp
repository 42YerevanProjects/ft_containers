#pragma once


namespace ft
{
    /*
    ===================================
        Constructors and Destructor
    ===================================
    */

    template <typename Key, typename Compare, typename Alloc>
    multiset<Key, Compare, Alloc>::multiset(const key_compare& comp, const allocator_type& alloc) : _tree(comp, alloc) {}

    template <typename Key, typename Compare, typename Alloc>
    template <typename InputIt>
    multiset<Key, Compare, Alloc>::multiset(InputIt first, InputIt last, const key_compare& comp, const allocator_type& alloc,
                                        typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type*)
    : _tree(comp, alloc)
    {
        this->insert(first, last);
    }

    template <typename Key, typename Compare, typename Alloc>
    multiset<Key, Compare, Alloc>::multiset(const multiset& other) : _tree(other._tree) {}

    template <typename Key, typename Compare, typename Alloc>
    multiset<Key, Compare, Alloc>&    multiset<Key, Compare, Alloc>::operator=(const multiset& other)
    {
        this->_tree = other._tree;
        return (*this);
    }

    template <typename Key, typename Compare, typename Alloc>
    multiset<Key, Compare, Alloc>::~multiset()
    {
        _tree.clear();
    }

    /*
    ==========================
        Iterator Functions
    ==========================
    */

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::iterator                          multiset<Key, Compare, Alloc>::begin() { return (_tree.begin()); }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::const_iterator                    multiset<Key, Compare, Alloc>::begin() const { return (_tree.begin()); }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::iterator                          multiset<Key, Compare, Alloc>::end() { return (_tree.end()); }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::const_iterator                    multiset<Key, Compare, Alloc>::end() const { return (_tree.end()); }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::reverse_iterator                  multiset<Key, Compare, Alloc>::rbegin() { return (_tree.rbegin()); }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::const_reverse_iterator            multiset<Key, Compare, Alloc>::rbegin() const { return (_tree.rbegin()); }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::reverse_iterator                  multiset<Key, Compare, Alloc>::rend() { return (_tree.rend()); }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::const_reverse_iterator            multiset<Key, Compare, Alloc>::rend() const { return (_tree.rend()); }


    /*
    ==========================
        Capacity Functions
    ==========================
    */

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::size_type                         multiset<Key, Compare, Alloc>::size() const { return (_tree.size()); }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::size_type                         multiset<Key, Compare, Alloc>::max_size() const { return (_tree.max_size()); }
 
    template <typename Key, typename Compare, typename Alloc>
    bool                                                                 multiset<Key, Compare, Alloc>::empty() const { return (_tree.empty()); }


    /*
    ==========================
        Modifier Functions
    ==========================
    */

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::iterator                     multiset<Key, Compare, Alloc>::insert(const value_type& val)
    {
        return (_tree.insert(val));
    }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::iterator                       multiset<Key, Compare, Alloc>::insert(iterator position, const value_type& val)
    {
        return (_tree.insert(position, val));
    }

    template <typename Key, typename Compare, typename Alloc>
    template <typename InputIt>
    void        multiset<Key, Compare, Alloc>::insert(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type*)
    {
        while (first != last)
        {
            this->insert(*first);
            first++;
        }
    }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::size_type                         multiset<Key, Compare, Alloc>::erase(const key_type& k)
    {
        if (_tree.count(k))
        {
            _tree.erase(_tree.find(k));
            return (1);
        }
        return (0);
    }

    template <typename Key, typename Compare, typename Alloc>
    void                                                                 multiset<Key, Compare, Alloc>::erase(iterator position)
    {
        _tree.erase(position);
    }

    template <typename Key, typename Compare, typename Alloc>
    void                                                                 multiset<Key, Compare, Alloc>::erase(iterator first, iterator last)
    {
        _tree.erase(first, last);
    }

    template <typename Key, typename Compare, typename Alloc>
    void                                                                 multiset<Key, Compare, Alloc>::swap(multiset& x)
    {
        _tree.swap(x._tree);
    }
 
    template <typename Key, typename Compare, typename Alloc>
    void                                                                 multiset<Key, Compare, Alloc>::clear()
    {
        _tree.clear();
    }


    /*
    ==========================
        Observer Functions
    ==========================
    */

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::key_compare                       multiset<Key, Compare, Alloc>::key_comp() const
    {
        return (_tree.key_comp());
    }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::key_compare                       multiset<Key, Compare, Alloc>::value_comp() const
    {
        return (_tree.key_comp());
    }


    /*
    =================================
        Lookup Operator Functions
    =================================
    */
    
    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::iterator                          multiset<Key, Compare, Alloc>::find(const key_type& k)
    {
        return (_tree.find(k));
    }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::const_iterator                    multiset<Key, Compare, Alloc>::find(const key_type& k) const
    {
        return (_tree.find(k));
    }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::size_type                         multiset<Key, Compare, Alloc>::count(const key_type& k) const
    {
        return (_tree.count(k));
    }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::iterator                          multiset<Key, Compare, Alloc>::lower_bound(const key_type& k)
    {
        return (_tree.lower_bound(k));
    }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::const_iterator                    multiset<Key, Compare, Alloc>::lower_bound(const key_type& k) const
    {
        return (_tree.lower_bound(k));
    }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::iterator                          multiset<Key, Compare, Alloc>::upper_bound(const key_type& k)
    {
        return (_tree.upper_bound(k));
    }

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::const_iterator                    multiset<Key, Compare, Alloc>::upper_bound(const key_type& k) const
    {
        return (_tree.upper_bound(k));
    }

    template <typename Key, typename Compare, typename Alloc>
    ft::pair<typename multiset<Key, Compare, Alloc>::iterator, typename multiset<Key, Compare, Alloc>::iterator>              multiset<Key, Compare, Alloc>::equal_range(const key_type& k)
    {
        return _tree.equal_range(k);
    }
    
    template <typename Key, typename Compare, typename Alloc>
    ft::pair<typename multiset<Key, Compare, Alloc>::const_iterator, typename multiset<Key, Compare, Alloc>::const_iterator>  multiset<Key, Compare, Alloc>::equal_range(const key_type& k) const
    {
        return _tree.equal_range(k);
    }


    /*
    =============================
        Allocator Object Copy
    =============================
    */

    template <typename Key, typename Compare, typename Alloc>
    typename multiset<Key, Compare, Alloc>::allocator_type                    multiset<Key, Compare, Alloc>::get_allocator() const
    {
        return (_tree.get_allocator());
    }


    /*
    =====================================
        Non-Member Operator Overloads
    =====================================
    */

    template <typename Key, typename Compare, typename Alloc>
    bool    operator==(const multiset<Key, Compare, Alloc> &lhs, const multiset<Key, Compare, Alloc> &rhs)
    {
        return (lhs._tree == rhs._tree);
    }

    template <typename Key, typename Compare, typename Alloc>
    bool    operator<(const multiset<Key, Compare, Alloc> &lhs, const multiset<Key, Compare, Alloc> &rhs)
    {
        return (lhs._tree < rhs._tree);
    }

    template <typename Key, typename Compare, typename Alloc>
    bool    operator!=(const multiset<Key, Compare, Alloc> &lhs, const multiset<Key, Compare, Alloc> &rhs)
    {
        return (!(lhs == rhs));
    }
	
    template <typename Key, typename Compare, typename Alloc>
    bool    operator<=(const multiset<Key, Compare, Alloc> &lhs, const multiset<Key, Compare, Alloc> &rhs)
    {
        return (!(rhs < lhs));
    }

    template <typename Key, typename Compare, typename Alloc>
    bool    operator>(const multiset<Key, Compare, Alloc> &lhs, const multiset<Key, Compare, Alloc> &rhs)
    {
        return (rhs < lhs);
    }

    template <typename Key, typename Compare, typename Alloc>
    bool    operator>=(const multiset<Key, Compare, Alloc> &lhs, const multiset<Key, Compare, Alloc> &rhs)
    {
        return (!(lhs < rhs));
    }

    template <typename Key, typename Compare, typename Alloc>
    void    swap(multiset<Key, Compare, Alloc> &lhs, multiset<Key, Compare, Alloc> &rhs)
    {
        lhs.swap(rhs);
    }
}
