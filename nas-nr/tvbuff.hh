#pragma once
#include "config.hh"

struct tvbuff { // NOLINT: typo
    const uint8_t *data   = nullptr;
    int            length = 0;

    tvbuff(const uint8_t *data, int len) : data(data), length(len) {}

    [[nodiscard]] uint16_t ntohs(int offset) const;;
    [[nodiscard]] uint8_t uint8(int offset) const;

    [[nodiscard]] int remain(int offset) const;
};

inline uint16_t tvbuff::ntohs(int offset) const {
    return data && ((offset + 2) <= length) ? n2uint16(data + offset) : 0;
}

inline uint8_t tvbuff::uint8(int offset) const {
    return data && (offset < length) ? data[offset] : 0;
}

inline int tvbuff::remain(int offset) const { return length - offset; }
