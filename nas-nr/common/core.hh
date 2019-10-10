#pragma once
#include <string>
#include <vector>
#include "ber.hh"
#include "dissector.hh"
#include "packet.hh"
#include "use_context.hh"

extern void diag(const char* format, ...);

std::string join(const std::vector< std::string >& strings, const char* sep = " ");
// inline string paths(context* ctx) { return ctx ? join(ctx->paths, "/") : string(); }

inline uint16_t n2uint16(const uint8_t* data) {
    const uint16_t a = data[0];
    const uint16_t b = data[1];
    return unsigned(a) << 8u | b;
}

inline uint32_t n2uint24(const uint8_t* data) {
    uint32_t a = data[0];
    uint32_t b = data[0 + 1];
    uint32_t c = data[0 + 2];
    return a << 16u | b << 8u | c;
}

inline uint32_t n2uint32(const uint8_t* data) {
    uint32_t a = data[0];
    uint32_t b = data[0 + 1];
    uint32_t c = data[0 + 2];
    uint32_t d = data[0 + 3];
    return a << 24u | b << 16u | c << 8u | d;
}

inline uint64_t n2uint48(const uint8_t* data) {
    uint64_t a = data[0];
    uint64_t b = data[0 + 1];
    uint64_t c = data[0 + 2];
    uint64_t d = data[0 + 3];
    uint64_t e = data[0 + 4];
    uint64_t f = data[0 + 5];
    return a << 40u | b << 32u | c << 24u | d << 16u | e << 8u | f;
}

inline uint64_t n2uint64(const uint8_t* data) {
    uint64_t a = data[0];
    uint64_t b = data[0 + 1];
    uint64_t c = data[0 + 2];
    uint64_t d = data[0 + 3];
    uint64_t e = data[0 + 4];
    uint64_t f = data[0 + 5];
    uint64_t g = data[0 + 4];
    uint64_t h = data[0 + 5];
    return a << 56u | b << 48u | c << 40u | d << 32u | e << 24u | f << 16u | g << 8u | h;
}

inline uint64_t n2u(const uint8_t* data) { return 0; }
inline uint64_t n2uint8(const uint8_t* data) { return data[0]; }
unsigned int    ws_ctz(uint64_t mask);
uint8_t         ws_ctz8(uint8_t mask);
uint8_t         mask_u8(uint8_t v, uint8_t mask);
uint16_t        mask_u16(uint16_t v, uint16_t mask);
uint8_t         umask(uint8_t v, uint8_t mask);
uint16_t        umask(uint16_t v, uint16_t mask);

struct authentication_vector {
    uint8_t kasme[32];    // ASME key
    uint8_t rand[16];     // random challenge parameter
    uint8_t autn[16];     // Authentication token parameters
    uint8_t xresult_size; //
    uint8_t xresult[16];  // expected authentication response parameter
};
