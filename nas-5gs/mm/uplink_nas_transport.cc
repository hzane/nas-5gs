#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"


using namespace cmn;
using namespace nas;
using namespace mm;

/* 8.2.10    UL NAS transport */
int mm::dissect_ul_nas_transp(dissector d, context* ctx) {
    const use_context uc(ctx, "ul-nas-transport", d, 1);

    /* Direction: UE to network */
    up_link(d.pinfo);

    /* Initalize the private struct */
    // nas5gs_get_private_data(pinfo);

    /* Payload container type   9.11.3.40    M    V    1/2 */
    // ELEM_MAND_V(,  DE_NAS_5GS_MM_PLD_CONT_TYPE,);
    auto consumed = dissect_elem_v(nullptr, &payload_container_type, d, ctx);

    /*Spare half octet  9.5    M    V    1/2*/
    // d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);
    d.step(1);

    /* Payload container  9.11.3.39    M    LV-E    3-65537*/
    // ELEM_MAND_LV_E(, DE_NAS_5GS_MM_PLD_CONT,);
    consumed = dissect_elem_lv_e(nullptr, &pld_cont, d, ctx);
    d.step(consumed);

    /*12 PDU session ID 2 9.11.3.41    C    TV    2 */
    // ELEM_OPT_TV( 0x12, , DE_NAS_5GS_MM_PDU_SES_ID_2, " - PDU session ID");
    consumed = dissect_opt_elem_tv(nullptr, &pdu_session_id, d, ctx);
    d.step(consumed);

    /*59    Old PDU session ID    PDU session identity 2 9.11.3.41    O    TV    2 */
    //    ELEM_OPT_TV( 0x59, , DE_NAS_5GS_MM_PDU_SES_ID_2, " - Old PDU session ID");
    consumed = dissect_opt_elem_tv(nullptr, &old_pdu_ses_id, d, ctx);
    d.step(consumed);

    /*8-    Request type  9.11.3.47    O    TV    1 */
    //    ELEM_OPT_TV_SHORT(0x80, , DE_NAS_5GS_MM_REQ_TYPE, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &request_type, d, ctx);
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
   

    return uc.length;
}
