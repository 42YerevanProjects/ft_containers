#pragma once

#include "../Iterators/andomIt.hpp"
#include "../Iterators/RevRandomIt.hpp"
#include <cstdint>
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
            typedef RandomIt<T, T*, T&>                 iterator;
            typedef RandomIt<T, const T*, const T&>     const_iterator;
            typedef RevRandomIt<T, T*, T&>              reverse_iterator;
            typedef RevRandomIt<T, const T*, const T&>  const_reverse_iterator;

        private:
            allocator_type  alloc;
            pointer         data;
            size_type       cap;
            size_type       len;

        public:
            /* Constructers and Destructer */
            explicit vector(const allocator_type& alloc = allocator_type());
            explicit vector (size_t n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

            vector(iterator first, iterator last, const allocator_type& alloc = allocator_type());
            vector(const_iterator first, const_iterator last, const allocator_type& alloc = allocator_type());

            vector(const vector& other);
            vector& operator=(const vector& other);

            ~vector();

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
            void		            assign(iterator first, iterator last);
			void		            assign(const_iterator first, const_iterator last);
            void		            assign(size_type n, const value_type& val);
            void                    push_back(const value_type& val);
            void                    pop_back();
            void                    insert(iterator position, size_type n, const value_type& val);
            void                    insert(iterator position, iterator first, iterator last);
            void                    insert(iterator position, const_iterator first, const_iterator last);
            void 		            swap(vector& x);
			void		            clear();
            iterator                erase (iterator position);
            iterator                erase (iterator first, iterator last);
    };
}

