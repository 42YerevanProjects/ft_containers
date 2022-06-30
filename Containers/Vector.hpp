#pragma once

#include "../Iterators/RandomIt.hpp"
#include <cstdint>
#include <memory>

namespace ft 
{

    template<class T, class Alloc = std::allocator<T>>
    class vector 
    {
        public:
            typedef T                       value_type;
            typedef Alloc                   alloc_type;
            typedef T&                      reference;
            typedef const T&                const_reference;
            typedef T*                      pointer;
            typedef const T*                const_pointer;
            
            /* Iterators of Vector */
            typedef RandomIt<T, T*, T&>                 iterator;
            typedef RandomIt<T, const T*, const T&>     const_iterator;
            typedef RevRandomIt<T, T*, T&>              reverse_iterator;
            typedef RevRandomIt<T, const T*, const T&>  const_reverse_iterator;

        private:
            allloc_type alloc;
            pointer     data;
            size_t      cap;
            size_t      len;

        public:
            /* Constructers and Destructer */
            explicit vector(const alloc_type& alloc = alloc_type());
            explicit vector (size_t n, const value_type& val = value_type(), const alloc_type& alloc = alloc_type());

            vector(iterator first, iterator last, const alloc_type& alloc = alloc_type());
            vector(cont_iterator first, const_iterator last, const alloc_type& alloc = alloc_type());

            vector(const vector& other);
            vector& operator=(const vector& other);

            ~vector();

    };
}
