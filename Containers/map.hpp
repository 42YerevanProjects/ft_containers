#pragma once

#include "../Includes/utility.hpp"

namespace ft
{
    template < class Key,
               class T,
               class Compare = ft::less<Key>,
               class Alloc = std::allocator<ft::pair<const Key, T> >
             >
    class map
    {
        public:
            typedef Key                                         key_type;
            typedef T                                           mapped_type;
            typedef Compare                                     key_compare;
            typedef Alloc                                       allocator_type;
            typedef ft::pair<const key_type, mapped_type>       value_type;

        private:
            typedef typename Alloc::template rebond<value_type>::other                                              pair_allocator;
            typedef ft::rb_tree<key_type, value_type, ft::select_first<value_type>, key_compare, pair_allocator>    rb_tree;

        public:
            typedef typename pair_allocator::reference          reference;               
            typedef typename pair_allocator::const_reference    const_reference;               
            typedef typename pair_allocator::pointer            pointer;               
            typedef typename pair_allocator::const_pointer      const_pointer;               
            typedef ptrdiff_t                                   difference_type;
            typedef size_t                                      size_type;

            typedef typename rb_tree::iterator                  iterator;
            typedef typename rb_tree::const_iterator            const_iterator;
            typedef typename rb_tree::reverse_iterator          reverse_iterator;
            typedef typename rb_tree::const_reverse_iterator    const_reverse_iterator;

        private:
            class value_compare : ft::binary_function<value_type, value_type, bool>
            {
                private:
                    friend class map<key_type, value_type, key_compare, allocator_type>;

                protected:
                    key_compare _comp;

                public:
                    value_compare(key_compare c) : _comp(c) {}

                    bool    operator()(const value_type& lhs, const value_type& rhs)
                    {
                        return (this->_comp(lhs.first, rhs.first));
                    }
            };

        protected:
            rb_tree _tree;

        public:
            /* Constructors and Destructor */

            explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

            template <typename InputIt>
            map(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
                    typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0);

            map(const map& other);
            map&    operator=(const map& other);

            ~map();
    };
}
