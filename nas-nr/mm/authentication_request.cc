#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.2.1.1    Authentication request */

int dissect_authentication_request(dissector                 d,
                                   context*                  ctx,
                                   authentication_request_t* ret) {
    const use_context uc(ctx, "authentication-request", d, 0);
    down_link(d.pinfo); // network to UE

    auto consumed = dissect_nmm_header(d, ctx, &ret->header);
    d.step(consumed);

    ret->ng_ksi = d.uint8() & 0x0fu;

    d.step(dissect_lv(d, ctx, &ret->abba, dissect_octet));

    d.step(dissect_tv(d.slice(17), ctx, &ret->rand, dissect_octet));
    return uc.length;
}
