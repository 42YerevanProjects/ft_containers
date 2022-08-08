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

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rb_tree(const key_compare& comp, const allocator_type& alloc) : _root(0), _comp(comp), _alloc(alloc), _size(0)
    {
        _sentinel.parent = &_sentinel;
        update_extremum(); 
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    template<typename InputIt>
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rb_tree(InputIt first, InputIt last, const key_compare& comp, const allocator_type& alloc) : _comp(comp), _alloc(alloc)
    {
        _sentinel.parent = &_sentinel;
        update_extremum();
        // TODO: To be implemented after I implement the insert function
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rb_tree(const rb_tree& other) : _size(other._size), _comp(other._comp), _alloc(other._alloc)
    {  
        // TODO: To be implemented after I implement the insert function
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>&  rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::operator=(const rb_tree& other)
    {    
        // TODO: To be implemented after I implement the insert and erase functions
    }
 
    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::~rb_tree()
    {
        // TODO: To be implemented after I implement the clear function
    }


    /*
    ==========================
        Iterator Functions
    ==========================
    */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::iterator                 rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::begin() { return iterator(_sentinel.left); }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_iterator           rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::begin() const { return const_iterator(_sentinel.left); }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::iterator                 rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::end() { return iterator(&_sentinel); }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_iterator           rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::end() const { return const_iterator(&_sentinel); }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::reverse_iterator         rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rbegin() { return reverse_iterator(end()); }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_reverse_iterator   rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rbegin() const { return const_reverse_iterator(end()); }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::reverse_iterator         rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rend() { return reverse_iterator(begin()); }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_reverse_iterator   rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rend() const { return const_reverse_iterator(begin()); }


    /*
    ==========================
        Capacity Functions
    ==========================
    */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::size_type               rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::size() const { return _size; }
    
    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::size_type               rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::max_size() const { return _alloc.max_size(); }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    bool                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::empty() const { return _size == 0; }


    /*
    ==========================
        Modifier Functions
    ==========================
    */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::insert(const value_type& val) 
    {
        base_ptr    x = _root;
        base_ptr    y = &_sentinel;
        node*       z = create_node(val);

        if (x == 0)
        {
            _root = z;
            _root->parent = &_sentinel;
        }
        else
        {
            while (!is_sentinel(x))
            {
                y = x;
                if (_comp(extract_key(z), extract_key(x)))
                    x = x->left;
                else
                    x = x->right;
            }

            z->parent = y;
            if (is_sentinel(y))
                _root = z;
            else if (_comp(extract_key(z), extract_key(y)))
                y->left = z;
            else
                y->right = z;
        }    

        z->left = &_sentinel;
        z->right = &_sentinel;
        z->color = red;

        _size++;
        insert_fixup(z);
        update_extremum();
    }


    /*
    =========================
        Utility Functions
    =========================
    */ 

    /* Insert & Delete Utility Functions */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::insert_fixup(base_ptr z)
    {
        while (is_red(z->parent))
        {
            if (z->parent == z->parent->parent->left)
            {
                base_ptr y = z->parent->parent->right;
                if (is_red(y))
                {
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    right_rotate(z->parent->parent);
                }
            }
            else
            {    
                base_ptr y = z->parent->parent->left;
                if (is_red(y))
                {
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                }
                else
                {    
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    left_rotate(z->parent->parent);
                }
            }
        }
        _root->color = black;
        _sentinel.color = black;
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::left_rotate(base_ptr x)
    {
        base_ptr y = x->right;

        x->right = y->left;
        if (!is_sentinel(y->left))
            y->left->parent = x;

        y->parent = x->parent;
        if (is_sentinel(x->parent))
            _root = static_cast<node *>(y);
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::right_rotate(base_ptr x)
    {
        base_ptr y = x->left;

        x->left = y->right;
        if (!is_sentinel(y->right))
            y->right->parent = x;

        y->parent = x->parent;
        if (is_sentinel(x->parent))
            _root = static_cast<node *>(y);
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->right = x;
        x->parent = y;
    }

    /* Key Extraction Utility Functions */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    const typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::key_type&         rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::extract_key(const value_type& val) const
    {
        return (KeyOfValue()(val));
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    const typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::key_type&         rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::extract_key(const base_ptr n) const
    {
        return (KeyOfValue()(static_cast<const node*>(n)->data));
    }

    /* Node Check Utility Functions */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::node*                   rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::root() const
    { 
        return (this->_root); 
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    bool                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::is_root(const base_ptr n) const
    { 
        return (this->_root == n); 
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    bool                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::is_red(const base_ptr n) const
    { 
        return (n != 0 and n->color == red); 
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    bool                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::is_black(const base_ptr n) const
    { 
        return (n != 0 and n->color == black); 
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    bool                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::is_external(const base_ptr n) const
    { 
        return (n == 0 or is_sentinel(n)); 
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    bool                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::is_internal(const base_ptr n) const
    { 
        return (n != 0 and !is_sentinel(n)); 
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    bool                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::is_sentinel(const base_ptr n) const
    { 
        return (n != 0 and n->parent == n); 
    }

    /* Node Create/Delete Utility Functions */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::node*                   rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::create_node(const value_type& val) 
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

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::node*                   rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::minimum()
    {
        base_ptr min = _root;
        while (min && min->left != 0 && !is_sentinel(min->left))
            min = min->left;
        return (static_cast<link_type>(min));
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::node*                   rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::maximum()
    {
        base_ptr max = _root;
        while (max && max->right != 0 && !is_sentinel(max->right))
            max = max->right;
        return (static_cast<link_type>(max));
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::update_extremum()
    {
        node* min = minimum();
        node* max = maximum();

        _sentinel.left = (min != 0) ? min : 0;
        _sentinel.right = (max != 0) ? max : 0;
    }
}
