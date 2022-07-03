#pragma once

#include <cstdlib>

/*
======================================
    Reverse Random Access Iterator
======================================
*/

template<typename T, bool isConst = false>
class RevRandomIt
{
    public:
        typedef typename ft::conditional<isConst, T, const T>::type value_type;
        typedef value_type*                                         pointer;
        typedef value_type&                                         reference;
        typedef std::ptrdiff_t                                      difference_type;
        typedef typename ft::random_access_iterator_tag             iterator_category;

    private:
        pointer data_ptr;

    public:
        /* Constructors and Destructor */

        RevRandomIt();
        RevRandomIt(const pointer ptr);
        RevRandomIt(const RevRandomIt<T, isConst>& other);
        ~RevRandomIt();

        /* Operator Overloads */
        
        RevRandomIt<T, isConst>&    operator=(const RevRandomIt<T, isConst>& other);

        RevRandomIt<T, isConst>     operator++(int);
        RevRandomIt<T, isConst>&    operator++();

        RevRandomIt<T, isConst>     operator+(size_t n) const;
        RevRandomIt<T, isConst>&    operator+=(size_t n);

        RevRandomIt<T, isConst>     operator--(int);
        RevRandomIt<T, isConst>&    operator--();

        RevRandomIt<T, isConst>     operator-(size_t n) const;
        difference_type             operator-(RevRandomIt<T, isConst> it) const;

        RevRandomIt<T, isConst>&    operator-=(size_t n);

        reference                   operator*();
        pointer                     operator->();
        reference                   operator[](size_t n);

        /* Equality Checks */

        bool                        operator==(const RevRandomIt<T, isConst> &other) const;
        bool                        operator!=(const RevRandomIt<T, isConst> &other) const;
        bool                        operator>=(const RevRandomIt<T, isConst> &other) const;
        bool                        operator<=(const RevRandomIt<T, isConst> &other) const;
        bool                        operator>(const RevRandomIt<T, isConst> &other) const;
        bool                        operator<(const RevRandomIt<T, isConst> &other) const;
};

#include "RevRandomIt.tpp"
