#pragma once

namespace ft
{
    template<typename T, typename U>
    struct pair
    {
            typedef T   first_type;
            typedef U   second_type;

            first_type  first;
            second_type second;

            /* Constructors and Desteructor */

            pair() : first(), second() {}

            pair(const first_type& a, const second_type& b) : first(a),  second(b) {}

            template<typename V1, typename V2>
            pair(const pair<V1, V2>& x) : first(x.first), second(x.second) {}

            pair&   operator=(const pair& x)
            {
                this->first = x.first;
                this->second = x.second;
                return (*this);
            }

            ~pair() {}
    };

    /* Comparison Operator Overloads */

    template <class T1, class T2>
    bool operator==(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template <class T1, class T2>
    bool operator!=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T1, class T2>
    bool operator<(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
    {
        return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
    }

    template <class T1, class T2>
    bool operator<=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
     {
         return !(rhs < lhs);
     }

    template <class T1, class T2>
    bool operator>(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
    {
         return (rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
    {
        return !(lhs < rhs);
    }

    /* A function that constructs a pair opject with given parameters */

    template <class T1, class T2>
    pair<T1,T2> make_pair(T1 x, T2 y)
    {
        return (pair<T1, T2>(x, y));
    }
}
