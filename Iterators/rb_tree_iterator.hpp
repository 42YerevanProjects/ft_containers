#pragma once

#include "iterator.hpp"
#include "../Utility/rb_tree_node.hpp"


/*
===============================
    Red-Black Tree Iterator
===============================
*/

namespace ft
{
    template <typename T>
    class	const_rb_tree_iterator;


    template <typename T>
    class rb_tree_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {
        private:
            template <class K, class V, class KOV, class C, class A>
			friend class rb_tree;

            template <typename U>
            friend class const_rb_tree_iterator;

            template <typename V>
            friend bool	operator==(const rb_tree_iterator<V>& lhs, const rb_tree_iterator<V>& rhs);
            template <typename V>
            friend bool operator==(const rb_tree_iterator<V>& lhs, const const_rb_tree_iterator<V>& rhs);
            template <typename V>
            friend bool operator==(const const_rb_tree_iterator<V>& lhs, const rb_tree_iterator<V>& rhs);

        public:
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type        value_type;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer           pointer;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference         reference;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type   difference_type;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;

            typedef rb_tree_iterator<T> self;
            typedef rb_tree_node_base*  base_ptr;
            typedef rb_tree_node<T>*    link_type;

        private:
            bool        is_sentinel(base_ptr node);

        protected:
            base_ptr    _node;

        public:
            /* Constructors and Destructor */

            rb_tree_iterator();
            rb_tree_iterator(base_ptr x);
            rb_tree_iterator(const self& other);
            virtual ~rb_tree_iterator();

            /* Operator Overloads */

            self&       operator=(const self& other);

            self&       operator++();
            self        operator++(int);

            self&       operator--();
            self        operator--(int);

            pointer     operator->() const;
            reference   operator*() const;
    };
}

#include "Impl/rb_tree_iteratorImpl.tpp"


/*
=====================================
    Red-Black Tree Const Iterator
=====================================
*/

namespace ft
{
    template <typename T>
    class const_rb_tree_iterator : ft::iterator<ft::bidirectional_iterator_tag, const T>
    {
        private:
            template <class K, class V, class KOV, class C, class A>
            friend class rb_tree;

            template <typename V>
            friend bool operator==(const const_rb_tree_iterator<V>& lhs, const const_rb_tree_iterator<V>& rhs);
            template <typename V>
            friend bool operator==(const rb_tree_iterator<V>& lhs, const const_rb_tree_iterator<V>& rhs);
            template <typename V>
            friend bool operator==(const const_rb_tree_iterator<V>& lhs, const rb_tree_iterator<V>& rhs);

        public:
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, const T>::value_type        value_type;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, const T>::pointer           pointer;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, const T>::reference         reference;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, const T>::difference_type   difference_type;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, const T>::iterator_category iterator_category;

            typedef rb_tree_iterator<T>         iterator;

            typedef const_rb_tree_iterator<T>   self;
            typedef ft::rb_tree_node_base*      base_ptr;
            typedef const rb_tree_node<T>*      link_type;

        private:
            bool        is_sentinel(const base_ptr node);

        protected:
            const ft::rb_tree_node_base    *_node;

        public:
            /* Constructors and Destructor */

            const_rb_tree_iterator();
            const_rb_tree_iterator(const base_ptr x);
            const_rb_tree_iterator(const iterator& _it);
            const_rb_tree_iterator(const self& other);
            virtual ~const_rb_tree_iterator();

            /* Operator Overloads */

            self&       operator=(const self& other);

            self&       operator++();
            self        operator++(int);

            self&       operator--();
            self        operator--(int);

            pointer     operator->() const;
            reference   operator*() const;
    };
}

#include "Impl/const_rb_tree_iteratorImpl.tpp"
