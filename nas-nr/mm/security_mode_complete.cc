#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"

const element_meta mm::imeisv_mobile_id = {
    0x77,
    "5G mobile identity - IMEISV",
    mm::dissect_mobile_id,
    nullptr,
};

/*  8.2.26 Security mode complete */
int mm::dissect_security_mode_complete(dissector d, context* ctx) {
    const use_context uc(ctx, "security-mode-complete", d, 0);
    // UE to network
    up_link(d.pinfo);

    /* 77    IMEISV    5G mobile identity 9.11.3.4    O    TLV-E    11 */
    auto consumed = dissect_opt_tlv_e(nullptr, &imeisv_mobile_id, d, ctx);
    d.step(consumed);

    /* 71    NAS message container  9.11.3.33    O    TLV-E    4-n  */
    consumed = dissect_opt_tlv_e(nullptr, &nas_msg_container, d, ctx);
    d.step(consumed);

    return uc.length;
}
