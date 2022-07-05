#pragma once

#include <cstddef>
#include "type_traits.hpp"

/*
==============================
    Random Access Iterator
==============================
*/

namespace ft
{

    template<typename T>
    class random_iterator
    {
        public:
            typedef T                                                   value_type;
            typedef value_type*                                         pointer;
            typedef value_type&                                         reference;
            typedef std::ptrdiff_t                                      difference_type;
            typedef typename ft::random_access_iterator_tag             iterator_category;
    
        protected:
            pointer data_ptr;
    
        public:
            /* Constructors and Destructor */
    
            random_iterator();
            random_iterator(const pointer ptr);
            random_iterator(const random_iterator<T>& other);
            virtual ~random_iterator();
    
            /* Operator Overloads */
            
            random_iterator<T>&    operator=(const random_iterator<T>& other);
    
            random_iterator<T>     operator++(int);
            random_iterator<T>&    operator++();
    
            random_iterator<T>     operator+(size_t n) const;
            random_iterator<T>&    operator+=(size_t n);
    
            random_iterator<T>     operator--(int);
            random_iterator<T>&    operator--();
    
            random_iterator<T>     operator-(size_t n) const;
            difference_type                 operator-(random_iterator<T> it) const;
    
            random_iterator<T>&    operator-=(size_t n);
    
            reference                       operator*();
            pointer                         operator->();
            reference                       operator[](size_t n);
    
            /* Equality Checks */
    
            bool                            operator==(const random_iterator<T> &other) const;
            bool                            operator!=(const random_iterator<T> &other) const;
            bool                            operator>=(const random_iterator<T> &other) const;
            bool                            operator<=(const random_iterator<T> &other) const;
            bool                            operator>(const random_iterator<T> &other) const;
            bool                            operator<(const random_iterator<T> &other) const;
    };

}
#include "random_iterator.tpp"
