#pragma once

#include <cstdlib>

/*
==============================
    Random Access Iterator
==============================
*/


template<typename T, typename Pointer, typename Reference>
class RandomIt
{
    public:
        typedef RandomIt<T, Pointer, Reference> RandIter;
        typedef RandomIt<T, T*, T&>             iterator;

        Pointer data_ptr;

        /* Constructors and Destructor */

        RandomIt();
        RandomIt(const Pointer ptr);
        RandomIt(const iterator& other);
        ~RandomIt();

        /* Operator Overloads */
        
        RandIter&   operator=(const iterator& other);

        RandIter&   operator++(int);
        RandIter&   operator++();

        RandIter&   operator+(size_t n) const;
        RandIter&   operator+=(size_t n);

        RandIter&   operator--(int);
        RandIter&   operator--();

        RandIter&   operator-(size_t n) const;
        size_t      operator-(RandIter it) const;

        RandIter&   operator-=(size_t n);

        Reference   operator*();
        Pointer     operator->();
        Reference   operator[](size_t n);

        /* Equality Checks */
        bool operator==(const RandIter &other) const;
        bool operator!=(const RandIter &other) const;
};
