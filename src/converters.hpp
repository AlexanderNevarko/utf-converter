#ifndef __CONVERTERS_H_INCLUDED__
#define __CONVERTERS_H_INCLUDED__

#include <vector>
#include <iostream>

std::vector<std::uint8_t> to_utf8(const std::vector<std::uint32_t> &x);
std::vector<std::uint32_t> from_utf8(const std::vector<std::uint8_t> &x);


#endif
