#pragma once

#include <string>
#include <sstream>

namespace ft
{
    /* Base class for standard unary function objects */

    template <class Arg, class Result>
    struct unary_function
    {
        typedef Arg     argument_type;

        typedef Result  result_type;
    };

    /* Base class for standard binary function objects */

    template <class Arg1, class Arg2, class Result>
    struct binary_function
    {
        typedef Arg1    first_argument_type;

        typedef Arg2    second_argument_type;

        typedef Result  result_type;    
    };

    /* A binary function object class performing the operation less then */

    template <class T>
    struct less : binary_function<T, T, bool>
    {
        bool operator() (const T& x, const T& y) const { return (x < y); }
    };

    /* A unary function object class that selscts the first parameter of a pair */

    template <class Pair>
    struct select_first : unary_function<Pair, typename Pair::first_type>
    {
        typename Pair::first_type&          operator()(Pair& x)
        {
            return (x.first);
        }

        const typename Pair::first_type&    operator()(const Pair& x)
        {
            return (x.first);
        }
    };


    /* A unary function object class that selscts the first parameter of a pair */

    template <class T>
    struct select_self : unary_function<T, T>
    {
        T&          operator()(T& x) 
        {
            return (x);
        }

        const T&    operator()(const T& x)
        {
            return (x);
        }
    };

    /* A generic swap function */

    template <typename T>
    void    swap(T& a, T& b)
    {
        T save = a;
        a = b;
        b = save;
    }

    /* A generic to_string function */

    template <typename T>
    std::string to_string(T n)
    {
        // Stream used to convert
        std::ostringstream ss;
        ss << n;
        return (ss.str());
    }
}
