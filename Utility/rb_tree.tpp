#pragma once

#include <memory>

namespace ft
{
    /*
    ===================================
        Constructors and Destructor
    ===================================
    */

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rb_tree(const key_compare& comp, const allocator_type& alloc) : _root(), _comp(comp), _alloc(alloc), _size(), _sentinel() {}

    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    template<typename InputIterator>
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rb_tree(InputIterator first, InputIterator last, const key_compare& comp, const allocator_type& alloc) : _comp(comp), _alloc(alloc), _sentinel() 
    {
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
    

}
