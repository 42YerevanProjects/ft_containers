#pragma once

#include <cstddef>

namespace ft
{

    /*
    ==============================
        Iterator Category Tags
    ==============================
    */

    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : input_iterator_tag {};
    struct bidirectional_iterator_tag : forward_iterator_tag {};
    struct random_access_iterator_tag : bidirectional_iterator_tag {};


    /*
    =======================
        Iterator Traits
    =======================
    */
    
    template <class It>
	struct	iterator_traits
	{
		typedef typename It::value_type         value_type;
		typedef typename It::pointer            pointer;
		typedef typename It::reference          reference;
		typedef typename It::difference_type    difference_type;
		typedef typename It::iterator_category  iterator_category;
	};

	template <class T>
	struct	iterator_traits<T*>
	{
		typedef T                                   value_type;
		typedef T*                                  pointer;
		typedef T&                                  reference;
		typedef std::ptrdiff_t                      difference_type;
		typedef ft::random_access_iterator_tag      iterator_category;
	};

	template <class T>
	struct	iterator_traits<const T*>
	{
		typedef T                                   value_type;
		typedef const T*                            pointer;
		typedef const T&                            reference;
		typedef std::ptrdiff_t                      difference_type;
		typedef ft::random_access_iterator_tag      iterator_category;
	};


    /*
    =================
        Enable If
    =================
    */

    template <bool B, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T> { typedef T type; };


    /*
    ===================
        Conditional
    ===================
    */

    template <bool B, class T = void, class U = void>
	struct conditional {};

	template <class T, class U>
	struct conditional<false, T, U> { typedef T type; };

	template <class T, class U>
	struct conditional<true, T, U> { typedef U type; };



    /*
    ======================
        Integral types
    ======================
    */

    template <bool is_integral, typename T>
    struct is_integral_res 
    { 
        typedef T type; 
        static const bool value = is_integral; 
    };


    template <typename>
    struct is_integral_type : is_integral_res<false, bool> {};

    template <>
    struct is_integral_type<bool> : is_integral_res<true, bool> {};

    template <>
    struct is_integral_type<char> : is_integral_res<true, char> {};

    template <>
    struct is_integral_type<signed char> : is_integral_res<true, signed char> {};

    template <>
    struct is_integral_type<short int> : is_integral_res<true, short int> {};

    template <>
    struct is_integral_type<int> : is_integral_res<true, int> {};

    template <>
    struct is_integral_type<long int> : is_integral_res<true, long int> {};

    template <>
    struct is_integral_type<long long int> : is_integral_res<true, long long int> {};

    template <>
    struct is_integral_type<unsigned char> : is_integral_res<true, unsigned char> {};

    template <>
    struct is_integral_type<unsigned short int> : is_integral_res<true, unsigned short int> {};

    template <>
    struct is_integral_type<unsigned int> : is_integral_res<true, unsigned int> {};

    template <>
    struct is_integral_type<unsigned long int> : is_integral_res<true, unsigned long int> {};

    template <>
    struct is_integral_type<unsigned long long int> : is_integral_res<true, unsigned long long int> {};


    template <typename T>
    struct is_integral : is_integral_type<T> {};

}
