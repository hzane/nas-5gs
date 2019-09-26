#pragma once
#include "nas.hh"
#include "core.hh"
#include "dissector.hh"

int dissect_octet(dissector d, context* ctx, octet_t* ret);

template < typename element_t >
int dissect_lv(dissector                   d,
               context*                    ctx,
               element_t*                  ret,
               dissect_func_t< element_t > func) {
    auto length = d.uint8();
    (void) func(d.slice(length), ctx, ret).step(d);
    return length + 1;
}

template < typename element_t >
int dissect_tv(dissector                   d,
               context*                    ctx,
               opt_t< element_t >*         ret,
               dissect_func_t< element_t > func) {
    auto iei = d.uint8();
    if (iei != ret->iei && ret->iei != 0xffu) return 0;
    ret->present = true;

    auto consumed = func(d, ctx, &ret->v).step(d);
    return consumed + 1;
}

unsigned int ws_ctz(uint64_t mask);

inline int dissect_uint8(dissector d, context*ctx, uint8_t ieid, opt_t<uint8_t> *ret, uint8_t mask = 0){
    auto iei = d.uint8();
    if (iei != ieid && ieid != 0xffu) return 0;

    ret->present = true;
    ret->v       = d.uint8();
    if (mask) ret->v = (unsigned(ret->v)&mask)>>ws_ctz(mask);
    return 1+1;
}

int dissect_uint16(dissector d, context*ctx, uint8_t ieid, opt_t<uint16_t> *ret){
    auto iei = d.uint8();
    if (iei != ieid && ieid != 0xffu) return 0;

    ret->present = true;
    ret->v = d.uint16();

    return 1 + 2;
}

/*  Type (T) element dissector */
template < typename element_t >
int dissect_t(dissector                   d,
              context*                    ctx,
              opt_t< element_t >*         ret,
              dissect_func_t< element_t > func) {
    auto iei = d.uint8();
    if (iei != ret->iei && ret->iei != 0xffu) return 0;
    ret->present = true;

    func(d.slice(0), ctx, &ret->v).step(d);
    return 1;
}

/* Type Length Value (TLV) element dissector */
template < typename element_t >
int dissect_tlv(dissector                   d,
                context*                    ctx,
                opt_t< element_t >*         ret,
                dissect_func_t< element_t > func) {
    auto iei = d.uint8();
    if (iei != ret->iei && ret->iei != 0xffu) return 0;
    ret->present = true;

    int length   = d.uint8();
    (void) func(d.slice(length), ctx, &ret->v).step(d);
    return length + 2;
}

/* Type Extendable Length Value (TELV) element dissector */
template < typename element_t >
int dissect_telv(dissector                   d,
                 context*                    ctx,
                 opt_t< element_t >*         ret,
                 dissect_func_t< element_t > func) {
    auto iei = d.uint8();
    if (iei != ret->iei && ret->iei != 0xffu) return 0;
    ret->present = true;

    uint16_t      len   = d.uint8(false);
    auto     len_length = 1;

    if ((len & 0x80u) == 0) {
        /* length in 2 octets */
        len   = d.uint16(false);
        len_length = 2;
    }
    d.step(len_length);

    (void) func(d.slice(len), ctx, &ret->v).step(d);
    return 1 + len_length + len;
}

/* Type Length Value Extended(TLV-E) element dissector TS 24.007 */
template < typename element_t >
int dissect_tlv_e(dissector                   d,
                  context*                    ctx,
                  opt_t< element_t >*         ret,
                  dissect_func_t< element_t > func) {
    auto iei = d.uint8();
    if (iei != ret->iei && ret->iei != 0xffu) return 0;
    ret->present = true;

    const auto len = d.uint16();

    (void) func(d.slice(len), ctx, &ret->v).step(d);

    return 1 + 2 + len;
}

int dissect_nibble(dissector d, context* ctx, uint8_t* ret) { *ret = d.uint8() & 0x0fu; }

/* Type Value (TV) element dissector */
int dissect_tv_short(dissector d, context* ctx, uint8_t ieid, opt_t< uint8_t >* ret) {
    auto iei = d.uint8(false)& 0xf0u;
    if (iei != ieid && ieid != 0xffu) return 0;
    ret->present = true;

    ret->v = d.uint8() & 0x0fu;

    return 1;
}

/* Length Value Extended(LV-E) element dissector */
template<typename element_t>
int dissect_lv_e(dissector                   d,
                 context*                    ctx,
                 opt_t< element_t >*         ret,
                 dissect_func_t< element_t > func) {
    ret->present        = true;
    const auto len = d.uint16();

    (void) func(d.slice(len), ctx, &ret->v).step(d);
    return len + 2;
}

inline int dissect_octet(dissector d, context* ctx, octet_t* ret) {
    ret->resize(d.length);
    d.octet(ret->data(), d.length);

    return ret->size();
}