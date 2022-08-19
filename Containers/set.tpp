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
}
