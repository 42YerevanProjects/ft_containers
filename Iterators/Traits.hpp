#pragma once

namespace ft
{

    /*
    ==============================
        Iterator Category Tags
    ==============================
    */

    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};


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
}
