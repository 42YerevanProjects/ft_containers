#pragma once

#include "iterator.hpp"

/*
==============================
    Random Access Iterator
==============================
*/

namespace ft
{

    template<typename T>
    class random_iterator : ft::iterator<ft::random_access_iterator_tag, T>
    {
        public:
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type        value_type;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer           pointer;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference         reference;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type   difference_type;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
    
        protected:
            pointer _elem;
    
        public:
            /* Constructors and Destructor */
    
            random_iterator();
            random_iterator(pointer ptr);
            random_iterator(const random_iterator& other);
            operator random_iterator<const T> () const;
            virtual ~random_iterator();
    
            /* Operator Overloads */
            
            random_iterator<T>&    operator=(const random_iterator& other);
    
            random_iterator<T>     operator++(int);
            random_iterator<T>&    operator++();
    
            random_iterator<T>     operator+(difference_type n) const;
            random_iterator<T>&    operator+=(difference_type n);
    
            random_iterator<T>     operator--(int);
            random_iterator<T>&    operator--();
    
            random_iterator<T>     operator-(difference_type n) const;
            difference_type        operator-(random_iterator<T> it) const;
    
            random_iterator<T>&    operator-=(difference_type n);
    
            reference              operator*();
            pointer                operator->();
            reference              operator[](difference_type n);

            /* The base function */

            pointer               base() const;

    
            /* Equality Checks */
    
            bool                   operator==(const random_iterator& other) const;
            bool                   operator!=(const random_iterator& other) const;
            bool                   operator>=(const random_iterator& other) const;
            bool                   operator<=(const random_iterator& other) const;
            bool                   operator>(const random_iterator& other) const;
            bool                   operator<(const random_iterator& other) const;
    };
}

#include "Impl/random_iteratorImpl.tpp"
