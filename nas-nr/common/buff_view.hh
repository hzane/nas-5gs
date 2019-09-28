#pragma once
#include "config.hh"

struct buff_view { // NOLINT: typo
    const uint8_t *data   = nullptr;
    int            length = 0;

    buff_view(const uint8_t *data, int len) : data(data), length(len) {}

    uint16_t uint16(int offset) const;;
    uint8_t uint8(int offset) const;

    int remain(int offset) const;
};

inline uint16_t buff_view::uint16(int offset) const {
    return data && ((offset + 2) <= length) ? n2uint16(data + offset) : 0;
}

inline uint8_t buff_view::uint8(int offset) const {
    return data && (offset < length) ? data[offset] : 0;
}

inline int buff_view::remain(int offset) const { return length - offset; }
