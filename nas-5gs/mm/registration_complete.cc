#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_reg_accept{
extern const element_meta sor_trans_cont;
}
/*
 * 8.2.8 Registration complete
 */
int mm::registration_complete(dissector d, context* ctx) {
    up_link(d.pinfo);

    const auto  len = d.length;
    use_context uc(ctx, "registration-complete");

    /* 73    SOR transparent container 9.11.3.51    O TLV-E 20-2048 */
    // ELEM_OPT_TLV_E(0x73, , DE_NAS_5GS_MM_SOR_TRASP_CONT, NULL);
    const auto consumed =
        dissect_opt_elem_tlv_e(nullptr, &mm_reg_accept::sor_trans_cont, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return len;
}
