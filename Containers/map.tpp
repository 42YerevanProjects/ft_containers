#pragma once

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
}
