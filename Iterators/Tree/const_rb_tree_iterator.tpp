#pragma once

namespace ft
{
    /* const_rb_tree_iterator utility functions */
    
    template<typename T>
    typename const_rb_tree_iterator<T>::link_type      const_rb_tree_iterator<T>::inorder_increment(link_type node)
    {
        if (node->right != 0)
        {
            node = node->right;
            while (node->left != 0)
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
    typename const_rb_tree_iterator<T>::link_type      const_rb_tree_iterator<T>::inorder_decrement(link_type node)
    {
        if (node->left != 0)
        {
            node = node->left;
            while (node->right != 0)
                node = node->right;
        }
        else
        {
            if (node == node->parent->right)
                node = node->parent;
            else
            {
                while (node == node->parent->left)
                    node = node->parent;
                node = node->parent;
            }
        }
        return (node);
    }

    /* const_rb_tree_iterator main interface functions */

    template<typename T>
    const_rb_tree_iterator<T>::const_rb_tree_iterator() : _node() {}

    template<typename T>
    const_rb_tree_iterator<T>::const_rb_tree_iterator(link_type x) : _node(x) {}

    template<typename T>
    const_rb_tree_iterator<T>::const_rb_tree_iterator(const iterator& _it) : _node(_it._node) {}

    template<typename T>
    const_rb_tree_iterator<T>::const_rb_tree_iterator(const self& other) { *this = other; }

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
        *this = inorder_increment(_node);
        return (*this);
    }
    
    template<typename T>
    typename const_rb_tree_iterator<T>::self         const_rb_tree_iterator<T>::operator++(int)
    {
        typename const_rb_tree_iterator<T>::self temp = *this;
        *this = inorder_increment(_node);
        return (temp);
    }

    template<typename T>
    typename const_rb_tree_iterator<T>::self&        const_rb_tree_iterator<T>::operator--()
    {
        *this = inorder_decrement(_node);
        return (*this);
    }
    
    template<typename T>
    typename const_rb_tree_iterator<T>::self         const_rb_tree_iterator<T>::operator--(int)
    {
        typename const_rb_tree_iterator<T>::self temp = *this;
        *this = inorder_decrement(_node);
        return (temp);
    }

    template<typename T>
    typename const_rb_tree_iterator<T>::pointer      const_rb_tree_iterator<T>::operator->() const
    {
        return &static_cast<link_type>(_node)->_data;
    }
    
    template<typename T>
    typename const_rb_tree_iterator<T>::reference    const_rb_tree_iterator<T>::operator*() const
    {
        return static_cast<link_type>(_node)->_data;
    }
    

    template<typename T>
    bool                                       const_rb_tree_iterator<T>::operator==(const self& x) const
    {
        return this->_node == x._node;
    }

    template<typename T>
    bool                                       const_rb_tree_iterator<T>::operator!=(const self& x) const
    {
        return this->_node == x._node;
    }
}
