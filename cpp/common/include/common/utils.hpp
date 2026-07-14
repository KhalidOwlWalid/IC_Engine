#pragma once

#include <vector>

namespace ice {

template <typename T>
inline std::vector<T> linear_array(T start, T stop, T step) {
    std::vector<T> tmp;
    assert(stop > start);
    size_t size = static_cast<size_t>(std::ceil((stop - start)/step));
    tmp.reserve(size);
    
    for (size_t i = 0; i < size; i++) {
        tmp.push_back(start + i * step);
    };

    return tmp;
};

}