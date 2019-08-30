#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

using namespace nas;

/*
 * 8.2.3 Authentication result
 */
int mm::authentication_result(dissector d, context* ctx) {
    use_context uc(ctx, "authentication-result");

    /* ngKSI    NAS key set identifier 9.11.3.27    M    V    1/2
       Spare half octet    Spare half octet 9.5    M    V    1/2  H1 */
    // proto_tree_add_item(        tree, hf_nas_5gs_spare_half_octet, tvb, curr_offset, 1,
    // ENC_BIG_ENDIAN);
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);

    // ELEM_MAND_V(DE_NAS_5GS_MM_NAS_KEY_SET_ID, " - ngKSI",ei_nas_5gs_missing_mandatory_elemen);
    auto consumed = dissect_elem_v(nullptr, &nas_ksi, d, ctx);
    d.step(consumed);

    /* EAP message    EAP message     9.11.2.2    M    LV-E    7-1503 */
    // ELEM_MAND_LV_E(DE_NAS_5GS_CMN_EAP_MESSAGE,ei_nas_5gs_missing_mandatory_elemen);
    consumed = dissect_elem_lv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    /* 38    ABBA    ABBA 9.11.3.10    O    TLV    4-n */
    // ELEM_OPT_TLV(0x38, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_ABBA, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &abba, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return d.tvb->length;
}


