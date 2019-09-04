#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_ul_nas_transp {
extern const element_meta pld_cont_type;
extern const element_meta pld_cont;
extern const element_meta pdu_ses_id;
extern const element_meta additional_inf;
extern const element_meta old_pdu_ses_id;
extern const element_meta req_type;
extern const element_meta s_nssai;
extern const element_meta dnn;
} // namespace mm_ul_nas_transp

using namespace nas;
using namespace mm;
using namespace mm_ul_nas_transp;

/* 8.2.10    UL NAS transport */
int mm::ul_nas_transp(dissector d, context* ctx) {
    auto        len = d.length;
    use_context uc(ctx, "ul-nas-transport", d);
    /* Direction: UE to network */
    up_link(d.pinfo);

    /* Initalize the private struct */
    // nas5gs_get_private_data(pinfo);

    /* Payload container type   9.11.3.40    M    V    1/2 */
    // ELEM_MAND_V(,  DE_NAS_5GS_MM_PLD_CONT_TYPE,);
    auto consumed = dissect_elem_v(nullptr, &pld_cont_type, d, ctx);

    /*Spare half octet  9.5    M    V    1/2*/
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);
    d.step(1);

    /* Payload container  9.11.3.39    M    LV-E    3-65537*/
    // ELEM_MAND_LV_E(, DE_NAS_5GS_MM_PLD_CONT,);
    consumed = dissect_elem_lv_e(nullptr, &pld_cont, d, ctx);
    d.step(consumed);

    /*12 PDU session ID 2 9.11.3.41    C    TV    2 */
    // ELEM_OPT_TV( 0x12, , DE_NAS_5GS_MM_PDU_SES_ID_2, " - PDU session ID");
    consumed = dissect_opt_elem_tv(nullptr, &pdu_ses_id, d, ctx);
    d.step(consumed);

    /*59    Old PDU session ID    PDU session identity 2 9.11.3.41    O    TV    2 */
    //    ELEM_OPT_TV( 0x59, , DE_NAS_5GS_MM_PDU_SES_ID_2, " - Old PDU session ID");
    consumed = dissect_opt_elem_tv(nullptr, &old_pdu_ses_id, d, ctx);
    d.step(consumed);

    /*8-    Request type  9.11.3.47    O    TV    1 */
    //    ELEM_OPT_TV_SHORT(0x80, , DE_NAS_5GS_MM_REQ_TYPE, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &req_type, d, ctx);
    d.step(consumed);

    /*22    S-NSSAI   9.11.2.8    O    TLV    3-10 */
    //    ELEM_OPT_TLV(0x22, , DE_NAS_5GS_CMN_S_NSSAI, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &s_nssai, d, ctx);
    d.step(consumed);

    /*25    DNN 9.11.2.1A    O    TLV    3-102 */
    //    ELEM_OPT_TLV(0x25, , DE_NAS_5GS_CMN_DNN, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &dnn, d, ctx);
    d.step(consumed);

    /*24 Additional information  9.11.2.1    O    TLV 3-n */
    // ELEM_OPT_TLV(0x24, , DE_NAS_5GS_CMN_ADD_INF, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &additional_inf, d, ctx);
    d.step(consumed);

    // Z	MA PDU session information	MA PDU session information	O	TV	1

    // extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    d.extraneous_data_check(1, ctx);

    return len;
}

namespace mm_ul_nas_transp {
int dissect_pld_cont_type(dissector d, context* ctx); // 9.11.3.40
int dissect_pld_cont(dissector d, context* ctx);      // 9.11.3.39
int dissect_pdu_ses_id(dissector d, context* ctx);
int dissect_additional_inf(dissector d, context* ctx);
int dissect_old_pdu_ses_id(dissector d, context* ctx);
int dissect_req_type(dissector d, context* ctx);

// Payload container type   9.11.3.40
extern const element_meta pld_cont_type = {
    0xff,
    "Payload container type",
    dissect_pld_cont_type,
    nullptr,
};

// Payload container  9.11.3.39
extern const element_meta pld_cont = {
    0xff,
    "Payload container",
    dissect_pld_cont,
    nullptr,
};

// PDU session ID 2 9.11.3.41
extern const element_meta pdu_ses_id = {
    0x12,
    "PDU session ID",
    dissect_pdu_ses_id,
    nullptr,
};

// Additional information  9.11.2.1
extern const element_meta additional_inf = {
    0x24,
    "Additional information",
    dissect_additional_inf,
    nullptr,
};

// PDU session identity 2 9.11.3.41
extern const element_meta old_pdu_ses_id = {
    0x59,
    "Old PDU session ID",
    dissect_old_pdu_ses_id,
    nullptr,
};

// Request type  9.11.3.47
extern const element_meta req_type = {
    0x80,
    "Request type    Request type",
    dissect_req_type,
    nullptr,
};

// S-NSSAI   9.11.2.8
extern const element_meta s_nssai = {
    0x22,
    "S-NSSAI",
    dissect_s_nssai,
    nullptr,
};

// DNN 9.11.2.1A
extern const element_meta dnn = {
    0x25,
    "DNN",
    dissect_dnn,
    nullptr,
};

// Payload container type   9.11.3.40
int dissect_pld_cont_type(dissector d, context* ctx) {
    return mm::dissect_pld_cont_type(d, ctx);
}

// Payload container  9.11.3.39
int dissect_pld_cont(dissector d, context* ctx) { return mm::dissect_pld_cont(d, ctx); }

// PDU session ID 2 9.11.3.41
int dissect_pdu_ses_id(dissector d, context* ctx) {
    // identity value as defined in 3GPP TS 24.007 [11]
    d.add_item(1, hf_pdu_sess_id, enc::be);
    return 1;
}

// Additional information  9.11.2.1
int dissect_additional_inf(dissector d, context* ctx) {
    // The coding of the additional information value is dependent on the LCS application.
    diag("no dissect for %s\n", paths(ctx).c_str());
    return d.length;
}

/*  9.11.3.41    PDU session identity 2 */
int dissect_old_pdu_ses_id(dissector d, context* ctx) {
    d.add_item(1, hf_pdu_sess_id, enc::be);
    return 1;
}

/*  9.11.3.47    Request type */
static const value_string nas_5gs_mm_req_type_vals[] = {
    {0x01, "Initial request"},
    {0x02, "Existing PDU session"},
    {0x03, "Initial emergency request"},
    {0x04, "Existing emergency PDU session"},
    {0x05, "Modification request"},
    {0x07, "Reserved"},
    {0, nullptr},
};
const field_meta hf_req_type = {
    "Request type",
    "nas_5gs.mm.req_typ",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_req_type_vals,
    nullptr,
    nullptr,
    0x0f,
};

// 9.11.3.47 Request type page.390
int dissect_req_type(dissector d, context* ctx) {
    d.add_item(1, &hf_req_type, enc::be);
    return 1;
}

} // namespace mm_ul_nas_transp
