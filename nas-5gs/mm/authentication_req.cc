#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_authentication_req {
extern const element_meta auth_parm_rand;
extern const element_meta auth_parm_autn;

} // namespace mm_authentication_req

using namespace nas;

/*
 * 8.2.1    Authentication request
 */
int mm::authentication_req(dissector d, context* ctx) {
    use_context uc(ctx, "authentication-request");

    using namespace mm_authentication_req;

    /* Spare half octet    Spare half octet     9.5    M    V    1/2 H1 */
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);

    /*ngKSI     NAS key set identifier 9.11.3.29    M    V    1/2  */
    // ELEM_MAND_V(DE_NAS_5GS_MM_NAS_KEY_SET_ID, " - ngKSI",ei_nas_5gs_missing_mandatory_elemen);
    auto consumed = dissect_elem_v(nullptr, &nas_ksi, d, ctx);
    d.step(consumed);

    /* ABBA    ABBA 9.11.3.10    M    LV    3-n */
    // ELEM_MAND_LV(DE_NAS_5GS_MM_ABBA,ei_nas_5gs_missing_mandatory_elemen);
    consumed = dissect_elem_lv(nullptr, &abba, d, ctx);
    d.step(consumed);

    /*21    Authentication parameter RAND (5G authentication challenge)    Authentication
     * parameter RAND     9.11.3.13    O    TV    17*/
    // ELEM_OPT_TV(        0x21, GSM_A_PDU_TYPE_DTAP, DE_AUTH_PARAM_RAND, " - 5G
    // authentication challenge");
    consumed = dissect_opt_elem_tv(nullptr, &auth_parm_rand, d, ctx);
    d.step(consumed);

    /*20    Authentication parameter AUTN (5G authentication challenge)    Authentication
     * parameter AUTN     9.11.3.14    O    TLV    18*/
    // ELEM_OPT_TLV(
    //     0x20, GSM_A_PDU_TYPE_DTAP, DE_AUTH_PARAM_AUTN, " - 5G authentication
    //     challenge");
    consumed = dissect_opt_elem_tlv(nullptr, &auth_parm_autn, d, ctx);
    d.step(consumed);

    /*78    EAP message    EAP message 9.10.2.2    O    TLV-E    7-1503 */
    // ELEM_OPT_TLV_E(0x78, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return d.tvb->reported_length;
}
namespace mm_authentication_req {


int                       dissect_auth_parm_rand(dissector d, context* ctx);
extern const element_meta auth_parm_rand = {
    0x21,
    "Authentication parameter RAND (5G authentication challenge)",
    dissect_auth_parm_rand,
};

int                       dissect_auth_parm_autn(dissector d, context* ctx);
extern const element_meta auth_parm_autn = {
    0x20,
    "Authentication parameter AUTN (5G authentication challenge)",
    dissect_auth_parm_autn,
};


extern const field_meta hf_abba = {
    "ABBA Contents",
    "nas_5gs.mm.abba_contents",
    ft::ft_uint16,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x00,
};

/*
 * 9.11.3.10    ABBA
 */
int dissect_abba(dissector d, context* ctx) {
    d.add_item(d.length, &hf_abba, enc::be);
    return d.length;
}


extern const field_meta hf_dtap_rand = {
    "RAND value",
    "gsm_a.dtap.rand",
    ft::ft_bytes,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x00,
};

/*
 * [9] 10.5.3.1 Authentication parameter RAND
 */
int dissect_auth_parm_rand(dissector d, context* ctx) {
    /* The RAND value is 16 octets long */
    d.add_item(16, &hf_dtap_rand, enc::be);

    /* no length check possible */
    return 16;
}


extern const field_meta hf_dtap_autn = {
    "AUTN value",
    "gsm_a.dtap.autn",
    ft::ft_bytes,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x00,
};
extern const field_meta hf_dtap_autn_sqn = {
    "SQN xor AK",
    "gsm_a.dtap.autn.sqn_xor_ak",
    ft::ft_bytes,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x00,
};
extern const field_meta hf_dtap_autn_amf= {
    "AMF",
    "gsm_a.dtap.autn.amf",
    ft::ft_bytes,
    fd::base_hex,
    nullptr, nullptr, nullptr,
    0x00,
};
extern const field_meta hf_dtap_autn_mac = {
    "MAC",
    "gsm_a.dtap.autn.mac",
    ft::ft_bytes,
    fd::base_hex,
    nullptr, nullptr, nullptr,
    0x00,
};

/*
 * [9] 10.5.3.1.1 Authentication Parameter AUTN (UMTS and EPS authentication challenge)
 */
int dissect_auth_parm_autn(dissector d, context* ctx) {
    auto len     = d.length;
    auto subtree= d.add_item(d.length, &hf_dtap_autn, enc::na);
    if(d.length == 16){
        // d.tree = subtree;
        use_tree ut(d, subtree);

        d.add_item(6, &hf_dtap_autn_sqn, enc::be);
        d.step(6);

        d.add_item(2, &hf_dtap_autn_amf, enc::be);
        d.step(2);

        d.add_item(8, &hf_dtap_autn_mac, enc::be);
        d.step(8);
    }else{
        d.tree->add_expert(
            d.pinfo, d.tvb, d.offset, d.length, "auth param autn length is %d", d.length);
    }
    return len;
}

} // namespace mm_authentication_req
