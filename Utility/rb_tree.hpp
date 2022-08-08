#pragma once

#include "rb_tree_node.hpp"
#include "functional.hpp"
#include "../Includes/iterators.hpp"
#include <memory>

namespace ft
{
    template< typename Key,
              typename Val,
              typename KeyOfValue,
              typename Compare = ft::less<Key>, 
              typename Alloc = std::allocator<Val> 
            >
    class rb_tree
    {
        private:
            typedef typename Alloc::template rebind< ft::rb_tree_node<Val> >::other    node_allocator;

        protected:
            typedef ft::rb_tree_node<Val>           node;
            typedef ft::rb_tree_node_base           base;
            typedef ft::rb_tree_node_base*          base_ptr;

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
            base            _sentinel;

        public:
            /* Constructors and Destructor */
    
            explicit rb_tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

            template <typename InputIt>
            rb_tree(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

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

            size_type               size() const;
            size_type               max_size() const;
            bool                    empty() const;

            /* Modifier Functions */

            void                    insert(const value_type& val);

            template <typename InputIterator>
            void                    insert(InputIterator first, InputIterator last);

            iterator                insert(iterator position, const value_type& val);
            iterator                insert(const_iterator position, const value_type& val);

            void                    erase(iterator position);
            void                    erase(const_iterator position);

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

            void                    hinted_insert(const value_type& val, base_ptr hint);
            void                    insert_fixup(base_ptr z);
            void                    erase_fixup(base_ptr x);
            void                    left_rotate(base_ptr x);
            void                    right_rotate(base_ptr x);
            void                    transplant(base_ptr u, base_ptr v);

            /* Key Extraction Utility Functions */

            const key_type&         extract_key(const value_type& val) const;
            const key_type&         extract_key(const base_ptr n) const;

            /* Node Check Utility Functions */

            node*                   root() const;
            bool                    is_root(const base_ptr n) const;
            bool                    is_red(const base_ptr n) const;
            bool                    is_black(const base_ptr n) const;
            bool                    is_external(const base_ptr n) const;
            bool                    is_internal(const base_ptr n) const;
            bool                    is_sentinel(const base_ptr n) const;

            /* Node Create/Delete Utility Functions */

            node*                   create_node(const value_type& val);
            void                    destroy_node(node* n);
            void                    destroy_tree(node* n);

            /* Tree min, max utility functions */

            node*                   minimum();
            node*                   maximum();
            void                    update_extremum();
    };
}

#include "rb_tree.tpp"
