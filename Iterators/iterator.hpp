#pragma once

#include "type_traits.hpp"
#include <string>
#include <typeinfo>
#include <exception>

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


    /*
    ==================================
        Invalid Iterator Exception
    ==================================
    */
    
    template<typename T>
    class InvalidIteratorException : public std::exception
    {
        private:
            std::string    _msg;

        public:
            InvalidIteratorException() throw() { _msg = ("Invalid Iterator tag: " + std::string(typeid(T).name())); }
            InvalidIteratorException(const InvalidIteratorException&) throw() {}
            InvalidIteratorException& operator=(const InvalidIteratorException&) throw() {}
            virtual ~InvalidIteratorException() throw() {}
            virtual const char* what() const throw() { return (_msg.c_str()); }
    };

    /*
    ============================= 
        Distance of Iterators
    ============================= 
    */

    template<typename InputIterator>
    typename ft::iterator_traits<InputIterator>::difference_type   distance(InputIterator first, InputIterator last)
    {
        typename ft::iterator_traits<InputIterator>::difference_type dist = 0;
        
        while (first != last)
        {
            dist++;
            first++;
        }
        
        return dist;
    }

    /*
    ============================= 
        Lexicographic Compare
    ============================= 
    */

    template <class InputIterator1, class InputIterator2>
	bool    lexicographical_compare(InputIterator1 lbeg, InputIterator1 lend, InputIterator2 rbeg, InputIterator2 rend)
	{
		while (lbeg != lend)
		{
			if (rbeg == rend || *rbeg < *lbeg)
				return (false);
			else if (*lbeg < *rbeg)
				return (true);
			++lbeg, ++rbeg;
		}

		return (rbeg != rend);
	}

    /*
    ============================= 
        Compare With Equals
    ============================= 
    */

    template <class InputIterator1, class InputIterator2>
	bool    equal(InputIterator1 lbeg, InputIterator1 lend, InputIterator2 rbeg, InputIterator2 rend)
	{
		while (lbeg != lend)
		{
			if (rbeg == rend || *rbeg != *lbeg)
				return (false);
			++lbeg, ++rbeg;
		}

		return (rbeg == rend);
	}
}

