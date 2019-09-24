#include "../base/ber.hh"
#include "../common/dissect_mm_msg.hh"

/* 8.2.8 Registration complete */
int mm::dissect_registration_complete(dissector d, context* ctx) {
    const use_context uc(ctx, "registration-complete", d);

    up_link(d.pinfo);

    /* 73    SOR transparent container 9.11.3.51    O TLV-E 20-2048 */
    const auto consumed = dissect_opt_tlv_e(nullptr, &sor_transparent_container, d, ctx);
    d.step(consumed);

    return uc.length;
}
