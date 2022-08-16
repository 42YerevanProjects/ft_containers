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
}
