#pragma once
#include "config.hh"

struct tvbuff { // NOLINT: typo
    // may be null, if zero-length, or lazily constructed
    const uint8_t *data   = nullptr;
    int            length = 0;

    tvbuff(const uint8_t *data, int len) : data(data), length(len) {}

    uint16_t ntohs(int offset) {
        return (offset + 2) <= length ? n2uint16(data + offset) : 0;
    };
    uint8_t uint8(int offset) const { return offset < length ? data[offset] : 0; }

    int     remain(int offset) const { return length - offset; }
};

