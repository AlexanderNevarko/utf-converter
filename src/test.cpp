#include <iostream>
#include "converters.hpp"

int main() {
    std::vector<std::uint32_t> vec(5, 2324);
    std::vector<std::uint8_t> utf_vec = to_utf8(vec);
    for (int i = 0; i < utf_vec.size(); i++) {
        printf("%d ", utf_vec[i]);
    }
    
    return 0;
}
