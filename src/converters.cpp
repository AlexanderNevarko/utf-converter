#include "converters.hpp"

using namespace std;

std::vector<uint8_t> to_utf8(const std::vector<uint32_t> &x) {
    std::vector<uint8_t> utf_vec;
    int len = x.size();
    for (int i = 0; i < len; i++) {
        uint32_t elem = x[i];
        if (elem > 0 && elem < 128) {
            utf_vec.push_back(uint8_t(x[i]));
        }
        else if (elem < 2048) {
            uint8_t byte1, byte2;
            byte2 = uint8_t(elem & 0x0000003F | 0x00000080);
            byte1 = uint8_t(((elem & 0x000007C0) >> 6) | 0x000000C0);
            utf_vec.push_back(byte1);
            utf_vec.push_back(byte2);
        }
        else if (elem < 65536) {
            uint8_t byte1, byte2, byte3;
            byte3 = uint8_t(elem & 0x0000003F | 0x00000080);
            byte2 = uint8_t(((elem & 0x00000FC0) >> 6) | 0x00000080);
            byte1 = uint8_t(((elem & 0x0000F000) >> 12) | 0x00000E0);
            utf_vec.push_back(byte1);
            utf_vec.push_back(byte2);
            utf_vec.push_back(byte3);
        }
        else if (elem < 1112065) {
            uint8_t byte1, byte2, byte3, byte4;
            byte4 = uint8_t(elem & 0x0000003F | 0x00000080);
            byte3 = uint8_t(((elem & 0x00000FC0) >> 6) | 0x00000080);
            byte2 = uint8_t(((elem & 0x0000F000) >> 12) | 0x0000080);
            byte1 = uint8_t(((elem & 0x001C0000) >> 18) | 0x000000F0);
            utf_vec.push_back(byte1);
            utf_vec.push_back(byte2);
            utf_vec.push_back(byte3);
            utf_vec.push_back(byte4);

        }
        else if (elem < 0x7FFFFFFF) {
            uint8_t byte1, byte2, byte3, byte4, byte5;
            byte5 = uint8_t(elem & 0x0000003F | 0x00000080);
            byte4 = uint8_t(((elem & 0x00000FC0) >> 6) | 0x00000080);
            byte3 = uint8_t(((elem & 0x0000F000) >> 12) | 0x0000080);
            byte2 = uint8_t(((elem & 0x001C0000) >> 18) | 0x00000080);
            byte1 = uint8_t(((elem & 0x03000000) >> 24) | 0x000000F8);
            utf_vec.push_back(byte1);
            utf_vec.push_back(byte2);
            utf_vec.push_back(byte3);
            utf_vec.push_back(byte4);
            utf_vec.push_back(byte5);
        }
        else {
            uint8_t byte1, byte2, byte3, byte4, byte5, byte6;
            byte6 = uint8_t(elem & 0x0000003F | 0x00000080);
            byte5 = uint8_t(((elem & 0x00000FC0) >> 6) | 0x00000080);
            byte4 = uint8_t(((elem & 0x0000F000) >> 12) | 0x0000080);
            byte3 = uint8_t(((elem & 0x001C0000) >> 18) | 0x00000080);
            byte2 = uint8_t(((elem & 0x03000000) >> 24) | 0x00000080);
            byte1 = uint8_t(((elem & 0x40000000) >> 30) | 0x000000FC);
            utf_vec.push_back(byte1);
            utf_vec.push_back(byte2);
            utf_vec.push_back(byte3);
            utf_vec.push_back(byte4);
            utf_vec.push_back(byte5);
            utf_vec.push_back(byte6);
        }
    }
    return utf_vec;
}


std::vector<uint32_t> from_utf8(const std::vector<uint8_t> &x) {
    return NULL;
}
