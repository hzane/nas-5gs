#include "../dissect_mm_msg.hh"
#include "../ber.hh"


using namespace nas;

/* 8.2.1.1    Authentication request */
int mm::authentication_request(dissector d, context* ctx) {    
    const use_context uc(ctx, "authentication-request", d, 0);
    // network to UE
    down_link(d.pinfo);

    /* Spare half octet    Spare half octet     9.5    M    V    1/2 H1 */
    
    /*ngKSI     NAS key set identifier 9.11.3.32    M    V    1/2  */
    // ELEM_MAND_V(DE_NAS_5GS_MM_NAS_KEY_SET_ID, " - ngKSI",);
    dissect_elem_v(nullptr, &nas_ksi, d, ctx);
    d.step(1);

    /* ABBA    ABBA 9.11.3.10    M    LV    3-n */
    // ELEM_MAND_LV(DE_NAS_5GS_MM_ABBA,);
    auto consumed = dissect_elem_lv(nullptr, &abba, d, ctx);
    d.step(consumed);

    /*21    Authentication parameter RAND (5G authentication challenge)    Authentication
     * parameter RAND     9.11.3.16    O    TV    17*/
    // ELEM_OPT_TV(0x21, , DE_AUTH_PARAM_RAND, " - 5G authentication challenge");
    consumed = dissect_opt_elem_tv(nullptr, &auth_param_rand, d, ctx);
    d.step(consumed);

    /*20    Authentication parameter AUTN (5G authentication challenge)    Authentication
     * parameter AUTN     9.11.3.15    O    TLV    18*/
    // ELEM_OPT_TLV(0x20, , DE_AUTH_PARAM_AUTN, " - 5G authentication challenge");
    consumed = dissect_opt_elem_tlv(nullptr, &auth_param_autn, d, ctx);
    d.step(consumed);

    /*78  EAP message 9.11.2.2    O    TLV-E    7-1503 */
    consumed = dissect_opt_elem_tlv_e(nullptr, &cmn::eap_msg, d, ctx);
    d.step(consumed);
    
    return uc.length;
}
namespace mm {

extern const element_meta auth_param_rand = {
    0x21,
    "Authentication parameter RAND - 5G authentication challenge",
    dissect_auth_parameter_rand,
    nullptr,
};

extern const element_meta auth_param_autn = {
    0x20,
    "Authentication parameter AUTN - 5G authentication challenge",
    dissect_auth_parameter_autn,
    nullptr,
};


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


} // namespace 
