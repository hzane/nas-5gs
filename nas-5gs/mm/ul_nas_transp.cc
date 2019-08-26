#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_ul_nas_transp {
extern const element_meta pld_cont_type;
extern const element_meta pld_cont;
extern const element_meta pdu_ses_id;
extern const element_meta add_inf;
extern const element_meta old_pdu_ses_id;
extern const element_meta req_type;
extern const element_meta s_nssai;
extern const element_meta dnn;
} // namespace mm_ul_nas_transp

using namespace nas;


/*
 * 8.2.10    UL NAS transport
 */
int mm::ul_nas_transp(dissector d, context* ctx) {
    use_context uc(ctx, "ul-nas-transport");

    using namespace mm_ul_nas_transp;

    /* Direction: UE to network */
    d.pinfo->dir = pi_dir::ul;

    /* Initalize the private struct */
    // nas5gs_get_private_data(pinfo);

    /*Payload container type    Payload container type     9.11.3.31    M    V    1/2 */
    /*Spare half octet    Spare half octet    9.5    M    V    1/2*/
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);

    //    ELEM_MAND_V(NAS_5GS_PDU_TYPE_MM,  DE_NAS_5GS_MM_PLD_CONT_TYPE,);
    auto consumed = dissect_elem_v(nullptr, &pld_cont_type, d, ctx);
    d.step(consumed);

    /*Payload container    Payload container    9.11.3.30    M    LV-E    3-65537*/
    //    ELEM_MAND_LV_E(NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PLD_CONT,);
    consumed = dissect_elem_lv_e(nullptr, &pld_cont, d, ctx);
    d.step(consumed);

    /*12    PDU session ID    PDU session identity 2 9.11.3.41    C    TV    2 */
    //    ELEM_OPT_TV( 0x12, , DE_NAS_5GS_MM_PDU_SES_ID_2, " - PDU session ID");
    consumed = dissect_opt_elem_tv(nullptr, &pdu_ses_id, d, ctx);
    d.step(consumed);

    /*59    Old PDU session ID    PDU session identity 2 9.11.3.37    O    TV    2 */
    //    ELEM_OPT_TV( 0x59, , DE_NAS_5GS_MM_PDU_SES_ID_2, " - Old PDU session ID");
    consumed = dissect_opt_elem_tv(nullptr, &old_pdu_ses_id, d, ctx);
    d.step(consumed);

    /*8-    Request type    Request type    9.11.3.42    O    TV    1 */
    //    ELEM_OPT_TV_SHORT(0x80, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_REQ_TYPE, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &req_type, d, ctx);
    d.step(consumed);

    /*22    S-NSSAI    S-NSSAI    9.11.3.37    O    TLV    3-10 */
    //    ELEM_OPT_TLV(0x22, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_S_NSSAI, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &s_nssai, d, ctx);
    d.step(consumed);

    /*25    DNN    DNN    9.11.2.1A    O    TLV    3-102 */
    //    ELEM_OPT_TLV(0x25, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_DNN, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &dnn, d, ctx);
    d.step(consumed);

    /*24    Additional information    Additional information    9.10.2.1    O    TLV 3-n
     */
    //    ELEM_OPT_TLV(0x24, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_ADD_INF, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &add_inf, d, ctx);
    d.step(consumed);

    // extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    d.extraneous_data_check(0);
    return d.tvb->reported_length;
}

namespace mm_ul_nas_transp {
int dissect_pld_cont_type(dissector d, context* ctx);
int dissect_pld_cont(dissector d, context* ctx);
int dissect_pdu_ses_id(dissector d, context* ctx);
int dissect_add_inf(dissector d, context* ctx);
int dissect_old_pdu_ses_id(dissector d, context* ctx);
int dissect_req_type(dissector d, context* ctx);
int dissect_s_nssai(dissector d, context* ctx);
int dissect_dnn(dissector d, context* ctx);

extern const element_meta pld_cont_type = {
    0xff,
    "Payload container type",
    dissect_pld_cont_type,
};
extern const element_meta pld_cont = {
    0xff,
    "Payload container",
    dissect_pld_cont,
};
extern const element_meta pdu_ses_id = {
    0x12,
    "PDU session ID",
    dissect_pdu_ses_id,
};
extern const element_meta add_inf = {
    0x24,
    "Additional information",
    dissect_add_inf,
};

extern const element_meta old_pdu_ses_id = {
    0x59,
    "Old PDU session ID",
    dissect_old_pdu_ses_id,
};
extern const element_meta req_type = {
    0x80,
    "Request type    Request type",
    dissect_req_type,
};
extern const element_meta s_nssai = {
    0x22,
    "S-NSSAI",
    dissect_s_nssai,
};
extern const element_meta dnn = {
    0x25,
    "DNN",
    dissect_dnn,
};
int dissect_pld_cont_type(dissector d, context* ctx) { return 0; }
int dissect_pld_cont(dissector d, context* ctx) { return 0; }
int dissect_pdu_ses_id(dissector d, context* ctx) { return 0; }
int dissect_add_inf(dissector d, context* ctx) { return 0; }
int dissect_old_pdu_ses_id(dissector d, context* ctx) { return 0; }
int dissect_req_type(dissector d, context* ctx) { return 0; }
int dissect_s_nssai(dissector d, context* ctx) { return 0; }
int dissect_dnn(dissector d, context* ctx) { return 0; }
} // namespace mm_ul_nas_transp
