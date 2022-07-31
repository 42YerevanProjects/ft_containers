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
            node*           _root;
            key_compare     _comp;
            node_allocator  _alloc;
            size_type       _size;
            base_ptr        _sentinel;


        public:
            /* Constructors and Destructor */
    
            explicit rb_tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

            template <typename InputIterator>
            rb_tree(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

            rb_tree(const rb_tree& other);
            rb_tree&    operator=(const rb_tree& other);

            virtual ~rb_tree();

            /* Iterator Functions */

            iterator                begin();
            const_iterator          begin() const;
            iterator                end();
            const_iterator          end() const;

            reverse_iterator        rbegin();
            const_reverse_iterator  rbegin() const;
            reverse_iterator        rend();
            const_reverse_iterator  rend() const;

            /* Capacity Functions */

            size_type               size();
            size_type               max_size();
            bool                    empty();

            /* Modifier Functions */

            iterator                insert(const_iterator position, const value_type& val);
            iterator                insert(iterator position, const value_type& val);
            
            template <typename InputIterator>
            void                    insert(InputIterator first, InputIterator last);

            void                    erase(iterator position);
            void                    erase(const_iterator position);
            size_type               erase(const key_type& k);

            template <typename InputIterator>
            void                    erase(InputIterator first, InputIterator last);

            void                    swap(rb_tree& x);
            void                    clear();

            /* Observer functions */

            key_compare             key_comp() const;

            /* Operations Functions */

            iterator                find(const key_type& k);
            const_iterator          find(const key_type& k) const;
            size_type               count(const key_type& k) const;
            iterator                lower_bound(const key_type& k);
            const_iterator          lower_bound(const key_type& k) const;
            iterator                upper_bound(const key_type& k);
            const_iterator          upper_bound(const key_type& k) const;

            /* Allocator Object Copy */

            allocator_type          get_allocator() const;
        

        protected:
            /* Insert & Delete Utility Functions */

            void                    insert_fixup(base_ptr z);
            void                    erase_fixup(base_ptr x);
            void                    left_rotate(base_ptr x);
            void                    right_rotate(base_ptr x);
            void                    transplant(base_ptr u, base_ptr v);
    };
}
