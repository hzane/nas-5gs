#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

/*  8.3.6 PDU session authentication result */
int sm::dissect_pdu_ses_auth_res(dissector d, context* ctx) {
    auto start = d.offset;
    /* Direction: network to UE */
    d.pinfo->dir = pi_dir::dl;

    /*EAP message    EAP message 9.11.2.2    M    LV-E    6-1502 */
    // ELEM_MAND_LV_E(,  DE_NAS_5GS_CMN_EAP_MESSAGE,  );
    auto consumed = dissect_elem_lv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options    Extended protocol configuration
     * options    9.11.4.2    O    TLV - E    4 - 65538*/
    // ELEM_OPT_TLV_E(0x7B, NAS_PDU_TYPE_ESM, DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return d.offset - start;
}

// Selected PDU session type    PDU session type 9.11.4.11
extern const element_meta sm::pdu_ses_type = {
    0x90,
    "Selected PDU session type",
    dissect_pdu_ses_type,
    nullptr,
};

/*  9.11.4.10    PDU address  */
const value_string nas_5gs_sm_pdu_ses_type_vals[] = {
    {0x1, "IPv4"},
    {0x2, "IPv6"},
    {0x3, "IPv4v6"},
    {0, nullptr},
};

const field_meta sm::hf_sm_pdu_ses_type = {
    "PDU session type",
    "nas_5gs.sm.pdu_ses_type",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_sm_pdu_ses_type_vals),
    nullptr,
    nullptr,
    0x0f,
};

// Selected PDU session type    PDU session type 9.11.4.11
int sm::dissect_pdu_ses_type(dissector d, context* ctx) {
    d.add_item(1, &hf_sm_pdu_ses_type, enc::be);
    return 1;
}
