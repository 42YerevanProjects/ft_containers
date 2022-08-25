#pragma once

#include <iostream>

namespace ft
{
    /* rb_tree_iterator utility functions */

    template<typename T>
    bool                                        rb_tree_iterator<T>::is_sentinel(base_ptr node)
    {
        return (node != 0 and node->parent == node);
    }
    
    /* rb_tree_iterator main interface functions */

    template<typename T>
    rb_tree_iterator<T>::rb_tree_iterator() : _node() {}

    template<typename T>
    rb_tree_iterator<T>::rb_tree_iterator(base_ptr x) : _node(x) { }

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
        if(is_sentinel(_node)) // for rend
            _node = _node->left;
        else if (_node->right != 0 and !is_sentinel(_node->right))
        {
            _node = _node->right;
            while (_node->left != 0 and !is_sentinel(_node->left))
                _node = _node->left;
        }
        else
        {
            if (_node == _node->parent->left)
                _node = _node->parent;
            else
            {
                while (_node == _node->parent->right)
                    _node = _node->parent;
                _node = _node->parent;
            }
        }

        return (*this);
    }
    
    template<typename T>
    typename rb_tree_iterator<T>::self         rb_tree_iterator<T>::operator++(int)
    {
        typename rb_tree_iterator<T>::self temp = *this;
        operator++();
        return (temp);
    }

    template<typename T>
    typename rb_tree_iterator<T>::self&        rb_tree_iterator<T>::operator--()
    {
        if(is_sentinel(_node)) // for end
           _node =  _node->right;
        else if (_node->left != 0 and !is_sentinel(_node->left))
        {
            _node = _node->left;
            while (_node->right != 0 and !is_sentinel(_node->right))
                _node = _node->right;
        }
        else
        {
            if (_node == _node->parent->right)
                _node = _node->parent;
            else
            {
                while (_node == _node->parent->left)
                    _node = _node->parent;
                _node = _node->parent;
            }
        }

        return (*this);
    }
    
    template<typename T>
    typename rb_tree_iterator<T>::self         rb_tree_iterator<T>::operator--(int)
    {
        typename rb_tree_iterator<T>::self temp = *this;
        operator--();
        return (temp);
    }

    template<typename T>
    typename rb_tree_iterator<T>::pointer      rb_tree_iterator<T>::operator->() const
    {
        return &static_cast<link_type>(_node)->data;
    }
    
    template<typename T>
    typename rb_tree_iterator<T>::reference    rb_tree_iterator<T>::operator*() const
    {
        return static_cast<link_type>(_node)->data;
    }
    
    /* Non-Member Operators */

    template <typename T>
	bool	operator==(const rb_tree_iterator<T>& lhs, const rb_tree_iterator<T>& rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <class T>
	bool	operator!=(const rb_tree_iterator<T>& lhs, const rb_tree_iterator<T>& rhs)
	{
		return (!(lhs == rhs));
	}
}
