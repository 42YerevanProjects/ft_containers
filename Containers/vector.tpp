#pragma once

#include <cstdint>
#include <memory>

namespace ft{

    template <class T, class Alloc>
    vector<T, Alloc>::vector(const allocator_type& alloc)
    {
        this->alloc = alloc;
        this->data = NULL;
        this->len = 0;
        this->cap = 0;
    }

    template <class T, class Alloc>
    vector<T, Alloc>::~vector() {}
}
