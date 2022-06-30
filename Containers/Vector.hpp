#pragma once

#include "../Iterators/RandomIt.hpp"
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

            /* Iterator functions */
            iterator                begin();
            iterator                end();

            const_iterator          begin() const;
            const_iterator          end() const;

            reverse_iterator        rbegin();
            reverse_iterator        rend();

            const_reverse_iterator  rbegin() const;
            const_reverse_iterator  rend() const;
    };
}
