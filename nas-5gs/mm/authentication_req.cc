#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_authentication_req{
extern const field_meta* hf_spare_half_octet;

extern const element_meta abba;
extern const element_meta auth_parm_rand;
extern const element_meta auth_parm_autn;

}
/*
 * 8.2.1    Authentication request
 */
int mm::authentication_req(dissector d, context* ctx) {
    using namespace mm_authentication_req;

    /* Spare half octet    Spare half octet     9.5    M    V    1/2 H1 */
    // proto_tree_add_item(        tree, hf_nas_5gs_spare_half_octet, tvb, curr_offset, 1, ENC_BIG_ENDIAN);
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);

    /*ngKSI     NAS key set identifier 9.11.3.29    M    V    1/2  */
    // ELEM_MAND_V(NAS_5GS_PDU_TYPE_MM,
    //             DE_NAS_5GS_MM_NAS_KEY_SET_ID,
    //             " - ngKSI",
    //             ei_nas_5gs_missing_mandatory_elemen);
    auto consumed = dissect_elem_v(nullptr, &nksi, d)                ;
    d.offset += consumed;
    d.length -= consumed;

    /* ABBA    ABBA 9.11.3.10    M    LV    3-n */
    // ELEM_MAND_LV(NAS_5GS_PDU_TYPE_MM,
    //              DE_NAS_5GS_MM_ABBA,
    //              NULL,
    //              ei_nas_5gs_missing_mandatory_elemen);
    consumed = dissect_elem_lv(nullptr, &abba, d);
    d.offset += consumed;
    d.length -= consumed;

    /*21    Authentication parameter RAND (5G authentication challenge)    Authentication
     * parameter RAND     9.11.3.13    O    TV    17*/
    // ELEM_OPT_TV(        0x21, GSM_A_PDU_TYPE_DTAP, DE_AUTH_PARAM_RAND, " - 5G authentication challenge");
    consumed = dissect_opt_elem_tv(nullptr, &auth_parm_rand, d);
    d.offset += consumed;
    d.length -= consumed;

    /*20    Authentication parameter AUTN (5G authentication challenge)    Authentication
     * parameter AUTN     9.11.3.14    O    TLV    18*/
    // ELEM_OPT_TLV(
    //     0x20, GSM_A_PDU_TYPE_DTAP, DE_AUTH_PARAM_AUTN, " - 5G authentication challenge");
    consumed = dissect_opt_elem_tlv(nullptr, &auth_parm_autn, d);
    d.offset += consumed;
    d.length -= consumed;

    /*78    EAP message    EAP message 9.10.2.2    O    TLV-E    7-1503 */
    // ELEM_OPT_TLV_E(0x78, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d);
    d.offset += consumed;
    d.length -= consumed;

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}
namespace mm_authentication_req {
extern const field_meta hfm_spare_half_octet = {
    "Spare Half Octet",
    "nas_5gs.spare_half_octet",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0xf0,
};
extern const field_meta* hf_sparse_half_octet = &hfm_spare_half_octet;

int dissect_abba(dissector d, context* ctx);
extern const element_meta abba = {
    -1,
    "ABBA",
    dissect_abba,
};

int dissect_auth_parm_rand(dissector d, context* ctx);
extern const element_meta auth_parm_rand = {
    0x21,
    "Authentication parameter RAND (5G authentication challenge)",
    dissect_auth_parm_rand,
};

int dissect_auth_parm_autn(dissector d, context* ctx);
extern const element_meta auth_parm_autn = {
    0x20,
    "Authentication parameter AUTN (5G authentication challenge)",
    dissect_auth_parm_autn,
};

} // namespace mm_authentication_req
