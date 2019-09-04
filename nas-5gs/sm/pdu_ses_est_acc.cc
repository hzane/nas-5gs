#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

namespace sm_pdu_ses_est {
extern const field_meta* hf_sel_sc_mode;

extern const element_meta pdu_ses_type;
extern const element_meta pdu_address;
extern const element_meta sm_s_nssai;
extern const element_meta dnn;
} // namespace sm_pdu_ses_est

using namespace nas;
using namespace sm;
/*
 * 8.3.2 PDU session establishment accept
 */
int sm::pdu_ses_est_acc(dissector d, context* ctx) {
    auto        len = d.length;
    use_context uc(ctx, "pdu-session-establishment-accept");

    using namespace sm_pdu_ses_est;
    /* Direction: network to UE */
    d.pinfo->dir = pi_dir::dl;

    // proto_tree_add_item(tree, hf_nas_5gs_sm_sel_sc_mode, tvb, offset, 1,
    // ENC_BIG_ENDIAN);
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_sel_sc_mode, enc::be);
    /*Selected PDU session type    PDU session type 9.11.4.5    M    V    1/2 H0*/
    // ELEM_MAND_V( DE_NAS_5GS_SM_PDU_SESSION_TYPE,);
    auto consumed = dissect_elem_v(nullptr, &pdu_ses_type, d, ctx);
    d.step(consumed);

    /*Selected SSC mode    SSC mode 9.11.4.9    M    V    1/2 H1*/

    /*Authorized QoS rules    QoS rules 9.11.4.6    M    LV-E    2-65537
     * DE_NAS_5GS_SM_QOS_RULES*/
    // ELEM_MAND_LV_E(,DE_NAS_5GS_SM_QOS_RULES, " - Authorized QoS rules",);
    consumed = dissect_elem_lv_e(nullptr, &authorized_qos_rules, d, ctx);
    d.step(consumed);

    /*Session AMBR    Session-AMBR 9.11.4.14    M    LV    7 */
    // ELEM_MAND_LV(, DE_NAS_5GS_SM_SESSION_AMBR);
    consumed = dissect_elem_lv(nullptr, &ses_ambr, d, ctx);
    d.step(consumed);

    /*59    5GSM cause    5GSM cause 9.11.4.2    O    TV    2*/
    // ELEM_OPT_TV(0x59, , DE_NAS_5GS_SM_5GSM_CAUSE, NULL);
    consumed = dissect_opt_elem_tv(nullptr, &sm_cause, d, ctx);
    d.step(consumed);

    /*29    PDU address    PDU address 9.11.4.4    O    TLV    7 */
    // ELEM_OPT_TLV(0x29, , DE_NAS_5GS_SM_PDU_ADDRESS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &pdu_address, d, ctx);
    d.step(consumed);

    /*56    RQ timer value    GPRS timer 9.10.2.3    O    TV    2*/
    // ELEM_OPT_TV(0x56, , DE_GPRS_TIMER, " - RQ timer value");
    consumed = dissect_opt_elem_tv(nullptr, &rq_gprs_timer, d, ctx);
    d.step(consumed);

    /*22    S-NSSAI    S-NSSAI 9.11.3.37    O    TLV    3-6*/
    // ELEM_OPT_TLV(0x22, , DE_NAS_5GS_CMN_S_NSSAI, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &sm_s_nssai, d, ctx);
    d.step(consumed);

    /* 8-    Always-on PDU session indication   9.11.4.3  O    TV    1 */
    // ELEM_OPT_TV_SHORT(w 0x80, , DE_NAS_5GS_SM_ALWAYS_ON_PDU_SES_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &always_on_pdu_ses_ind, d, ctx);
    d.step(consumed);

    /* 75    Mapped EPS bearer contexts  9.11.4.9    O  TLV-E    7-65538 */
    // ELEM_OPT_TLV_E(0x75, , DE_NAS_5GS_SM_MAPPED_EPS_B_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &mapped_eps_b_cont, d, ctx);
    d.step(consumed);

    /*78    EAP message    EAP message 9.11.3.14    O    TLV-E    7-1503*/
    // ELEM_OPT_TLV_E(0x78, , DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    /*79    Authorized QoS flow descriptions    QoS flow descriptions 9.11.4.12    O
     * TLV-E    6-65538 */
    // ELEM_OPT_TLV_E( 0x79, , DE_NAS_5GS_SM_QOS_FLOW_DES, " - Authorized");
    consumed = dissect_opt_elem_tlv_e(nullptr, &authorized_qos_rules, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options    Extended protocol configuration
     * options 9.11.4.2    O    TLV-E    4-65538*/
    // ELEM_OPT_TLV_E(0x7B, , DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    /* 25    DNN    DNN 9.11.2.1A    O    TLV    3-102 */
    // ELEM_OPT_TLV(0x25, , DE_NAS_5GS_CMN_DNN, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &dnn, d, ctx);
    d.step(consumed);

    // extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    d.extraneous_data_check(0);

    return len;
}

