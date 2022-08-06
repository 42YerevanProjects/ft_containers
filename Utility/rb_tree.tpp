#pragma once

#include <memory>
#include <iostream>

namespace ft
{
    /*
    ===================================
        Constructors and Destructor
    ===================================
    */

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rb_tree(const key_compare& comp, const allocator_type& alloc) : _comp(comp), _alloc(alloc)
    {
        _root = 0;
        _size = 0;
        _sentinel.parent = &_sentinel;
        update_extremum(); 
    }

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    template<typename InputIt>
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rb_tree(InputIt first, InputIt last, const key_compare& comp, const allocator_type& alloc) : _comp(comp), _alloc(alloc)
    {
        _sentinel.parent = &_sentinel;
        update_extremum();
        // TODO: To be implemented after I implement the insert function
    }

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rb_tree(const rb_tree& other) : _size(other._size), _comp(other._comp), _alloc(other._alloc)
    {  
        // TODO: To be implemented after I implement the insert function
    }

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>&  rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::operator=(const rb_tree& other)
    {    
        // TODO: To be implemented after I implement the insert and erase functions
    }

    
    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::~rb_tree()
    {
        // TODO: To be implemented after I implement the clear function
    }


    /*
    ==========================
        Iterator Functions
    ==========================
    */

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::iterator                rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::begin() { return iterator(_sentinel.left); }

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_iterator          rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::begin() const { return const_iterator(_sentinel.left); }

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::iterator                rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::end() { return iterator(&_sentinel); }

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_iterator          rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::end() const { return const_iterator(&_sentinel); }

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::reverse_iterator        rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rbegin() { return reverse_iterator(end()); }

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_reverse_iterator  rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rbegin() const { return const_reverse_iterator(end()); }

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::reverse_iterator        rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rend() { return reverse_iterator(begin()); }

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_reverse_iterator          rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rend() const { return const_reverse_iterator(begin()); }


    /*
    =========================
        Utility Functions
    =========================
    */

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    bool                                                                                    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::is_sentinel(const base_ptr n) const
    { 
        return (n != 0 and n->parent == n); 
    }


    /* Node Create/Delete Utility Functions */

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::node*                           rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::create_node(const value_type& val) 
    { 
        node*   new_node = this->_alloc.allocate(1);
        try
        {
            allocator_type  alloc_copy(this->_alloc);
            alloc_copy.construct(&new_node->data, val);
        }
        catch(...)
        {
            this->_alloc.deallocate(new_node, 1);
            throw ;
        }
        return (new_node);
    }


    /* Tree min, max utility functions */

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::node*                           rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::minimum()
    {
        base_ptr min = _root;
        while (min && min->left != 0 && !is_sentinel(min->left))
            min = min->left;
        return (static_cast<link_type>(min));
    }

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::node*                           rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::maximum()
    {
        base_ptr max = _root;
        while (max && max->right != 0 && !is_sentinel(max->right))
            max = max->right;
        return (static_cast<link_type>(max));
    }

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                                    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::update_extremum()
    {
        node* min = minimum();
        node* max = maximum();

        _sentinel.left = (min != 0) ? min : 0;
        _sentinel.right = (max != 0) ? max : 0;
    }
}
