#pragma once

namespace ft
{
    /*
    ===================================
        Constructor and Destructeor
    ===================================
    */

    template<class T, class Container>
    queue<T, Container>::queue(const container_type& ctnr) : _ctnr(ctnr) {}

    template<class T, class Container>
    queue<T, Container>::~queue() { _ctnr.clear(); }

    /*
    ========================== 
        Capacity Functions
    ========================== 
    */

    template<class T, class Container>
    typename queue<T, Container>::size_type         queue<T, Container>::size() const { return _ctnr.size(); }

    template<class T, class Container>
    bool                                            queue<T, Container>::empty() const { return _ctnr.empty(); }

    /*
    ================================ 
        Element Access Functions
    ================================ 
    */

    template<class T, class Container>
    typename queue<T, Container>::value_type&       queue<T, Container>::front() { return _ctnr.front(); }

    template<class T, class Container>
    const typename queue<T, Container>::value_type& queue<T, Container>::front() const { return _ctnr.front(); }

    template<class T, class Container>
    typename queue<T, Container>::value_type&       queue<T, Container>::back() { return _ctnr.back(); }

    template<class T, class Container>
    const typename queue<T, Container>::value_type& queue<T, Container>::back() const { return _ctnr.back(); }

    /*
    ================================== 
        Element Modifier Functions
    ==================================
    */

    template<class T, class Container>
    void                                    queue<T, Container>::push(const value_type& val) { return _ctnr.push_back(val); }

    template<class T, class Container>
    void                                    queue<T, Container>::pop() { return _ctnr.pop_front(); }

    template<class T, class Container>
    void                                    queue<T, Container>::swap(queue& x) { return _ctnr.swap(x._ctnr); }

    /*
    ============================ 
        Non-member Functions
    ============================
    */

    template<class T, class Container>
    bool    operator==(const ft::queue<T, Container>& lhs, const ft::queue<T, Container>& rhs) { return (lhs._ctnr == rhs._ctnr); }

    template<class T, class Container>
    bool    operator!=(const ft::queue<T, Container>& lhs, const ft::queue<T, Container>& rhs) { return !(lhs == rhs); }

    template<class T, class Container>
    bool    operator<=(const ft::queue<T, Container>& lhs, const ft::queue<T, Container>& rhs) { return !(rhs < lhs); }

    template<class T, class Container>
    bool    operator>=(const ft::queue<T, Container>& lhs, const ft::queue<T, Container>& rhs) { return !(lhs < rhs); }

    template<class T, class Container>
    bool    operator<(const ft::queue<T, Container>& lhs, const ft::queue<T, Container>& rhs) { return (lhs._ctnr < rhs._ctnr); }

    template<class T, class Container>
    bool    operator>(const ft::queue<T, Container>& lhs, const ft::queue<T, Container>& rhs) { return (rhs < lhs); }
}
