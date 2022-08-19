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
            typedef Key                                         key_type;
            typedef Key                                         value_type;
            typedef Compare                                     key_compare;
            typedef Compare                                     value_compare;
            typedef Alloc                                       allocator_type;

        private:
            typedef typename Alloc::template rebind<key_type>::other                                        key_allocator;
            typedef ft::rb_tree<key_type, value_type, select_self<value_type>, key_compare, key_allocator>  rb_tree;

        public:
            typedef typename key_allocator::reference           reference;               
            typedef typename key_allocator::const_reference     const_reference;               
            typedef typename key_allocator::pointer             pointer;               
            typedef typename key_allocator::const_pointer       const_pointer;               
            typedef ptrdiff_t                                   difference_type;
            typedef size_t                                      size_type;

            typedef typename rb_tree::iterator                  iterator;
            typedef typename rb_tree::const_iterator            const_iterator;
            typedef typename rb_tree::reverse_iterator          reverse_iterator;
            typedef typename rb_tree::const_reverse_iterator    const_reverse_iterator;
    };
}
