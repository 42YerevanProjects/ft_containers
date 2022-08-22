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
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rb_tree(InputIt first, InputIt last, const key_compare& comp, const allocator_type& alloc,
                                                                typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type*) : _comp(comp), _alloc(alloc), _size(0)
    {
        _sentinel.parent = &_sentinel;
        insert(first, last);
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rb_tree(const rb_tree& other) : _comp(other._comp), _alloc(other._alloc), _size(0)
    {  
        _sentinel.parent = &_sentinel;

        const_iterator first = other.begin();
        const_iterator last = other.end();

        this->insert(first, last);
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>&  rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::operator=(const rb_tree& other)
    {    

        if (other != *this)
        {
            this->_comp = other._comp;

            clear();
            insert(other.begin(), other.end());
        }
        return (*this);
    }
 
    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::~rb_tree()
    {
        clear();
    }


    /*
    ==========================
        Iterator Functions
    ==========================
    */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::iterator                 rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::begin()
    { 
        return iterator(_sentinel.left);
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_iterator           rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::begin() const
    { 
        return const_iterator(_sentinel.left);
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::iterator                 rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::end() 
    {
        return iterator(&_sentinel);
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_iterator           rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::end() const 
    { 
        return const_iterator(const_cast<base_ptr>(&_sentinel)); 
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::reverse_iterator         rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rbegin() 
    {
        return reverse_iterator(end());
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_reverse_iterator   rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rbegin() const
    {
        return const_reverse_iterator(end());
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::reverse_iterator         rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rend() 
    {
        return reverse_iterator(begin());
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_reverse_iterator   rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::rend() const
    {
        return const_reverse_iterator(begin());
    }


    /*
    ==========================
        Capacity Functions
    ==========================
    */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::size_type               rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::size() const
    {
        return _size;
    }
    
    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::size_type               rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::max_size() const
    {
        return _alloc.max_size();
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    bool                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::empty() const
    {
        return _size == 0;
    }


    /*
    ==========================
        Modifier Functions
    ==========================
    */

    /* Insert Function of the Red-Black Tree */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::iterator                rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::insert(const value_type& val) 
    { 
        return (hinted_insert(val, NULL));
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    template <typename InputIterator>
    void    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::insert(InputIterator first, InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
    {
        iterator hint = end();

        while (first++ != last)
            hint = hinted_insert(*first, hint._node);
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::iterator                rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::insert(iterator position, const value_type& val)
    {
        if (position == end())
        {
            if (!empty() and _comp(extract_key(--end()), extract_key(val)))
                return(hinted_insert(val, (--position)._node));
            else
                return (hinted_insert(val, NULL));
        }
        else if (_comp(extract_key(val), extract_key(position)))
        {
            iterator	pred = position;

            if (position == begin() or _comp(extract_key(--pred), extract_key(val)))
                return (hinted_insert(val, position._node));
            else
                return (hinted_insert(val, NULL));
        }
        else if (_comp(extract_key(position), extract_key(val)))
        {
            iterator	succ = position;

            if (position == --end() or _comp(extract_key(val), extract_key(++position)))
                return (hinted_insert(val, position._node));
            else
                return (hinted_insert(val, NULL));
        }
        else
            return (hinted_insert(val, position._node));	
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::iterator                rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::insert(const_iterator position, const value_type& val)
    {
        return (insert(iterator(const_cast<base_ptr>(position._node)), val));
    }

    /* Erase Function of the Red-Black Tree */
    
    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::erase(iterator position)
    {
        base_ptr z = position._node;
        base null_leaf; // to keep track of x and nullify it with sentinels
        base_ptr x;

        base_ptr y = z;
        color y_original_color = y->color;

        if (is_external(z->left))
        {
            x = is_external(z->right) ? &null_leaf : z->right;
            transplant(z, x);
        }
        else if (is_sentinel(z->right))
        {
            x = is_external(z->right) ? &null_leaf : z->right;
            transplant(z, x);
        }
        else
        {
            y = minimum(z->right); 
            y_original_color = y->color;

            x = is_external(y->right) ? &null_leaf : y->right;
            if (y->parent == z)
                x->parent = y;
            else
            {
                transplant(y, x);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        this->_size--;
        destroy_node(z);
        if (empty())
            this->_root = 0;

        if (y_original_color == black)
            erase_fixup(x);
        nullify(&null_leaf); 

        update_extremum();
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::erase(const_iterator position)
    {
        erase(iterator(const_cast<base_ptr>(position._node)));
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::erase(iterator first, iterator last)
    {
        while (first != last)
        {

            erase(first++);
        }
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::erase(const_iterator first, const_iterator last)
    {
        iterator beg(const_cast<base_ptr>(first._node));
        iterator end(const_cast<base_ptr>(last._node));

        erase(beg, end);
    }

    /* Clear Function of Red-Black Tree */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::clear()
    {
        destroy_tree(_root);
        _root = 0;
        _size = 0;
        _sentinel.left = &_sentinel;
        _sentinel.right = &_sentinel;
    }

    /* Swap Function of Red-Black Tree */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::swap(rb_tree& x)
    {
        if (this->root() == 0)
        {
            if (x.root() != 0)
            {
                this->_root = x._root;
                this->_sentinel.left = x._sentinel.left;
                this->_sentinel.right = x._sentinel.left;
                this->_root->parent = &this->_sentinel;

                x._root = 0;
                x._sentinel.left = &x._sentinel;
                x._sentinel.right = &x._sentinel;
            }
        }
        else if (x.root() == 0)
        {
            x._root = this->_root;
            x._sentinel.left = this->_sentinel.left;
            x._sentinel.right = this->_sentinel.right;
            x._root->parent = &x._sentinel;

            this->_root = 0;
            this->_sentinel.left = x._sentinel.left;
            this->_sentinel.right = x._sentinel.left;
        }
        else
        {
            ft::swap(this->_root, x._root);
            ft::swap(this->_sentinel.left, x._sentinel.left);
            ft::swap(this->_sentinel.right, x._sentinel.right);

            this->_root->parent = &this->_sentinel;
            x._root->parent = &x._sentinel;
        
        }
        
        // No need to swap header's color as it does not change.

        ft::swap(this->_size, x._size);
        ft::swap(this->_comp, x._comp);
    }


    /*
    ========================
        Lookup Functions
    ========================
    */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::size_type               rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::count(const key_type& k) const
    {
       size_type n = 0;
       base_ptr  x = root();

       while (is_internal(x))
       {
           key_type curr = extract_key(x);

           if (_comp(k, curr))
               x = x->left;
           else if (_comp(curr, k))
               x = x->right;
           else
           {
               n++;
               x = x->left; // Case for multiset and multimap
           }
       }

       return (n);
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::iterator                rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::find(const key_type& k)
    {
        if (count(k))
            return iterator(find_node(root(), k));
        else
            return end();
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_iterator           rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::find(const key_type& k) const
    {
        if (count(k))
            return const_iterator(find_node(root(), k));
        else
            return end();
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::iterator                rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::lower_bound(const key_type& k)
    {
        base_ptr x = root();
        base_ptr y = &this->_sentinel;

        while (is_internal(x))
        {
            if (!_comp(extract_key(x), k))
            {
                y = x;
                x = x->left;
            }
            else
                x = x->right;
        }

        return iterator(y);
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_iterator           rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::lower_bound(const key_type& k) const
    {
        base_ptr x = root();
        base_ptr y = const_cast<base_ptr>(&_sentinel);

        while (is_internal(x))
        {
            if (!_comp(extract_key(x), k))
            {
                y = x;
                x = x->left;
            }
            else
                x = x->right;
        }

        return const_iterator(y);
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::iterator                rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::upper_bound(const key_type& k)
    {
        base_ptr x = root();
        base_ptr y = &this->_sentinel;

        while (is_internal(x))
        {
            if (_comp(k, extract_key(x)))
            {
                y = x;
                x = x->left;
            }
            else
                x = x->right;
        }

        return iterator(y);
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_iterator          rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::upper_bound(const key_type& k) const
    {
        base_ptr x = root();
        base_ptr y = const_cast<base_ptr>(&_sentinel);

        while (is_internal(x))
        {
            if (_comp(k, extract_key(x)))
            {
                y = x;
                x = x->left;
            }
            else
                x = x->right;
        }

        return const_iterator(y);
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    ft::pair< typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::iterator, typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::iterator>           
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::equal_range(const key_type& k)
    {
        ft::pair<const_iterator, const_iterator> const_range = static_cast<const rb_tree&>(*this).equal_range(k);
        
        iterator low = iterator(const_cast<base_ptr>(const_range.first._node));
        iterator up = iterator(const_cast<base_ptr>(const_range.second._node));

        return (ft::make_pair(low, up));
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    ft::pair< typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_iterator, typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::const_iterator>           
    rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::equal_range(const key_type& k) const
    {
        return (ft::make_pair(lower_bound(k), upper_bound(k)));
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::print_keys() const
    {
        inorder(root());
    }


    /*
    ==========================
        Observer Functions
    ==========================
    */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::key_compare             rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::key_comp() const
    {
        return (this->_comp);
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::allocator_type          rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::get_allocator() const
    {
        return (this->_alloc);
    }


    /*
    =========================
        Utility Functions
    =========================
    */ 

    /* Insert & Delete Utility Functions */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::iterator                rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::hinted_insert(const value_type& val, base_ptr hint)
    {        
        base_ptr    x = ((is_internal(hint)) ? hint : this->root());
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
                else if (_comp(extract_key(x), extract_key(z)))
                    x = x->right;
                else    // Case for multiset and multimap
                    x = x->left;
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
        return (iterator(z));
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::insert_fixup(base_ptr z)
    {
        while (is_red(z->parent))
        {
            if (z->parent == z->parent->parent->left)
            {
                base_ptr y = z->parent->parent->right;

                /* Case 1 */
                if (is_red(y))
                {
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                }
                else
                {
                    /* Case 2 */
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        left_rotate(z);
                    }

                    /* Case 3 */
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    right_rotate(z->parent->parent);
                }
            }
            else
            {    
                base_ptr y = z->parent->parent->left;

                /* Case 1 */
                if (is_red(y))
                {
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                }
                else
                {    

                    /* Case 2 */
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        right_rotate(z);
                    }

                    /* Case 3 */
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
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::erase_fixup(base_ptr x)
    {
        while (!is_root(x) and is_black(x))
        {
            if (x == x->parent->left)
            {
                base_ptr w = x->parent->right;
 
                /* Case 1 */
                if (is_red(w))
                {
                    w->color = black;
                    x->parent->color = red;
                    left_rotate(x->parent);
                    w = x->parent->right;
                }

                /* Case 2 */
                if (is_black(w->left) and is_black(w->right))
                {
                    w->color = red;
                    x = x->parent;
                }
                else 
                {
                    /* Case 3*/
                    if (is_black(w->right))
                    {
                        w->left->color = black;
                        w->color = red;
                        right_rotate(w);
                        w = x->parent->right;
                    }

                    /* Case 4*/
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->right->color = black;
                    left_rotate(x->parent);
                    x = root();
                }
            }
            else
            {
                base_ptr w = x->parent->left;
 
                /* Case 1 */
                if (is_red(w))
                {
                    w->color = black;
                    x->parent->color = red;
                    right_rotate(x->parent);
                    w = x->parent->left;
                }

                /* Case 2 */
                if (is_black(w->left) and is_black(w->right))
                {

                    w->color = red;
                    x = x->parent;
                }
                else 
                {
                    /* Case 3*/
                    if (is_black(w->left))
                    {
                        w->right->color = black;
                        w->color = red;
                        left_rotate(w);
                        w = x->parent->left;
                    }

                    /* Case 4*/
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->left->color = black;
                    right_rotate(x->parent);
                    x = root();
                }
            } 
            x->color = black;
        }
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

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::transplant(base_ptr u, base_ptr v)
    {
        if (is_root(u))
            _root = static_cast<node *>(v);
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::nullify(base_ptr leaf)
    {
        if (leaf->parent)
        {
            if (leaf == leaf->parent->left)
                leaf->parent->left = &_sentinel;
            else
                leaf->parent->right = &_sentinel;
        }
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

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    const typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::key_type&         rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::extract_key(iterator it) const
    {
        return (KeyOfValue()(*it));
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

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::destroy_node(base_ptr n) 
    {
        allocator_type alloc_copy(this->_alloc);
        alloc_copy.destroy(&static_cast<node *>(n)->data);
        this->_alloc.deallocate(static_cast<node *>(n), 1);
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::destroy_tree(base_ptr n) 
    {
        if (is_external(n))
            return;
        destroy_tree(n->left);
        destroy_tree(n->right);
        destroy_node(n);
    }

    /* Node Lookup Utility Function */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::base_ptr                rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::find_node(base_ptr current, const key_type& k) const
    {
        if (is_external(current) || equal_keys(extract_key(current), k))
            return (current);
        else if (_comp(k, extract_key(current)))
            return find_node(current->left, k);
        else 
            return find_node(current->right, k);
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    bool                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::equal_keys(const key_type& x, const key_type& y) const
    {
        return (!_comp(x, y) and !_comp(y, x));
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::inorder(base_ptr x) const
    {
        if (is_external(x))
            return;
        inorder(x->left);
        std::cout << extract_key(x) << " ";
        inorder(x->right);
    }

    /* Tree min, max utility functions */

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::node*                   rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::minimum(base_ptr n)
    {
        base_ptr min = n;
        if (is_external(min))
            return (NULL);

        while (is_internal(min->left))
            min = min->left;
        return (static_cast<link_type>(min));
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    typename rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::node*                   rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::maximum(base_ptr n)
    {
        base_ptr max = n;

        if (is_external(max))
            return (NULL);

        while (is_internal(max->right))
            max = max->right;
        return (static_cast<link_type>(max));
    }

    template < typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    void                                                                            rb_tree<Key, Val, KeyOfValue, Compare, Alloc>::update_extremum()
    {
        node* min = minimum(this->_root);
        node* max = maximum(this->_root);

        _sentinel.left = (min != 0) ? min : &_sentinel;
        _sentinel.right = (max != 0) ? max : &_sentinel;
    }


    /*
    =====================================
        Non-Member Operator Overloads
    =====================================
    */

    template <typename Key, typename Val, typename KeyOfValue, typename  Compare, typename Alloc>
	bool    operator==(const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &lhs, const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &rhs)
	{
		return (lhs.size() == rhs.size() and ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

    template <typename Key, typename Val, typename KeyOfValue, typename  Compare, typename Alloc>
	bool    operator!=(const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &lhs, const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

    template <typename Key, typename Val, typename KeyOfValue, typename  Compare, typename Alloc>
	bool    operator<(const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &lhs, const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

    template <typename Key, typename Val, typename KeyOfValue, typename  Compare, typename Alloc>
	bool    operator<=(const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &lhs, const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

    template <typename Key, typename Val, typename KeyOfValue, typename  Compare, typename Alloc>
	bool    operator>(const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &lhs, const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

    template <typename Key, typename Val, typename KeyOfValue, typename  Compare, typename Alloc>
	bool    operator>=(const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &lhs, const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

    template <typename Key, typename Val, typename KeyOfValue, typename  Compare, typename Alloc>
	void    swap(rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &lhs, rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &rhs)
	{
        lhs.swap(rhs);
	}
}
