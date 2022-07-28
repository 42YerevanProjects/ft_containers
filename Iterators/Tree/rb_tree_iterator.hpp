#pragma once

#include "../iterator.hpp"
#include "../../Utility/rb_tree_node.hpp"

/*
===============================
    Red-Black Tree Iterator
===============================
*/

namespace ft
{
    template <typename T>
    class rb_tree_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {
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
            base_ptr    inorder_increment(base_ptr node);
            base_ptr    inorder_decrement(base_ptr node);

        protected:
            base_ptr    node;

        public:

            /* Constructors and Destructor */

            rb_tree_iterator();
            explicit rb_tree_iterator(link_type x);
            rb_tree_iterator(const rb_tree_iterator& other);
            virtual ~rb_tree_iterator();

            /* Operator Overloads */

            self&       operator++();
            self        operator++(int);

            self&       operator--();
            self        operator--(int);

            pointer     operator->();
            reference   operator*();

            bool    operator==(const self& x) const;
            bool    operator!=(const self& x) const;
    };
}
