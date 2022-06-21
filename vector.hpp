#pragma once

namespace ft 
{

    template<class T, class Alloc = std::alocator<T>>
    class vector 
    {
        public:
            typedef T               value_type;
            typedef Alloc           alloc_type;
            typedef T&              reference;
            typedef const T&        const_reference;
            typedef T*              pointer;
            typedef const T*        const_pointer;
        
    };
}
