#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/*
 * 8.2.11 DL NAS transport
 */
int mm::dl_nas_transp(dissector d, context* ctx) {
    /* Initalize the private struct */
    nas5gs_get_private_data(pinfo);

    /*Payload container type    Payload container type     9.11.3.40    M    V    1/2 H0*/
    /*Spare half octet    Spare half octet    9.5    M    V    1/2 H1*/
    proto_tree_add_item(
        tree, hf_nas_5gs_spare_half_octet, tvb, curr_offset, 1, ENC_BIG_ENDIAN);
    ELEM_MAND_V(NAS_5GS_PDU_TYPE_MM,
                DE_NAS_5GS_MM_PLD_CONT_TYPE,
                NULL,
                ei_nas_5gs_missing_mandatory_elemen);
    /*Payload container    Payload container    9.11.3.39    M    LV-E    3-65537*/
    ELEM_MAND_LV_E(NAS_5GS_PDU_TYPE_MM,
                   DE_NAS_5GS_MM_PLD_CONT,
                   NULL,
                   ei_nas_5gs_missing_mandatory_elemen);
    /*12    PDU session ID    PDU session identity 2 9.11.3.37    C    TV    2 */
    ELEM_OPT_TV(
        0x12, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PDU_SES_ID_2, " - PDU session ID");
    /*24    Additional information    Additional information    9.10.2.1    O    TLV 3-n*/
    ELEM_OPT_TLV(0x24, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_ADD_INF, NULL);
    /*58    5GMM cause    5GMM cause 9.11.3.2    O    TV    2 */
    ELEM_OPT_TV(0x58, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_5GMM_CAUSE, NULL);
    /*37    Back-off timer value    GPRS timer 3 9.10.2.5    O    TLV    3 */
    ELEM_OPT_TLV(0x37, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER_3, " - Back-off timer value");

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}
