#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/* 8.2.8 Registration complete */
int mm::dissect_registration_complete(dissector d, context* ctx) {
    const use_context uc(ctx, "registration-complete", d);

    up_link(d.pinfo);

    /* 73    SOR transparent container 9.11.3.51    O TLV-E 20-2048 */
    // ELEM_OPT_TLV_E(0x73, , DE_NAS_5GS_MM_SOR_TRASP_CONT, NULL);
    const auto consumed =
        dissect_opt_elem_tlv_e(nullptr, &sor_trans_cont, d, ctx);
    d.step(consumed);
    
    return uc.length;
}
