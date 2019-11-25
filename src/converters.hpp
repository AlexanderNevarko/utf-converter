#ifndef __CONVERTERS_H_INCLUDED__
#define __CONVERTERS_H_INCLUDED__

#include <vector>

std::vector<uint8_t> to_utf8(const std::vector<uint32_t> &x);
std::vector<uint32_t> from_utf8(const std::vector<uint8_t> &x);


#endif
