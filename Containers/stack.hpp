#pragma once

#include "vector.hpp"

namespace ft
{
    template<class T, class Container = ft::vector<T> >
    class stack
    {
        public:
            typedef T           value_type;
            typedef size_t      size_type;
            typedef Container   container_type;

        protected:
            container_type  _ctnr;

        public:
                /* Constructor and Destructor */

                explicit stack(const container_type& ctnr = container_type());
                ~stack();

                /* Capacity Functions */

                size_type           size() const;
                bool                empty() const;

                /* Element Access Functions */

                value_type&         top();
                const value_type&   top() const;

                /* Element Modifier Functions */

                void                push(const value_type& val);
                void                pop();
                void                swap(stack& x);

                /* Non-Member Functions */
                
                template<class U, class Cont>
                friend bool         operator==(const stack<U, Cont>&, const stack<U, Cont>&);

                template<class U, class Cont>
                friend bool         operator<(const stack<U, Cont>&, const stack<U, Cont>&);
    };
}
#include "stack.tpp"
