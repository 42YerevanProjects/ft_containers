#pragma once

#include <iostream>

namespace ft
{
    /* rb_tree_iterator utility functions */

    template<typename T>
    bool                                        rb_tree_iterator<T>::is_sentinel(link_type node)
    {
        return (node != 0 and node->data == 0 and node->parent == node);
    }
    
    template<typename T>
    typename rb_tree_iterator<T>::link_type     rb_tree_iterator<T>::inorder_increment(link_type node)
    {
        if(is_sentinel(node))
            return node->left;
        if (node->right != 0 and !is_sentinel(node->right))
        {
            node = node->right;
            while (node and node->left != 0 and !is_sentinel(node->left))
                node = node->left;
        }
        else
        {
            if (node == node->parent->left)
                node = node->parent;
            else
            {
                while (node == node->parent->right)
                    node = node->parent;
                node = node->parent;
            }
        }
        return (node);
    }

    template<typename T>
    typename rb_tree_iterator<T>::link_type     rb_tree_iterator<T>::inorder_decrement(link_type node)
    {
        if(is_sentinel(node))
            return node->right;
        if (node->left != 0 and !is_sentinel(node->left))
        {
            node = node->left;
            while (node and node->right != 0 and !is_sentinel(node->right))
                node = node->right;
        }
        else
        {
            if (node->parent && node == node->parent->right)
                node = node->parent;
            else
            {
                while (node->parent && node == node->parent->left)
                    node = node->parent;
                node = node->parent;
            }
        }
        return (node);
    }

    /* rb_tree_iterator main interface functions */

    template<typename T>
    rb_tree_iterator<T>::rb_tree_iterator() : _node() {}

    template<typename T>
    rb_tree_iterator<T>::rb_tree_iterator(link_type x) : _node(x) { }

    template<typename T>
    rb_tree_iterator<T>::rb_tree_iterator(const self& other) { *this = other; }

    template<typename T>
    rb_tree_iterator<T>::~rb_tree_iterator() {}

    template<typename T>
    typename rb_tree_iterator<T>::self&        rb_tree_iterator<T>::operator=(const self& other) 
    {
        this->_node = other._node;
        return (*this);
    }

    template<typename T>
    typename rb_tree_iterator<T>::self&        rb_tree_iterator<T>::operator++()
    {
        this->_node = inorder_increment(_node);
        return (*this);
    }
    
    template<typename T>
    typename rb_tree_iterator<T>::self         rb_tree_iterator<T>::operator++(int)
    {
        typename rb_tree_iterator<T>::self temp = *this;
        this->_node = inorder_increment(_node);
        return (temp);
    }

    template<typename T>
    typename rb_tree_iterator<T>::self&        rb_tree_iterator<T>::operator--()
    {
        this->_node = inorder_decrement(_node);
        return (*this);
    }
    
    template<typename T>
    typename rb_tree_iterator<T>::self         rb_tree_iterator<T>::operator--(int)
    {
        typename rb_tree_iterator<T>::self temp = *this;
        this->_node = inorder_decrement(_node);
        return (temp);
    }

    template<typename T>
    typename rb_tree_iterator<T>::pointer      rb_tree_iterator<T>::operator->() const
    {
        return &static_cast<link_type>(_node)->_data;
    }
    
    template<typename T>
    typename rb_tree_iterator<T>::reference    rb_tree_iterator<T>::operator*() const
    {
        return static_cast<link_type>(_node)->data;
    }
    
    /* rb_tree_iterator equality checks */

    template<typename T>
    bool                                       rb_tree_iterator<T>::operator==(const self& x) const
    {
        return this->_node == x._node;
    }

    template<typename T>
    bool                                       rb_tree_iterator<T>::operator!=(const self& x) const
    {
        return this->_node != x._node;
    }
}
