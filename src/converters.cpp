#include "converters.hpp"

#define CHECK_FIRST_TWO_BYTES(x, n) \
for (int i = 1; i < n+1; i++) { \
    if ((x[i] & 0xC0) != 0x80) { \
        printf("Non utf-8 bit set: 0x%X\n", x[i]); \
        std::vector<std::uint32_t> ret; \
        return ret; \
    } \
}

std::vector<std::uint8_t> to_utf8(const std::vector<std::uint32_t> &x) {
    std::vector<std::uint8_t> utf_vec;
    int len = x.size();
    for (int i = 0; i < len; i++) {
        std::uint32_t elem = x[i];
        if (elem > 0 && elem < 0x80) {
            utf_vec.push_back(std::uint8_t(x[i]));
        }
        else if (elem < 0x800) {
            std::uint8_t byte1, byte2;
            byte2 = std::uint8_t((elem & 0x0000003F) | 0x00000080);
            byte1 = std::uint8_t(((elem & 0x000007C0) >> 6) | 0x000000C0);
            utf_vec.push_back(byte1);
            utf_vec.push_back(byte2);
        }
        else if (elem < 0x10000) {
            std::uint8_t byte1, byte2, byte3;
            byte3 = std::uint8_t((elem & 0x0000003F) | 0x00000080);
            byte2 = std::uint8_t(((elem & 0x00000FC0) >> 6) | 0x00000080);
            byte1 = std::uint8_t(((elem & 0x0000F000) >> 12) | 0x00000E0);
            utf_vec.push_back(byte1);
            utf_vec.push_back(byte2);
            utf_vec.push_back(byte3);
        }
        else if (elem < 0x200000) {
            std::uint8_t byte1, byte2, byte3, byte4;
            byte4 = std::uint8_t((elem & 0x0000003F) | 0x00000080);
            byte3 = std::uint8_t(((elem & 0x00000FC0) >> 6) | 0x00000080);
            byte2 = std::uint8_t(((elem & 0x0003F000) >> 12) | 0x0000080);
            byte1 = std::uint8_t(((elem & 0x001C0000) >> 18) | 0x000000F0);
            utf_vec.push_back(byte1);
            utf_vec.push_back(byte2);
            utf_vec.push_back(byte3);
            utf_vec.push_back(byte4);

        }
        else if (elem < 0x4000000) {
            std::uint8_t byte1, byte2, byte3, byte4, byte5;
            byte5 = std::uint8_t((elem & 0x0000003F) | 0x00000080);
            byte4 = std::uint8_t(((elem & 0x00000FC0) >> 6) | 0x00000080);
            byte3 = std::uint8_t(((elem & 0x0003F000) >> 12) | 0x0000080);
            byte2 = std::uint8_t(((elem & 0x00FC0000) >> 18) | 0x00000080);
            byte1 = std::uint8_t(((elem & 0x03000000) >> 24) | 0x000000F8);
            utf_vec.push_back(byte1);
            utf_vec.push_back(byte2);
            utf_vec.push_back(byte3);
            utf_vec.push_back(byte4);
            utf_vec.push_back(byte5);
        }
        else if (elem < 0x80000000) {
            std::uint8_t byte1, byte2, byte3, byte4, byte5, byte6;
            byte6 = std::uint8_t((elem & 0x0000003F) | 0x00000080);
            byte5 = std::uint8_t(((elem & 0x00000FC0) >> 6) | 0x00000080);
            byte4 = std::uint8_t(((elem & 0x0003F000) >> 12) | 0x0000080);
            byte3 = std::uint8_t(((elem & 0x00FC0000) >> 18) | 0x00000080);
            byte2 = std::uint8_t(((elem & 0x3F000000) >> 24) | 0x00000080);
            byte1 = std::uint8_t(((elem & 0x40000000) >> 30) | 0x000000FC);
            utf_vec.push_back(byte1);
            utf_vec.push_back(byte2);
            utf_vec.push_back(byte3);
            utf_vec.push_back(byte4);
            utf_vec.push_back(byte5);
            utf_vec.push_back(byte6);
        }
        else {
            printf("Too big number: 0x%X\nMaximal number is 0x%X\n", elem, 0x7FFFFFFF);
            std::vector<std::uint8_t> ret;
            return ret;
        }
    }
    return utf_vec;
}