namespace sm_pdu_ses_est {
/*
 *      9.11.4.16    SSC mode
 */
static const val_string nas_5gs_sc_mode_values[] = {
    {0x1, "SSC mode 1"},
    {0x2, "SSC mode 2"},
    {0x3, "SSC mode 3"},
    {0, nullptr},
};
extern const field_meta hfm_sel_sc_mode = {
    "Selected SSC mode",
    "nas_5gs.sm.sel_sc_mode",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_sc_mode_values,
    nullptr,
    nullptr,
    0xf0,
};
const field_meta* hf_sel_sc_mode = &hfm_sel_sc_mode;

int dissect_pdu_ses_type(dissector d, context* ctx);
int dissect_pdu_address(dissector d, context* ctx);

extern const element_meta pdu_ses_type = {
    0xff,
    "Selected PDU session type",
    dissect_pdu_ses_type,
    nullptr,
};
extern const element_meta pdu_address = {
    0x29,
    "PDU address",
    dissect_pdu_address,
    nullptr,
};
extern const element_meta sm_s_nssai = {
    0x22,
    "S-NSSAI",
    dissect_sm_s_nssai,
    nullptr,
};
extern const element_meta dnn = {
    0x25,
    "DNN",
    dissect_dnn,
    nullptr,
};

int dissect_pdu_ses_type(dissector d, context* ctx) { return 0; }


/*
 *     9.11.4.10    PDU address
 */

static const value_string nas_5gs_sm_pdu_ses_type_vals[] = {
    {0x1, "IPv4"},
    {0x2, "IPv6"},
    {0x3, "IPv4v6"},
    {0, nullptr},
};
const field_meta hf_sm_pdu_ses_type = {
    "PDU session type",
    "nas_5gs.sm.pdu_ses_type",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_sm_pdu_ses_type_vals),
    nullptr,
    nullptr,
    0x0f,
};
const field_meta hf_pdu_addr_ipv4 = {
    "PDU address information",
    "nas_5gs.sm.pdu_addr_inf_ipv4",
    ft::ft_uint32,
    fd::ipv4,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_pdu_addr_ipv6 = {
    "PDU address information",
    "nas_5gs.sm.pdu_addr_inf_ipv6",
    ft::ft_bytes,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

int dissect_pdu_address(dissector d, context* ctx) {
    auto len = d.length;
    uint32_t val = (uint32_t) d.tvb->uint8(d.offset);
    auto item = d.add_item(1, &hf_sm_pdu_ses_type, enc::be);
    d.step(1);

    use_tree ut(d, item);
    /* PDU address information */
    switch(val){
    case 1: // ipv4
        d.add_item(4, &hf_pdu_addr_ipv4, enc::be);
        d.step(4);
        break;
    case 2: // ipv6
        /* If the PDU session type value indicates IPv6, the PDU address information in
         * octet 4 to octet 11 contains an interface identifier for the IPv6 link local
         * address.
         */
        d.add_item(8, &hf_pdu_addr_ipv6, enc::na);
        d.step(8);
        break;
    case 3: // ipv6 and ipv4
        /* If the PDU session type value indicates IPv4v6, the PDU address information in
         * octet 4 to octet 11 contains an interface identifier for the IPv6 link local
         * address and in octet 12 to octet 15 contains an IPv4 address.
         */
        d.add_item(8, &hf_pdu_addr_ipv6, enc::na);
        d.step(8);
        d.add_item(4, &hf_pdu_addr_ipv4, enc::be);
        d.step(4);
        break;
    default:
        diag("known value %d", val);
    }
    return 0;
}


} // namespace sm_pdu_ses_est
