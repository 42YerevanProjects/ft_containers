#pragma once

#include "rb_tree_node.hpp"
#include "../Iterators/List/reverse_iterator.hpp"
#include "../Iterators/Tree/rb_tree_iterator.hpp"
#include "../Iterators/Tree/const_rb_tree_iterator.hpp"
#include <memory>


namespace ft
{
    template< typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc = std::allocator<Val> >
    class rb_tree
    {
        private:
            typedef typename Alloc::template rebind< ft::rb_tree_node<Val> >::other    node_allocator;

        protected:
            typedef ft::rb_tree_node_base*          base_ptr;
            typedef const ft::rb_tree_node_base*    const_base_ptr;
            typedef ft::rb_tree_node<Val>           node;

        public:
            typedef Key             key_type;
            typedef Val             value_type;
            typedef Compare         key_compare;
            typedef value_type*     pointer;
            typedef value_type&     reference;
            typedef node*           link_type;
            typedef size_t          size_type;
            typedef Alloc           allocator_type;

            typedef ft::rb_tree_iterator<value_type>         iterator;
            typedef ft::const_rb_tree_iterator<value_type>   const_iterator;
            typedef ft::reverse_iterator<iterator>           reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

        protected:
            base_ptr        _root;
            key_compare     _comp;
            node_allocator  _alloc;
            size_type       _size;


    };
}
