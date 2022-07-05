#pragma once

#include "iterator.hpp"

/*
======================== 
    Reverse Iterator
======================== 
*/

namespace ft
{
    template<typename It>
    class reverse_iterator
    {
        public:
            typedef typename ft::iterator_traits<It>::type              value_type;
            typedef typename ft::iterator_traits<It>::pointer           pointer;
            typedef typename ft::iterator_traits<It>::reference         reference;
            typedef typename ft::iterator_traits<It>::difference_type   difference_type;
            typedef typename ft::iterator_traits<It>::iterator_category iterator_category;
            typedef It                                                  iterator_type;

        protected:
            iterator_type  _base;

        public:
            /* Constructors and Destructor */

            reverse_iterator();
            explicit reverse_iterator(iterator_type it);

            template<class Iter>
            reverse_iterator(const reverse_iterator<Iter>& rev_it);

            virtual ~reverse_iterator();

            /* Operator Overloads */
            
            reverse_iterator<It>&    operator=(const reverse_iterator& other);

            reverse_iterator<It>    operator++(int);
            reverse_iterator<It>&   operator++();

            reverse_iterator<It>    operator--(int);
            reverse_iterator<It>&   operator--();

            reverse_iterator<It>    operator+(difference_type n) const;
            reverse_iterator<It>    operator-(difference_type n) const;

            reverse_iterator<It>&   operator+=(difference_type n);
            reverse_iterator<It>&   operator-=(difference_type n);

            reference               operator*() const;
            pointer                 operator->() const;
            reference               operator[](difference_type n) const;

            /* Return Base Iterator */

            iterator_type           base() const;
    };
}

#include "reverse_iterator.tpp"
