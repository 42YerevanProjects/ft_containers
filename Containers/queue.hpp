#pragma once

#include <deque>

namespace ft
{
    template<class T, class Container = std::deque<T> >
    class queue
    {
        public:
            typedef T           value_type;
            typedef size_t      size_type;
            typedef Container   container_type;

        protected:
            container_type  _ctnr;

        public:
                /* Constructor and Destructor */

                explicit queue(const container_type& ctnr = container_type());
                ~queue();

                /* Capacity Functions */

                size_type           size() const;
                bool                empty() const;

                /* Element Access Functions */

                value_type&         front();
                const value_type&   front() const;

                value_type&         back();
                const value_type&   back() const;

                /* Element Modifier Functions */

                void                push(const value_type& val);
                void                pop();
                void                swap(queue& x);

                /* Non-Member Functions */
                
                template<class U, class Cont>
                friend bool         operator==(const queue<U, Cont>&, const queue<U, Cont>&);

                template<class U, class Cont>
                friend bool         operator<(const queue<U, Cont>&, const queue<U, Cont>&);
    };
}

#include "Impl/queueImpl.tpp"
