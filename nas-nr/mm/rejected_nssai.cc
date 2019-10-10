#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* *   9.11.3.46    Rejected NSSAI page.389 */
result_t die_rejected_nssai(dissector d, context* ctx, rejected_nssai_t* ret) {
    const use_context uc(&d, ctx, "rejected-nssai", 0);
    while (d.length > 0) {
        rejected_nssai_t::nssai_t n = {};
        auto                      l = mask_u8(d.uint8(false), 0xf0u);
        de_uint8(d, ctx, &n.cause, 0x0fu).step(d);
        de_uint8(d, ctx, &n.sst).step(d);
        if (l > 2) {
            n.sd.present = true;
            de_octet(d.slice(l - 2), ctx, &n.sd.v).step(d);
        }
        ret->nssais.push_back(n);
    }
    return {uc.length};
}
