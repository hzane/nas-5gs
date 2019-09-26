#pragma once
#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

struct packet;
struct context;

using string  = std::string;
using octet_t = std::vector< uint8_t >;

using octet_4 = uint8_t[4];
using octet_2 = uint8_t[2];
using octet_3 = uint8_t[3];
using octet_6 = uint8_t[6];
using octet_16  = uint8_t[16];
using octet_b   = uint8_t[11];

using uint24_t = uint32_t;
using uint48_t = uint64_t;

using bit1_t = uint8_t;
using bit2_t = uint8_t;
using bit3_t = uint8_t;
using bit4_t = uint8_t;
using bit7_t = uint8_t;
using bit6_t = uint8_t;
using bit5_t = uint8_t;
using bita_t = uint16_t;

template < typename element_t >
struct opt_t {
    bool      present = false;
    element_t v       = {};
};
