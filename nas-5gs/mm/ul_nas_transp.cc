#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/*
 * 8.2.10    UL NAS transport
 */
int mm::ul_nas_transp(dissector d, context* ctx) {
    /* Direction: UE to network */
    pinfo->link_dir = P2P_DIR_UL;

    /* Initalize the private struct */
    nas5gs_get_private_data(pinfo);

    /*Payload container type    Payload container type     9.11.3.31    M    V    1/2 */
    /*Spare half octet    Spare half octet    9.5    M    V    1/2*/
    proto_tree_add_item(
        tree, hf_nas_5gs_spare_half_octet, tvb, curr_offset, 1, ENC_BIG_ENDIAN);
    ELEM_MAND_V(NAS_5GS_PDU_TYPE_MM,
                DE_NAS_5GS_MM_PLD_CONT_TYPE,
                NULL,
                ei_nas_5gs_missing_mandatory_elemen);
    /*Payload container    Payload container    9.11.3.30    M    LV-E    3-65537*/
    ELEM_MAND_LV_E(NAS_5GS_PDU_TYPE_MM,
                   DE_NAS_5GS_MM_PLD_CONT,
                   NULL,
                   ei_nas_5gs_missing_mandatory_elemen);
    /*12    PDU session ID    PDU session identity 2 9.11.3.41    C    TV    2 */
    ELEM_OPT_TV(
        0x12, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PDU_SES_ID_2, " - PDU session ID");
    /*59    Old PDU session ID    PDU session identity 2 9.11.3.37    O    TV    2 */
    ELEM_OPT_TV(
        0x59, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PDU_SES_ID_2, " - Old PDU session ID");
    /*8-    Request type    Request type    9.11.3.42    O    TV    1 */
    ELEM_OPT_TV_SHORT(0x80, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_REQ_TYPE, NULL);
    /*22    S-NSSAI    S-NSSAI    9.11.3.37    O    TLV    3-10 */
    ELEM_OPT_TLV(0x22, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_S_NSSAI, NULL);
    /*25    DNN    DNN    9.11.2.1A    O    TLV    3-102 */
    ELEM_OPT_TLV(0x25, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_DNN, NULL);
    /*24    Additional information    Additional information    9.10.2.1    O    TLV 3-n
     */
    ELEM_OPT_TLV(0x24, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_ADD_INF, NULL);

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}
