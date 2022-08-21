#pragma once

#include "../Iterators/random_iterator.hpp"
#include "../Iterators/reverse_iterator.hpp"
#include "../Utility/functional.hpp"
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
            typedef ptrdiff_t               difference_type;
            typedef size_t                  size_type;
            
            /* Iterators of Vector */
            typedef ft::random_iterator<T>                  iterator;
            typedef ft::random_iterator<const T>            const_iterator;
            typedef ft::reverse_iterator<iterator>          reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

        protected:
            allocator_type  _alloc;
            pointer         _vct;
            size_type       _size;
            size_type       _cap;


        public:
            /* Constructers and Destructer */

            explicit vector(const allocator_type& alloc = allocator_type());
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

            template<typename InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0);

            vector(const vector& other);
            vector& operator=(const vector& other);

            virtual ~vector();

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

            template<typename InputIterator>
            void                    insert(iterator position, InputIterator first, InputIterator last, 
                                            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0);

            iterator                insert(iterator position, const value_type& val);
            void                    insert(iterator position, size_type n, const value_type& val);
            void                    swap(vector& x);
            void                    clear();
            iterator                erase(iterator position);
            iterator                erase(iterator first, iterator last);

            /* Allocator Object */
            
            allocator_type          get_allocator() const;


        private:
            /* Utility Functions */

            template <typename InputIterator>
            void        range_fill(InputIterator first, InputIterator last);

            template <typename InputIterator>
            pointer     deep_copy(size_type n, InputIterator first, InputIterator last);

            void        fill(size_type n, const value_type& val, pointer start);
            void        check_range(size_type n) const;
            size_type   check_size(size_type n) const;
    };
}

#include "vector.tpp"
