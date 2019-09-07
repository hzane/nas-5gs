#pragma once
#include "config.hh"

struct tvbuff { // NOLINT: typo
    const uint8_t *data   = nullptr;
    int            length = 0;

    tvbuff(const uint8_t *data, int len) : data(data), length(len) {}

    [[nodiscard]] uint16_t ntohs(int offset) const {
        return data && ((offset + 2) <= length) ? n2uint16(data + offset) : 0;
    };
    [[nodiscard]] uint8_t uint8(int offset) const { return data && (offset < length) ? data[offset] : 0; }

    [[nodiscard]] int remain(int offset) const { return length - offset; }
};
