#pragma once

/*
==============================
    Random Access Iterator
==============================
*/


template<typename T, typename Pointer, typename Reference>
class RandomIt
{
    public:
        typedef RandomIt<T, Pointer, Reference> RandIter;
        typedef RandomIt<T, T*, T&>             iterator;
   
        /* To be continued... */
};
