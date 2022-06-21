#pragma once

#include "Iterators/RandomIt.hpp"

namespace ft 
{

    template<class T, class Alloc = std::alocator<T>>
    class vector 
    {
        public:
            typedef T                       value_type;
            typedef Alloc                   alloc_type;
            typedef T&                      reference;
            typedef const T&                const_reference;
            typedef T*                      pointer;
            typedef const T*                const_pointer;
            
            /* To Be implemented... */
            typedef RandomIt<T, T*, T&>                 iterator;
            typedef RandomIt<T, const T*, const T&>     const_iterator;
            typedef RevRandomIt<T, T*, T&>              reverse_iterator;
            typedef RevRandomIt<T, const T*, const T&>  const_reverse_iterator;
        
    };
}
