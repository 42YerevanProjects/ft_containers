#pragma once

#include <cstddef>
#include "type_traits.hpp"
#include "random_iterator.hpp"
#include "reverse_iterator.hpp"


namespace ft
{
    /*
    ==============================
        Iterator Base Class
    ==============================
    */

    template <class Category, class T, class Distance = ptrdiff_t,
                class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef T           value_type;
        typedef Pointer     pointer;
        typedef Reference   rference;
        typedef Distance    difference_type;
        typedef Category    iterator_category;
    };
}
