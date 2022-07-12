#pragma once

#include "vector.hpp"

namespace ft
{
    /*
    ===================================
        Constructor and Destructeor
    ===================================
    */

    template<class T, class Container>
    stack<T, Container>::stack(const container_type& ctnr) : _ctnr(ctnr) {}

    template<class T, class Container>
    stack<T, Container>::~stack() {}

    /*
    ========================== 
        Capacity Functions
    ========================== 
    */

    template<class T, class Container>
    typename stack<T, Container>::size_type         stack<T, Container>::size() const { return _ctnr.size(); }

    template<class T, class Container>
    bool                                            stack<T, Container>::empty() const { return _ctnr.empty(); }

    /*
    ================================ 
        Element Access Functions
    ================================ 
    */

    template<class T, class Container>
    typename stack<T, Container>::value_type&       stack<T, Container>::top() { return _ctnr.back(); }

    template<class T, class Container>
    const typename stack<T, Container>::value_type& stack<T, Container>::top() const { return _ctnr.back(); }

    /*
    ================================== 
        Element Modifier Functions
    ==================================
    */

    template<class T, class Container>
    void                                    stack<T, Container>::push(const value_type& val) { return _ctnr.push_back(val); }

    template<class T, class Container>
    void                                    stack<T, Container>::pop() { return _ctnr.pop_back(); }

    template<class T, class Container>
    void                                    stack<T, Container>::swap(stack& x) { return _ctnr.swap(x._ctnr); }

    /*
    ============================ 
        Non-member Functions
    ============================
    */

    template<class T, class Container>
    bool    operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return (lhs._ctnr == rhs._ctnr); }

    template<class T, class Container>
    bool    operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return !(lhs == rhs); }

    template<class T, class Container>
    bool    operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return !(rhs < lhs); }

    template<class T, class Container>
    bool    operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return !(lhs < rhs); }

    template<class T, class Container>
    bool    operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return (lhs._ctnr < rhs._ctnr); }

    template<class T, class Container>
    bool    operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return (rhs > lhs); }
}
