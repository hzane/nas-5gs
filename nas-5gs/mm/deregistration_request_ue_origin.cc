#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"


/*  8.2.12 De-registration request (UE originating de-registration)  */
int mm::dissect_dereg_req_ue_orig(dissector d, context* ctx) {    
    const use_context uc(ctx, "de-reg-ue-orig", d, 0);
    // UE to network
    up_link(d.pinfo);

    /* De-registration type   9.11.3.20   M   V   1/2 */
    /*ELEM_MAND_V(DE_NAS_5GS_MM_DE_REG_TYPE,);*/
    auto consumed = dissect_deregistration_type(d, ctx);
    // auto consumed = dissect_elem_v(nullptr, &de_reg_type, d, ctx);

    /* ngKSI    NAS key set identifier 9.11.3.32    M    V    1/2 H1 */
    consumed = dissect_elem_v(nullptr, &nas_ksi, d, ctx);
    d.step(1);

    /* 5GS mobile identity  9.11.3.4    M    LV-E    6-n */
    /*ELEM_MAND_LV_E(DE_NAS_5GS_MM_5GS_MOBILE_ID,); */
    consumed = dissect_elem_lv_e(nullptr, &mobile_id, d, ctx);
    d.step(consumed);
    
    return uc.length;
}

