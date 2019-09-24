#pragma once
#include "config.hh"

struct bufview { // NOLINT: typo
    const uint8_t *data   = nullptr;
    int            length = 0;

    bufview(const uint8_t *data, int len) : data(data), length(len) {}

    [[nodiscard]] uint16_t uint16(int offset) const;
    [[nodiscard]] uint8_t  uint8(int offset) const;
};

inline uint16_t bufview::uint16(int offset) const {
    return data && ((offset + 2) <= length) ? n2uint16(data + offset) : 0;
}

inline uint8_t bufview::uint8(int offset) const {
    return data && (offset < length) ? data[offset] : 0;
}
