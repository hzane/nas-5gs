#include "ber.hh"

#include <cstring>

#include "definitions.hh"

int dissect_octet(dissector d, context* ctx, octet_t* ret) {
    ret->resize(d.length);
    d.octet(ret->data(), d.length);

    return ret->size();
}
int dissect_octet(dissector d, context*, uint8_t *v){
    std::memcpy(v, d.safe_ptr(), d.safe_length(d.length));
    return d.length;
}

/* Type Value (TV) element dissector */
int dissect_tv_short(dissector d, context* ctx, uint8_t ieid, opt_t< uint8_t >* ret) {
    auto iei = d.uint8(false) & 0xf0u;
    if (iei != ieid && ieid != 0xffu) return 0;
    ret->present = true;

    ret->v = d.uint8() & 0x0fu;

    return 1;
}

int dissect_nibble(dissector d, context* ctx, uint8_t* ret) { *ret = d.uint8() & 0x0fu; return 1;}

int dissect_uint16(dissector d, context* ctx, uint8_t ieid, opt_t< uint16_t >* ret) {
    auto iei = d.uint8();
    if (iei != ieid && ieid != 0xffu) return 0;

    ret->present = true;
    ret->v       = d.uint16();

    return 1 + 2;
}

int dissect_uint8(dissector         d,
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
int dissect_t(dissector d, context* ctx, uint8_t ieid, uint8_t* ret) {
    auto iei = d.uint8();
    if (iei != ieid && ieid != 0xffu) return 0;
    *ret = 1;

    return 1;
}
