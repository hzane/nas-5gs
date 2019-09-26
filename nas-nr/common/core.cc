#include "core.hh"
#include <sstream>
#include "message.hh"
#include "dissector.hh"
#include "context.hh"

int dissect_nmm_header(dissector d, context* ctx, nmm_header_t* ret) {
    ret->epd                  = d.uint8();
    ret->security_header_type = d.uint8() & 0x0fu;
    ret->message_type         = d.uint8();
    return 3;
}


use_context::use_context(dissector const* d,
                         context*         ctx,
                         const char*      path,
                         const int        maxlen)
    : ctx(ctx), offset(d->offset), length(d->length), maxlen(maxlen), d(d) {
    if (!ctx) return;
    if (path == nullptr) path = ".";
    ctx->paths.emplace_back(path);
    diag("%s%s %d-%d\n",
         string(ctx->paths.size() << 1u, ' ').c_str(),
         path,
         offset,
         length);
}
use_context::~use_context() {
    extraneous_data_check();
    if (ctx) {
        ctx->paths.pop_back();
    }
}
void use_context::extraneous_data_check() {
    if (maxlen < 0) return;
    if (d->length <= maxlen) return;
    if (!ctx) return;

    diag("extraneous data %d bytes, %s\n", d->length, join(ctx->paths).c_str());
}

inline int ws_ctz32(uint32_t x) {
    /* From http://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup */
    static const uint8_t table[32] = {
        0,  1,  28, 2,  29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4,  8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6,  11, 5,  10, 9,
    };

    return table[((uint32_t)((x & (uint32_t)(0u - x)) * 0x077CB531U)) >> 27u];
}
inline uint8_t ws_ctz8(uint8_t x){
    return static_cast<uint8_t>(ws_ctz32(x));
}
unsigned int ws_ctz(uint64_t x) {
    auto hi = uint32_t(x >> 32u);
    auto lo = (uint32_t) x;

    if (lo == 0)
        return 32 + ws_ctz32(hi);
    else
        return ws_ctz32(lo);
}
