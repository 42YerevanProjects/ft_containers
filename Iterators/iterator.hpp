#pragma once

#include "type_traits.hpp"

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
        typedef Reference   reference;
        typedef Distance    difference_type;
        typedef Category    iterator_category;
    };
}
