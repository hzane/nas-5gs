#pragma once
#include "config.hh"

struct tvbuff { // NOLINT: typo
    const uint8_t *data   NASNR_EQUAL_INIT( nullptr);
    int            length NASNR_EQUAL_INIT( 0);

    tvbuff(const uint8_t *data, int len) : data(data), length(len) {}

    uint16_t ntohs(int offset) const;;
    uint8_t uint8(int offset) const;

    int remain(int offset) const;
};

inline uint16_t tvbuff::ntohs(int offset) const {
    return data && ((offset + 2) <= length) ? n2uint16(data + offset) : 0;
}

inline uint8_t tvbuff::uint8(int offset) const {
    return data && (offset < length) ? data[offset] : 0;
}

inline int tvbuff::remain(int offset) const { return length - offset; }
