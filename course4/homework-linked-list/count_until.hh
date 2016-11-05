#pragma once

#include <iterator>

namespace course {

template<class InputIt, class T>
typename std::iterator_traits<InputIt>::difference_type
    count_until(InputIt first, InputIt last, const T& value, const T& stop)
{
    typename std::iterator_traits<InputIt>::difference_type ret = 0;
    for (; (first != last) && (*first)!=stop; ++first) {
        if (*first == value) {
            ret++;
        }
    }
    return ret;
}

}