std::vector<std::uint32_t> from_utf8(const std::vector<std::uint8_t> &x) {
    std::vector<std::uint32_t> ret_vec;
    int len = x.size();
    int i = 0;
    while (i < len) {
        std::uint8_t elem = x[i];
        if (elem >> 7 == 0) {
            ret_vec.push_back(std::uint32_t(elem));
            i++;
        }
        else if (elem >> 5 == 0b110) {
            std::uint32_t qbyte1, qbyte2;
            CHECK_FIRST_TWO_BYTES(x, 1)
            qbyte1 = std::uint32_t(x[i] & 0x1F) << 6;
            qbyte2 = std::uint32_t(x[i+1] & 0x3F);
            ret_vec.push_back(qbyte1 + qbyte2);
            i += 2;
        }
        else if (elem >> 4 == 0b1110) {
            std::uint32_t qbyte1, qbyte2, qbyte3;
            CHECK_FIRST_TWO_BYTES(x, 2)
            qbyte1 = std::uint32_t(x[i] & 0x0F) << 12;
            qbyte2 = std::uint32_t(x[i+1] & 0x3F) << 6;
            qbyte3 = std::uint32_t(x[i+2] & 0x3F);
            ret_vec.push_back(qbyte1 + qbyte2 + qbyte3);
            i += 3;
        }
        else if (elem >> 3 == 0b11110) {
            std::uint32_t qbyte1, qbyte2, qbyte3, qbyte4;
            CHECK_FIRST_TWO_BYTES(x, 3)
            qbyte1 = std::uint32_t(x[i] & 0x07) << 18;
            qbyte2 = std::uint32_t(x[i+1] & 0x3F) << 12;
            qbyte3 = std::uint32_t(x[i+2] & 0x3F) << 6;
            qbyte4 = std::uint32_t(x[i+3] & 0x3F);
            ret_vec.push_back(qbyte1 + qbyte2 + qbyte3 + qbyte4);
            i += 4;
        }
        else if (elem >> 2 == 0b111110) {
            std::uint32_t qbyte1, qbyte2, qbyte3, qbyte4, qbyte5;
            CHECK_FIRST_TWO_BYTES(x, 4)
            qbyte1 = std::uint32_t(x[i] & 0x03) << 24;
            qbyte2 = std::uint32_t(x[i+1] & 0x3F) << 18;
            qbyte3 = std::uint32_t(x[i+2] & 0x3F) << 12;
            qbyte4 = std::uint32_t(x[i+3] & 0x3F) << 6;
            qbyte5 = std::uint32_t(x[i+4] & 0x3F);
            ret_vec.push_back(qbyte1 + qbyte2 + qbyte3 + qbyte4 + qbyte5);
            i += 5;
        }
        else {
            std::uint32_t qbyte1, qbyte2, qbyte3, qbyte4, qbyte5, qbyte6;
            CHECK_FIRST_TWO_BYTES(x, 5)
            qbyte1 = std::uint32_t(x[i] & 0x01) << 30;
            qbyte2 = std::uint32_t(x[i+1] & 0x3F) << 24;
            qbyte3 = std::uint32_t(x[i+2] & 0x3F) << 18;
            qbyte4 = std::uint32_t(x[i+3] & 0x3F) << 12;
            qbyte5 = std::uint32_t(x[i+4] & 0x3F) << 6;
            qbyte6 = std::uint32_t(x[i+5] & 0x3F);
            ret_vec.push_back(qbyte1 + qbyte2 + qbyte3 + qbyte4 + qbyte5 + qbyte6);
            i += 6;
        }
    }
    return ret_vec;
}
