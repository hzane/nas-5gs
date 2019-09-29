#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace mm;
using namespace nas;


/* * 8.2.6 Registration request */
int mm::dissect_registration_request(dissector d, context* ctx) {
    const use_context uc(ctx, "registration-request", d, -1);

    // UE to network
    up_link(d.packet);
    // get private data

    /*   5GS registration type  9.11.3.7    M    V    1/2  H0*/
    (void) dissect_registration_requestuest_type(d, ctx);
    /*    ngKSI    NAS key set identifier 9.11.3.32    M    V    1/2 H1*/
    (void) dissect_v( &nas_ksi, d, ctx);
    d.step(1);

    /* 5GS mobile identity 9.11.3.4    M    LV-E    6-n*/
    auto consumed = dissect_lv_e( &mobile_id, d, ctx);
    d.step(consumed);

    /*C-    Non-current native NAS KSI    NAS key set identifier 9.11.3.32    O    TV 1*/
    // ELEM_OPT_TV_SHORT( 0xc0, , DE_NAS_5GS_MM_NAS_KEY_SET_ID, " - native KSI");
    consumed = dissect_opt_tv_short( &nc_native_nas_ksi, d, ctx);
    d.step(consumed);

    /*10    5GMM capability  9.11.3.1    O    TLV    3-15*/
    consumed = dissect_opt_tlv( &nrmm_capability, d, ctx);
    d.step(consumed);

    /*2E    UE security capability   9.11.3.54    O    TLV 4-10*/
    consumed = dissect_opt_tlv( &ue_security_capability, d, ctx);
    d.step(consumed);

    /*2F    Requested NSSAI    NSSAI 9.11.3.37    O    TLV    4-74*/
    consumed = dissect_opt_tlv( &requested_nssai, d, ctx);
    d.step(consumed);

    /*52 Last visited registered TAI 5GS tracking area identity 9.11.3.8 O TV  7 */
    // ELEM_OPT_TV(0x52, DE_NAS_5GS_MM_5GS_TA_ID, " - Last visited registered TAI");
    consumed = dissect_opt_tv( &last_visited_tai, d, ctx);
    d.step(consumed);

    /*17    S1 UE network capability  9.11.3.48    O    TLV  4-15 */
    // ELEM_OPT_TLV(0x17, , DE_EMM_UE_NET_CAP, NULL);
    consumed = dissect_opt_tlv( &s1_ue_network_capability, d, ctx);
    d.step(consumed);

    /*40    Uplink data status  9.11.3.57    O    TLV    4-34 */
    // ELEM_OPT_TLV(0x40, , DE_NAS_5GS_MM_UL_DATA_STATUS, NULL);
    consumed = dissect_opt_tlv( &uplink_data_status, d, ctx);
    d.step(consumed);

    /*50    PDU session status  9.11.3.44    O    TLV    4-34 */
    // ELEM_OPT_TLV(0x50, , DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    consumed = dissect_opt_tlv( &pdu_session_status, d, ctx);
    d.step(consumed);

    /*B-  MICO indication 9.11.3.31    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0xb0, , DE_NAS_5GS_MM_MICO_IND, NULL);
    consumed = dissect_opt_tv_short( &mico_indication, d, ctx);
    d.step(consumed);

    /*2B UE status 9.11.3.56    O    TLV    3*/
    // ELEM_OPT_TLV(0x2b, , DE_NAS_5GS_MM_UE_STATUS, NULL);
    consumed = dissect_opt_tlv( &ue_status, d, ctx);
    d.step(consumed);

    /*77    Additional GUTI    5GS mobile identity 9.11.3.4    O    TLV-E    14 */
    // ELEM_OPT_TLV_E(0x77, , DE_NAS_5GS_MM_5GS_MOBILE_ID, " -  Additional GUTI");
    consumed = dissect_opt_tlv_e( &aguti_mobile_id, d, ctx);
    d.step(consumed);

    /*25    Allowed PDU session status    9.11.3.13  O    TLV    4 - 34 */
    // ELEM_OPT_TLV(0x25, , DE_NAS_5GS_MM_ALLOW_PDU_SES_STS, NULL);
    consumed = dissect_opt_tlv( &allowed_pdu_session_status, d, ctx);
    d.step(consumed);

    /*18    UE's usage setting    9.11.3.55    O    TLV    3 */
    // ELEM_OPT_TLV(0x18, , DE_NAS_5GS_MM_UE_USAGE_SET, NULL);
    consumed = dissect_opt_tlv( &ue_usage_setting, d, ctx);
    d.step(consumed);

    /* 51    Requested DRX parameters    5GS DRX parameters 9.11.3.2A    O    TLV    3 */
    /* ELEM_OPT_TLV(0x51,DE_NAS_5GS_MM_5GS_DRX_PARAM, " - Requested DRX parameters"); */
    consumed = dissect_opt_tlv( &requested_drx_parameter, d, ctx);
    d.step(consumed);

    /* 70    EPS NAS message container  9.11.3.24    O    TLV-E 4-n */
    // ELEM_OPT_TLV_E(0x70, , DE_NAS_5GS_MM_EPS_NAS_MSG_CONT, NULL);
    consumed = dissect_opt_tlv_e( &eps_nas_message_container, d, ctx);
    d.step(consumed);

    /* 74    LADN indication  9.11.3.29    O    TLV-E    3-811 */
    // ELEM_OPT_TLV_E(0x74, , DE_NAS_5GS_MM_LADN_IND, NULL);
    consumed = dissect_opt_tlv_e( &ladn_indication, d, ctx);
    d.step(consumed);

    /* 8-    Payload container type  9.11.3.40    O    TV    1 */
    // ELEM_OPT_TV_SHORT(0x80, , DE_NAS_5GS_MM_PLD_CONT_TYPE, NULL);
    consumed = dissect_opt_tv_short( &payload_container_type, d, ctx);
    d.step(consumed);

    /* 7B    Payload container  9.11.3.39    O    TLV-E    4-65538 */
    // ELEM_OPT_TLV_E(0x7B, , DE_NAS_5GS_MM_PLD_CONT, NULL);
    consumed = dissect_opt_tlv_e( &payload_container, d, ctx);
    d.step(consumed);

    /* 9-    Network slicing indication 9.11.3.36    O    TV 1 */
    // ELEM_OPT_TV_SHORT(0x90, , DE_NAS_5GS_MM_network_slicing_indication, NULL);
    consumed = dissect_opt_tv_short( &network_slicing_indication, d, ctx);
    d.step(consumed);

    /* 53    5GS update type 9.11.3.9A    O    TLV    3 */
    // ELEM_OPT_TLV(0x53, , DE_NAS_5GS_MM_UPDATE_TYPE, NULL);
    consumed = dissect_opt_tlv( &update_type, d, ctx);
    d.step(consumed);

    /*TBD	Mobile station classmark 2	9.11.3.61	O	TLV	5
     *TBD	Supported codecs	Supported codec list 9.11.3.62	O	TLV	5-n */


    /* 71    NAS message container 9.11.3.33    O    TLV-E    4-n */
    // ELEM_OPT_TLV_E(0x71, , DE_NAS_5GS_MM_NAS_MSG_CONT, NULL);
    consumed = dissect_opt_tlv_e( &nas_msg_container, d, ctx);
    d.step(consumed);

    /*60	EPS bearer context status	9.11.3.59	O	TLV	4 */
    consumed = dissect_opt_tlv( &eps_bearer_context_status, d, ctx);
    d.step(consumed);

    /* XX	Requested extended DRX parameters 9.11.3.60	O TLV 3*/
    /* TBD	T3324 value	GPRS timer 3 9.11.2.5	O	TLV	3 */

    return uc.length;
}

