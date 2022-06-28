#pragma once

#include <cstdlib>

/*
======================================
    Reverse Random Access Iterator
======================================
*/


template<typename T, typename Pointer, typename Reference>
class RevRandomIt
{
    public:
        typedef RevRandomIt<T, Pointer, Reference> RevRandIter;
        typedef RevRandomIt<T, T*, T&>             iterator;

        Pointer data_ptr;

        /* Constructors and Destructor */

        RevRandomIt();
        RevRandomIt(const Pointer ptr);
        RevRandomIt(const iterator& other);
        ~RevRandomIt();

        /* Operator Overloads */
        
        RevRandIter&    operator=(const iterator& other);

        RevRandIter     operator++(int);
        RevRandIter&    operator++();

        RevRandIter     operator+(size_t n) const;
        RevRandIter&    operator+=(size_t n);

        RevRandIter     operator--(int);
        RevRandIter&    operator--();

        RevRandIter     operator-(size_t n) const;
        size_t          operator-(RevRandIter it) const;

        RevRandIter&    operator-=(size_t n);

        Reference       operator*();
        Pointer         operator->();
        Reference       operator[](size_t n);

        /* Equality Checks */
        bool operator==(const RevRandIter &other) const;
        bool operator!=(const RevRandIter &other) const;
};

#include "RevRandomIt.tpp"
