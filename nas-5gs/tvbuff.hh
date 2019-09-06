#pragma once
#include "config.hh"

struct tvbuff { // NOLINT: typo
    const uint8_t *data   = nullptr;
    int            length = 0;

    tvbuff(const uint8_t *data, int len) : data(data), length(len) {}

    _NODISCARD uint16_t ntohs(int offset) const {
        return data && ((offset + 2) <= length) ? n2uint16(data + offset) : 0;
    };
    _NODISCARD uint8_t uint8(int offset) const { return data && (offset < length) ? data[offset] : 0; }

    _NODISCARD int remain(int offset) const { return length - offset; }
};