static const char* supported = "Supported";
static const char* notsupported = "Not supported";
namespace mm {
const bool_field hf_ea0 = {
    "5G-EA0",
    0x80,
    notsupported,supported,
};
const bool_field hf_ea1 = {
    "128-5G-EA1",
    0x40,
    notsupported,supported,
};
const bool_field hf_ea2 = {
    "128-5G-EA2",
    0x20,
    notsupported,supported,
};
const bool_field hf_ea3 = {
    "128-5G-EA3",
    0x10,
    notsupported,supported,
};

} // namespace mm


namespace mm {
const bool_field hf_nas_eps_emm_eea0 = {
    "EEA0",
    0x80,
    notsupported,supported,
};

const bool_field hf_nas_eps_emm_128eea1 = {
    "128-EEA1",
    0x40,
    notsupported,supported,
};

const bool_field hf_nas_eps_emm_128eea2 = {
    "128-EEA2",
    0x20,
    notsupported,supported,
};

const bool_field hf_nas_eps_emm_eea3 = {
    "128-EEA3",
    0x10,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_eea4 = {
    "EEA4",
    0x08,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_eea5 = {
    "EEA5",
    0x04,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_eea6 = {
    "EEA6",
    0x02,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_eea7 = {
    "EEA7",
    0x01,
    notsupported,supported,
};

const bool_field hf_nas_eps_emm_eia0 = {
    "EIA0",
    0x80,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_128eia1 = {
    "128-EIA1",
    0x40,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_128eia2 = {
    "128-EIA2",
    0x20,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_eia3 = {
    "128-EIA3",
    0x10,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_eia4 = {
    "EIA4",
    0x08,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_eia5 = {
    "EIA5",
    0x04,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_eia6 = {
    "EIA6",
    0x02,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_eia7 = {
    "EIA7",
    0x01,
    notsupported,supported,
};

const bool_field hf_nas_eps_emm_uea0 = {
    "UEA0",
    0x80,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_uea1 = {
    "UEA1",
    0x40,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_uea2 = {
    "UEA2",
    0x20,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_uea3 = {
    "UEA3",
    0x10,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_uea4 = {
    "UEA4",
    0x08,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_uea5 = {
    "UEA5",
    0x04,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_uea6 = {
    "UEA6",
    0x02,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_uea7 = {
    "UEA7",
    0x01,
    notsupported,supported,
};

// S1 UE network capability 9.11.3.48
const bool_field hf_nas_eps_emm_ucs2_supp = {
    "UCS2 support (UCS2)",
    0x80,
    "The UE has a preference for the default alphabet",
    "The UE has no preference between the use of the default alphabet and the use of "
    "UCS2",
};
const bool_field hf_nas_eps_emm_uia1 = {
    "UMTS integrity algorithm UIA1",
    0x40,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_uia2 = {
    "UMTS integrity algorithm UIA2",
    0x20,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_uia3 = {
    "UMTS integrity algorithm UIA3",
    0x10,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_uia4 = {
    "UMTS integrity algorithm UIA4",
    0x08,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_uia5 = {
    "UMTS integrity algorithm UIA5",
    0x04,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_uia6 = {
    "UMTS integrity algorithm UIA6",
    0x02,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_uia7 = {
    "UMTS integrity algorithm UIA7",
    0x01,
    notsupported,supported,
};

const bool_field hf_nas_eps_emm_prose_dd_cap = {
    "ProSe direct discovery",
    0x80,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_prose_cap = {
    "ProSe",
    0x40,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_h245_ash_cap = {
    "H.245 After SRVCC Handover",
    0x20,
    notsupported,supported,
};
const bool_field hf_access_class_control_csfb_cap = {
    "Access class control for CSFB",
    0x10,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_lpp_cap = {
    "LTE Positioning Protocol",
    0x08,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_lcs_cap = {
    "Location services (LCS) notification mechanisms",
    0x04,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_1xsrvcc_cap = {
    "SRVCC from E-UTRAN to cdma2000 1xCS",
    0x02,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_nf_cap = {
    "Notification procedure",
    0x01,
    notsupported,supported,
};

const bool_field hf_nas_eps_emm_epco_cap = {
    "Extended protocol configuration options",
    0x80,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_hc_cp_ciot_cap = {
    "Header compression for control plane CIoT EPS optimization",
    0x40,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_er_wo_pdn_cap = {
    "EMM-REGISTERED w/o PDN connectivity",
    0x20,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_s1u_data_cap = {
    "S1-U data transfer",
    0x10,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_up_ciot_cap = {
    "User plane CIoT EPS optimization",
    0x08,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_cp_ciot_cap = {
    "Control plane CIoT EPS optimization",
    0x04,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_prose_relay_cap = {
    "ProSe UE-to-network relay",
    0x02,
    notsupported,supported,
};
const bool_field hf_nas_eps_emm_prose_dc_cap = {
    "ProSe direct communication",
    0x01,
    notsupported,supported,
};

const bool_field hf_nas_eps_15_bearers_cap = {
    "Signalling for a maximum number of 15 EPS bearer contexts",
    0x80,
    notsupported,supported,
};
const bool_field hf_nas_eps_sgc_cap = {
    "Service gap control",
    0x40,
    notsupported,supported,
};
const bool_field hf_nas_eps_n1mode_cap = {
    "N1 mode",
    0x20,
    notsupported,supported,
};
const bool_field hf_nas_eps_dcnr_cap = {
    "Dual connectivity with NR",
    0x10,
    notsupported,supported,
};
const bool_field hf_nas_eps_cp_backoff_cap = {
    "Control plane data backoff",
    0x08,
    notsupported,supported,
};
const bool_field hf_nas_eps_restrict_ec_cap = {
    "Restriction on use of enhanced coverage",
    0x04,
    notsupported,supported,
};
const bool_field hf_nas_eps_v2x_pc5_cap = {
    "V2X communication over PC5",
    0x02,
    notsupported,supported,
};
const bool_field hf_nas_eps_multiple_drb_cap = {
    "Multiple DRB",
    0x01,
    notsupported,supported,
};

const uint8_field hf_nas_eps_spare_bits = {
    "Spare bit(s)",
    0x0,
    notsupported,supported,
};

} // namespace mm


const tf_string tfs_nas_5gs_mm_n1_mod = { // NOLINT
    "UE is in 5GMM-REGISTERED state",
    "UE is not in 5GMM-REGISTERED state",
};


/* 9.11.3.9A    5GS update type */
const tf_string tfs_nas5gs_sms_requested = { // NOLINT
    "SMS over NAS supported",
    "SMS over NAS not supported",
};

const bool_field        mm::hf_ngran_radio_capability_update = {
    "NG-RAN Radio Capability Update (NG-RAN-RCU)",
    0x02,
    "Not Needed",
    "Needed",
};

const tag_field mm::hf_preferred_network_behaviour = {
    "Preferred CIoT network behaviour (PNB-CIoT)",
    0,
    (const v_string[]){
        {0, "no additional information"},
        {1, "control plane CIot 5GS optimization"},
        {2, "user plane CIot 5GS optimization"},
        {3, "reserved"},
        {0, nullptr},
    },
};
