#pragma once

#include "rb_tree_node.hpp"
#include <memory>


namespace ft
{

    template<typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc = std::allocator<Val> >
    class rb_tree
    {
        typedef typename Alloc::template rebind< ft::rb_tree_node<Val> >::other    node_allocator;

        protected:
            typedef ft::rb_tree_node_base*          base_ptr;
            typedef const ft::rb_tree_node_base*    const_base_ptr;
            typedef ft::rb_tree_node<Val>           rb_tree_node;

        public:
            typedef Key                     key_type;
            typedef Val                     value_type;
            typedef value_type*             pointer;
            typedef const value_type*       const_pointer;
            typedef value_type&             reference;
            typedef const value_type&       const_reference;
            typedef rb_tree_node*           link_type;
            typedef const rb_tree_node*     const_link_type;
            typedef ptrdiff_t               difference_type;
            typedef Alloc                   allocator_type;


    };
}
