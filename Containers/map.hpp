#pragma once

#include "../Includes/utility.hpp"
#include <stdexcept>

namespace ft
{
    template < 
              class Key,
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
            typedef typename Alloc::template rebind<value_type>::other                                              pair_allocator;
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

            virtual ~map();

            /* Iterator Functions */

            iterator                    begin();
            const_iterator              begin() const;
            iterator                    end();
            const_iterator              end() const;

            reverse_iterator            rbegin();
            const_reverse_iterator      rbegin() const;
            reverse_iterator            rend();
            const_reverse_iterator      rend() const;

            /* Capacity Functions */

            size_type                   size() const;
            size_type                   max_size() const;
            bool                        empty() const;

            /* Element Access Functions */

            mapped_type&                at(const key_type& k);
            mapped_type&                operator[](const key_type& k);

            /* Modifier Functions */

            ft::pair<iterator, bool>    insert(const value_type& val);
            iterator                    insert(iterator position, const value_type& val);

            template <typename InputIt>
            void                        insert(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0);

            size_type                   erase(const key_type& k);
            void                        erase(iterator position);
            void                        erase(iterator first, iterator last);

            void                        swap(map& x);
            void                        clear();

            /* Observer Functions */

            key_compare                 key_comp() const;
            value_compare               value_comp() const;

            /* Lookup Operation Functions */

            iterator                    find(const key_type& k);
            const_iterator              find(const key_type& k) const;

            size_type                   count(const key_type& k) const;

            iterator                    lower_bound(const key_type& k);
            const_iterator              lower_bound(const key_type& k) const;
            iterator                    upper_bound(const key_type& k);
            const_iterator              upper_bound(const key_type& k) const;

            ft::pair<iterator, iterator>                equal_range(const key_type& k);
            ft::pair<const_iterator, const_iterator>    equal_range(const key_type& k) const;

            /* Allocator Object Copy */

            allocator_type              get_allocator() const;

        private:
            template <typename Key1, typename T1, typename Compare1, typename Alloc1>
            friend bool operator<(const map<Key1, T1, Compare1, Alloc1>&, const map<Key1, T1, Compare1, Alloc1>&);

            template <typename Key1, typename T1, typename Compare1, typename Alloc1>
            friend bool operator==(const map<Key1, T1, Compare1, Alloc1>&, const map<Key1, T1, Compare1, Alloc1>&);
    };
}

#include "Impl/mapImpl.tpp"
