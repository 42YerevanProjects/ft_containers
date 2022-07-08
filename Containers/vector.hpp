#pragma once

#include "../Iterators/random_iterator.hpp"
#include "../Iterators/reverse_iterator.hpp"
#include <memory>

namespace ft 
{

    template<class T, class Alloc = std::allocator<T> >
    class vector 
    {
        public:
            typedef T                       value_type;
            typedef Alloc                   allocator_type;
            typedef T&                      reference;
            typedef const T&                const_reference;
            typedef T*                      pointer;
            typedef const T*                const_pointer;
            typedef size_t                  size_type;
            
            /* Iterators of Vector */
            typedef ft::random_iterator<T>                  iterator;
            typedef ft::random_iterator<const T>            const_iterator;
            typedef ft::reverse_iterator<iterator>          reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

        protected:
            allocator_type  _alloc;
            pointer         _data;
            size_type       _size;
            size_type       _cap;

        public:
            /* Constructers and Destructer */
            explicit vector(const allocator_type& alloc = allocator_type());
            explicit vector (size_t n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

            template<typename InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0);

            vector(const vector& other);
            vector& operator=(const vector& other);

            virtual ~vector();

            /* Iterator Functions */
            iterator                begin();
            iterator                end();
            reverse_iterator        rbegin();
            reverse_iterator        rend();

            const_iterator          begin() const;
            const_iterator          end() const;
            const_reverse_iterator  rbegin() const;
            const_reverse_iterator  rend() const;

            /* Capacity Functions */
            size_type               size() const;
            size_type               max_size() const;
            size_type               capacity() const;
            bool                    empty() const;
            void                    reserve(size_type n);
            void                    resize(size_type n, value_type val = value_type());

            /* Element Access Functions */
            reference               operator[](size_type n);
            const_reference         operator[](size_type n) const;

            reference               at(size_type n);
            const_reference         at(size_type n) const;

            reference               front();
            reference               back();
            const_reference         front() const;
            const_reference         back() const;

            /* Modifier Functions */
            template<typename InputIterator>
            void                    assign(InputIterator first, InputIterator last,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0);

            void                    assign(size_type n, const value_type& val);
            void                    push_back(const value_type& val);
            void                    pop_back();
            void                    insert(iterator position, size_type n, const value_type& val);
            void                    insert(iterator position, iterator first, iterator last);
            void                    insert(iterator position, const_iterator first, const_iterator last);
            void                    swap(vector& x);
            void                    clear();
            iterator                erase (iterator position);
            iterator                erase (iterator first, iterator last);

            /* Allocator Object Copy */
            allocator_type          get_allocator() const;
    };
}

#include "vector.tpp"
