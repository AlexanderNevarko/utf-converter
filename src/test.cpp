#include <iostream>
#include <iomanip>
#include <assert.h>
#include "converters.hpp"

int main() {
    std::vector<std::uint32_t> vec = {3212, 32, 32413, 543};
    std::vector<std::uint32_t> _vec = from_utf8(to_utf8(vec));
    assert(vec.size() == _vec.size());
    for (int i = 0; i < vec.size(); i++) {
        //printf("orig: %d, from_utf8(to_utf8(orig)): %d\n ", vec[i], _vec[i]);
        std::cout << "original" << std::setw(12) << vec[i] << std::setw(30)
        << "from_utf8(to_utf8(orig))" << std::setw(12) << _vec[i] << std::endl;
    }
    
    return 0;
}
