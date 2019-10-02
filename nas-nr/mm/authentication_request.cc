#include "../common/ber.hh"
#include "../common/dissector.hh"
#include "../common/dissects.hh"
#include "../common/ies.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.2.1.1    Authentication request */

int dissect_authentication_request(dissector                 d,
                                   context*                  ctx,
                                   authentication_request_t* ret) {
    const use_context uc(&d, ctx, "authentication-request", 0);
    down_link(d.pinfo); // network to UE

    auto consumed = dissect_nmm_header(d, ctx, &ret->header);
    d.step(consumed);

    ret->ng_ksi = d.uint8() & 0x0fu;

    auto c= dissect_lv(d, ctx, &ret->abba, dissect_octet);
    d.step(c);

    d.step(1);
    c = dissect_octet(d.slice(16), ctx, ret->rand);
    d.step(c);

    return uc.length;
}
