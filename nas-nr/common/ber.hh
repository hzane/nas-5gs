#pragma once
#include "core.hh"
#include "definitions.hh"
#include "dissector.hh"
#include "nas.hh"

template < typename element_t >
using dissect_func_t = result_t (*)(dissector, context*, element_t *);

uint8_t ws_ctz8(uint8_t mask);

result_t de_uint8(dissector d, context* ctx, uint8_t* ret, uint8_t mask = 0);

result_t de_uint16(dissector d, context* ctx, uint16_t* ret, uint16_t mask = 0);

result_t de_l_uint8(dissector d, context* ctx, uint8_t* ret);

result_t de_tl_uint8(dissector d, context* ctx, uint8_t ieid, opt_t< uint8_t >* ret);

result_t de_t_uint8(dissector         d,
                    context*          ctx,
                    uint8_t           ieid,
                    opt_t< uint8_t >* ret,
                    uint8_t           mask = 0);

result_t de_t_uint8(dissector d,
                    context*  ctx,
                    uint8_t   ieid,
                    uint8_t*  ret,
                    uint8_t   mask = 0);

result_t de_tv_short(dissector d, context* ctx, uint8_t ieid, opt_t< uint8_t >* ret);

result_t de_octet(dissector d, context* ctx, octet_t* ret);

result_t de_t_octet(dissector d, context* ctx, uint8_t ieid, opt_t< octet_t >* ret);

result_t de_tl_octet(dissector d, context* ctx, uint8_t ieid, opt_t< octet_t >* ret);

result_t de_tle_octet(dissector d, context* ctx, uint8_t ieid, opt_t< octet_t >* ret);

result_t de_le_octet(dissector d, context* ctx, octet_t* ret);

result_t de_l_octet(dissector d, context* ctx, octet_t* ret);

result_t de_nibble(dissector d, context* ctx, uint8_t* ret);

result_t de_t_uint16(dissector d, context* ctx, uint8_t ieid, opt_t< uint16_t >* ret);

result_t de_tl_uint16(dissector d, context* ctx, uint8_t ieid, opt_t< uint16_t >* ret);

template < typename element_t >
result_t de_l(dissector                   d,
              context*                    ctx,
              element_t*                  ret,
              dissect_func_t< element_t > func) {
    auto length = d.uint8();
    (void) func(d.slice(length), ctx, ret);

    return {length + 1};
}

template < typename element_t >
result_t de_t(dissector                   d,
              context*                    ctx,
              opt_t< element_t >*         ret,
              dissect_func_t< element_t > func) {
    auto iei = d.uint8();
    if (iei != ret->iei && ret->iei != 0xffu) return {0};
    ret->present = true;

    auto consumed = func(d, ctx, &ret->v);
    return {consumed + 1};
}

/*  Type (T) element dissector */
result_t de_t(dissector d, context* ctx, uint8_t ieid, uint8_t* ret);

/* Type Length Value (TLV) element dissector */
template < typename element_t >
result_t de_tl(dissector                   d,
               context*                    ctx,
               opt_t< element_t >*         ret,
               dissect_func_t< element_t > func) {
    auto iei = d.uint8();
    if (iei != ret->iei && ret->iei != 0xffu) return {0};
    ret->present = true;

    int length = d.uint8();
    (void) func(d.slice(length), ctx, &ret->v);
    return {length + 2};
}

/* Type Extendable Length Value (TELV) element dissector */
template < typename element_t >
result_t de_tel(dissector                   d,
                context*                    ctx,
                opt_t< element_t >*         ret,
                dissect_func_t< element_t > func) {
    auto iei = d.uint8();
    if (iei != ret->iei && ret->iei != 0xffu) return {0};
    ret->present = true;

    uint16_t len        = d.uint8(false);
    auto     len_length = 1;

    if ((len & 0x80u) == 0) {
        /* length in 2 octets */
        len        = d.uint16(false);
        len_length = 2;
    } else
        len = len & 0x7fu;
    d.step(len_length);

    (void) func(d.slice(len), ctx, &ret->v);
    return {1 + len_length + len};
}

/* Type Length Value Extended(TLV-E) element dissector TS 24.007 */
template < typename element_t >
result_t de_tle(dissector                   d,
                context*                    ctx,
                uint8_t ieid,
                opt_t< element_t >*         ret,
                dissect_func_t< element_t > func) {
    auto iei = d.uint8();
    if (iei != ieid && ieid != 0xffu) return {0};
    ret->present = true;

    const auto len = d.uint16();

    (void) func(d.slice(len), ctx, &ret->v);

    return {1 + 2 + len};
}

/* Length Value Extended(LV-E) element dissector */
template < typename element_t >
result_t de_le(dissector                   d,
               context*                    ctx,
               opt_t< element_t >*         ret,
               dissect_func_t< element_t > func) {
    ret->present   = true;
    const auto len = d.uint16();

    (void) func(d.slice(len), ctx, &ret->v);
    return {len + 2};
}

template < typename E >
result_t de_t_fixed(dissector d, context* ctx, uint8_t ieid, opt_t< E >* ret) {
    auto ie      = d.uint8(true);
    ret->present = ie == ieid || ieid == 0xffu;
    if (ie != ieid && ieid != 0xffu) return {0};
    d.octet(ret->v, sizeof(ret->v));

    return {1 + sizeof(ret->v)};
}

template < typename E >
result_t de_tl_fixed(dissector d, context* ctx, uint8_t ieid, opt_t< E >* ret) {
    auto ie  = d.uint8(true);
    auto len = d.uint8(true);
    if (ie != ieid && ieid != 0xffu) return {0};

    ret->present = true;
    d.octet(ret->v, d.safe_length(len > sizeof(ret->v) ? sizeof(ret->v) : len));

    return {1 + 1 + len};
}

template < typename Slice >
result_t de_fixed(dissector d, context*, Slice ret) {
    auto l = d.octet(ret, sizeof(ret));
    return {int(l)};
}

template < typename Slice >
result_t de_le_fixed(dissector d, context*, Slice ret) {
    auto len = d.uint16(true);

    auto l = d.octet(ret, sizeof(ret) > len ? len : sizeof(ret));
    return {2 + len};
}

template < typename Slice >
result_t de_l_fixed(dissector d, context*, Slice ret) {
    auto len = d.uint8(true);

    auto l = d.octet(ret, sizeof(ret) > len ? len : sizeof(ret));
    return {1 + len};
}

template < typename E >
result_t de_tle_fixed(dissector d, context* ctx, uint8_t ieid, opt_t< E >* ret) {
    auto ie  = d.uint8(true);
    auto len = d.uint16(true);
    if (ie != ieid && ieid != 0xffu) return {0};

    ret->present = true;
    d.octet(ret->v, d.safe_length(len > sizeof(ret->v) ? sizeof(ret->v) : len));

    return {1 + 2 + len};
}
