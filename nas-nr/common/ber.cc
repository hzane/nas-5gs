#include "ber.hh"

#include <cstring>

#include "definitions.hh"

result_t de_octet(dissector d, context* ctx, octet_t* ret) {
    auto len = d.length;
    *ret     = std::move(octet_t(d.safe_ptr(), d.safe_ptr() + d.length));

    return result_t{len};
}

result_t de_t_octet(dissector d, context*, uint8_t ieid, opt_t< octet_t >* ret) {
    auto len = d.length;

    auto ie = d.uint8(true);
    if (ie != ieid && ieid != 0xffu) return {0};
    ret->present = true;

    de_octet(d, ctx, &ret->v).step(d);

    return {len};
}

result_t de_tl_octet(dissector d, context*, uint8_t ieid, opt_t< octet_t >* ret) {
    auto len    = d.length;

    auto ie     = d.uint8(true);
    if (ie != ieid && ieid != 0xffu) return {0};

    auto length = d.uint8(true);
    ret->present = true;

    ret->v = octet_t(d.safe_ptr(), d.safe_ptr() + d.safe_length(length));

    return {1 + 1 + length};
}

result_t de_tle_octet(dissector d, context*, uint8_t ieid, opt_t< octet_t >* ret) {
    auto ie     = d.uint8(true);
    if (ie != ieid && ieid != 0xffu) return {0};

    auto length = d.uint16(true);
    ret->present = true;

    ret->v = octet_t(d.safe_ptr(), d.safe_ptr() + d.safe_length(length));

    return {1 + 2 + length};
}

result_t de_le_octet(dissector d, context*ctx, octet_t*ret) {
    auto l = d.uint16(true);
    de_octet(d.slice(l), ctx, ret).step(d);
    return {2+int(l)};
}

result_t de_l_octet(dissector d, context*ctx, octet_t*ret) {
    auto l = d.uint8(true);
    de_octet(d.slice(l), ctx, ret).step(d);
    return {1+int(l)};
}

/* Type Value (TV) element dissector */
result_t de_tv_short(dissector d, context* ctx, uint8_t ieid, opt_t< uint8_t >* ret) {
    auto iei = d.uint8(false) & 0xf0u;
    if (iei != ieid && ieid != 0xffu) return {0};

    ret->present = true;
    ret->v = d.uint8() & 0x0fu;

    return {1};
}

result_t de_nibble(dissector d, context* ctx, uint8_t* ret) {
    *ret = d.uint8() & 0x0fu;
    return {1};
}

result_t de_t_uint16(dissector d, context* ctx, uint8_t ieid, opt_t< uint16_t >* ret) {
    if (d.uint8(true) != ieid && ieid != 0xffu) return {0};

    ret->present = true;
    ret->v       = d.uint16();

    return {1 + 2};
}

result_t de_tl_uint16(dissector d, context* ctx, uint8_t ieid, opt_t< uint16_t >* ret) {
    if (d.uint8(true) != ieid && ieid != 0xffu) return {0};

    ret->present = true;
    ret->v       = d.uint16(1);

    return {1+ 1+ 2};
}

result_t de_t_uint8(dissector         d,
                  context*          ctx,
                  uint8_t           ieid,
                  opt_t< uint8_t >* ret,
                  uint8_t           mask ) {
    if (d.uint8(true) != ieid && ieid != 0xffu) return {0};

    ret->present = true;
    ret->v       = mask_u8(d.uint8(true), mask);
    return {1 + 1};
}

/*  Type (T) element dissector */
result_t de_t(dissector d, context* ctx, uint8_t ieid, uint8_t* ret) {
    auto iei = d.uint8();
    if (iei != ieid && ieid != 0xffu) return {0};
    *ret = 1;

    return {1};
}

result_t de_tl_uint8(dissector d, context* ctx, uint8_t ieid, opt_t<uint8_t>*ret){
    if (d.uint8(true) != ieid && ieid != 0xffu) return {0};

    d.step(1); // length

    ret->present = true;
    ret->v       = d.uint8(true);
    return {3};
}

result_t de_uint8(dissector d, context* , uint8_t* ret, uint8_t mask) {
    *ret = mask_u8(d.uint8(true), mask);
    return {1};
}

result_t de_uint16(dissector d, context* ctx, uint16_t*ret, uint16_t mask){
    *ret = mask_u16(d.uint16(true), mask);
    return {2};
}
