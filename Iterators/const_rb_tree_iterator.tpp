#pragma once

namespace ft
{
    /* const_rb_tree_iterator utility functions */
    
    template<typename T>
    bool                                            const_rb_tree_iterator<T>::is_sentinel(const base_ptr node)
    {
        return (node != 0 and node->parent == node);
    }

    /* const_rb_tree_iterator main interface functions */

    template<typename T>
    const_rb_tree_iterator<T>::const_rb_tree_iterator() : _node() {}

    template<typename T>
    const_rb_tree_iterator<T>::const_rb_tree_iterator(const base_ptr x) : _node(x) {}

    template<typename T>
    const_rb_tree_iterator<T>::const_rb_tree_iterator(const iterator& _it) : _node(_it._node) {}

    template<typename T>
    const_rb_tree_iterator<T>::const_rb_tree_iterator(const self& other) : _node(other._node ) {}

    template<typename T>
    const_rb_tree_iterator<T>::~const_rb_tree_iterator() {}

    template<typename T>
    typename const_rb_tree_iterator<T>::self&        const_rb_tree_iterator<T>::operator=(const self& other) 
    {
        this->_node = other._node;
        return (*this);
    }

    template<typename T>
    typename const_rb_tree_iterator<T>::self&        const_rb_tree_iterator<T>::operator++()
    {
        if(_node == _node->parent) // for rend
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
    typename const_rb_tree_iterator<T>::self         const_rb_tree_iterator<T>::operator++(int)
    {
        typename const_rb_tree_iterator<T>::self temp = *this;
        operator++();
        return (temp);
    }

    template<typename T>
    typename const_rb_tree_iterator<T>::self&        const_rb_tree_iterator<T>::operator--()
    {
        if(_node == _node->parent) // for end
            _node = _node->right;
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
    typename const_rb_tree_iterator<T>::self         const_rb_tree_iterator<T>::operator--(int)
    {
        typename const_rb_tree_iterator<T>::self temp = *this;
        operator--();
        return (temp);
    }

    template<typename T>
    typename const_rb_tree_iterator<T>::pointer      const_rb_tree_iterator<T>::operator->() const
    {
        return &(operator*());
    }
    
    template<typename T>
    typename const_rb_tree_iterator<T>::reference    const_rb_tree_iterator<T>::operator*() const
    {
        return static_cast<link_type>(_node)->data;
    }
    

    /* Non-Member Operators*/

    template <typename T>
	bool	operator==(const const_rb_tree_iterator<T>& lhs, const const_rb_tree_iterator<T>& rhs)
	{
		return (lhs._node == rhs._node);
	}

    template <typename T>
	bool	operator!=(const const_rb_tree_iterator<T>& lhs, const const_rb_tree_iterator<T>& rhs)
	{
		return (!(lhs == rhs));
	}

    template <typename T>
	bool    operator==(const rb_tree_iterator<T>& lhs, const const_rb_tree_iterator<T>& rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <class T>
	bool	operator==(const const_rb_tree_iterator<T>& lhs, const rb_tree_iterator<T>& rhs)
	{
		return (lhs._node == rhs._node);
	}

    template <typename T>
	bool    operator!=(const rb_tree_iterator<T>& lhs, const const_rb_tree_iterator<T>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename T>
	bool	operator!=(const const_rb_tree_iterator<T>& lhs, const rb_tree_iterator<T>& rhs)
	{
		return (!(lhs == rhs));
	}

    // For iterator and const iterator
    template <typename U, typename V>
	bool	operator==(const rb_tree_iterator<U>& lhs, const const_rb_tree_iterator<V>& rhs)
	{
		return (lhs._node == rhs._node);
	}

    template <typename U, typename V>
	bool	operator==(const const_rb_tree_iterator<U>& lhs, const rb_tree_iterator<V>& rhs)
	{
		return (lhs._node == rhs._node);
	}

    template <typename U, typename V>
	bool	operator!=(const rb_tree_iterator<U>& lhs, const const_rb_tree_iterator<V>& rhs)
	{
		return (!(lhs == rhs));
	}

    template <typename U, typename V>
	bool	operator!=(const const_rb_tree_iterator<U>& lhs, const rb_tree_iterator<V>& rhs)
	{
		return (!(lhs == rhs));
	}
}
