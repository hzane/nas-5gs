#include "ber.hh"

#include <cstring>

#include "definitions.hh"

result_t de_octet(dissector d, context* ctx, octet_t* ret) {
    ret->resize(d.length);
    d.octet(ret->data(), d.length);

    return result_t{ret->size()};
}
result_t de_t_octet(dissector d, context*, uint8_t ieid, uint8_t *v, bool *present){
    auto len = d.length;
    auto ie = d.uint8(true);
    if (present) *present = (ie == ieid);
    if (ie != ieid && ieid != 0xffu) return {0};

    std::memcpy(v, d.safe_ptr(), d.safe_length(d.length));
    return {len};
}

result_t de_tl_octet(dissector d, context*, uint8_t ieid, opt_t< octet_t >* ret) {
    auto len    = d.length;
    auto ie     = d.uint8(true);
    auto length = d.uint8(true);
    if (ie != ieid && ieid != 0xffu) return 0;
    ret->present = true;

    ret->resize(d.length);
    d.octet(ret->data(), ret->size());

    return {len};
}

/* Type Value (TV) element dissector */
result_t de_tv_short(dissector d, context* ctx, uint8_t ieid, opt_t< uint8_t >* ret) {
    auto iei = d.uint8(false) & 0xf0u;
    if (iei != ieid && ieid != 0xffu) return 0;
    ret->present = true;

    ret->v = d.uint8() & 0x0fu;

    return {1};
}

result_t de_nibble(dissector d, context* ctx, uint8_t* ret) {
    *ret = d.uint8() & 0x0fu;
    return {1};
}

result_t de_uint16(dissector d, context* ctx, uint8_t ieid, opt_t< uint16_t >* ret) {
    auto iei = d.uint8();
    if (iei != ieid && ieid != 0xffu) return 0;

    ret->present = true;
    ret->v       = d.uint16();

    return 1 + 2;
}

result_t de_uint8(dissector         d,
                  context*          ctx,
                  uint8_t           ieid,
                  opt_t< uint8_t >* ret,
                  uint8_t           mask ) {
    auto iei = d.uint8();
    if (iei != ieid && ieid != 0xffu) return 0;

    ret->present = true;
    ret->v       = mask_u8(d.uint8(), mask);
    return 1 + 1;
}

/*  Type (T) element dissector */
result_t de_t(dissector d, context* ctx, uint8_t ieid, uint8_t* ret) {
    auto iei = d.uint8();
    if (iei != ieid && ieid != 0xffu) return 0;
    *ret = 1;

    return 1;
}
