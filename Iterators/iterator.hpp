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


    /*
    ==============================
        Iterator Tag Checks
    ==============================
    */

    template<bool is_valid, class T>
    struct valid_iterator_tag_res
    {
        typedef T   type;
        static const bool value = is_valid;
    };

    template<class T>
    struct is_iterator_tagged : valid_iterator_tag_res<false, T> {};

    template<>
    struct is_iterator_tagged<ft::random_access_iterator_tag> 
        : valid_iterator_tag_res<true, ft::random_access_iterator_tag> {};

    template<>
    struct is_iterator_tagged<ft::bidirectional_iterator_tag> 
        : valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> {};

    template<>
    struct is_iterator_tagged<ft::forward_iterator_tag> 
        : valid_iterator_tag_res<true, ft::forward_iterator_tag> {};

    template<>
    struct is_iterator_tagged<ft::input_iterator_tag> 
        : valid_iterator_tag_res<true, ft::input_iterator_tag> {};

    template<>
    struct is_iterator_tagged<ft::output_iterator_tag> 
        : valid_iterator_tag_res<true, ft::output_iterator_tag> {};
}


