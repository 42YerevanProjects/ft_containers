#pragma once

#include <cstddef>
#include "Traits.hpp"

/*
==============================
    Random Access Iterator
==============================
*/

template<typename T, bool isConst = false>
class RandomIt
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

        RandomIt();
        RandomIt(const pointer ptr);
        RandomIt(const RandomIt<T, isConst>& other);
        ~RandomIt();

        /* Operator Overloads */
        
        RandomIt<T, isConst>&   operator=(const RandomIt<T, isConst>& other);

        RandomIt<T, isConst>    operator++(int);
        RandomIt<T, isConst>&   operator++();

        RandomIt<T, isConst>    operator+(size_t n) const;
        RandomIt<T, isConst>&   operator+=(size_t n);

        RandomIt<T, isConst>    operator--(int);
        RandomIt<T, isConst>&   operator--();

        RandomIt<T, isConst>    operator-(size_t n) const;
        difference_type         operator-(RandomIt<T, isConst> it) const;

        RandomIt<T, isConst>&   operator-=(size_t n);

        reference               operator*();
        pointer                 operator->();
        reference               operator[](size_t n);

        /* Equality Checks */

        bool                    operator==(const RandomIt<T, isConst> &other) const;
        bool                    operator!=(const RandomIt<T, isConst> &other) const;
        bool                    operator>=(const RandomIt<T, isConst> &other) const;
        bool                    operator<=(const RandomIt<T, isConst> &other) const;
        bool                    operator>(const RandomIt<T, isConst> &other) const;
        bool                    operator<(const RandomIt<T, isConst> &other) const;
};

#include "RandomIt.tpp"
