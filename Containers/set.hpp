#pragma once

#include "../Includes/utility.hpp"
#include <memory>

namespace ft
{
    template<
              class Key,
              class Compare = ft::less<Key>,
              class Alloc = std::allocator<Key>
            >
    class set
    {
        public:
            typedef Key                 key_type;
            typedef Key                 value_type;
            typedef Compare             key_compare;
            typedef Compare             value_compare;
            typedef Alloc               allocator_type;

        private:
            typedef typename Alloc::template rebind<key_type>::other                                        key_allocator;
            typedef ft::rb_tree<ket_type, value_type, select_self<value_type>, key_compare, key_allocator>  rb_tree;

    };
}
