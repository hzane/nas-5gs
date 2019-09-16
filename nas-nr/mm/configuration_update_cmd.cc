#include "../dissect_mm_msg.hh"
#include "../gsm.hh"
#include "../ber.hh"

using namespace cmn;
using namespace mm;
using namespace nas;

/* 8.2.19 Configuration update command */
int mm::dissect_config_update_cmd(dissector d, context* ctx) {
    use_context uc(ctx, "configuration-update-command", d, 3);
    // network to UE
    down_link(d.pinfo);

    /*D-    Configuration update indication 9.11.3.18 O    TV    1 */
    NASNR_AUTO(int) consumed = dissect_opt_tv_short(nullptr, &configure_update_indication, d, ctx);
    d.step(consumed);

    /*77    5G-GUTI    5GS mobile identity     9.11.3.4    O    TLV    TBD*/
    consumed = dissect_opt_tlv_e(nullptr, &guti_mobile_id, d, ctx);
    d.step(consumed);

    /*54    TAI list    Tracking area identity list     9.11.3.9    O    TLV    8-98*/
    consumed = dissect_opt_tlv(nullptr, &tracking_area_id_list, d, ctx);
    d.step(consumed);

    /*15    Allowed NSSAI    NSSAI     9.11.3.37    O    TLV    4-74*/
    // ELEM_OPT_TLV(0x15, , DE_NAS_5GS_MM_NSSAI, " - Allowed NSSAI");
    consumed = dissect_opt_tlv(nullptr, &allowed_nssai, d, ctx);
    d.step(consumed);

    /*27    Service area list    9.11.3.49    O    TLV    6-114 */
    consumed = dissect_opt_tlv(nullptr, &service_area_list, d, ctx);
    d.step(consumed);

    /*43  Full name for network   Network name    9.11.3.35   O   TLV    3-n*/
    // ELEM_OPT_TLV(0x43, , DE_NETWORK_NAME, " - Full name for network");
    consumed = dissect_opt_tlv(nullptr, &full_name_network, d, ctx);
    d.step(consumed);

    /*45    Short name for network    Network name     9.11.3.35    O    TLV    3-n*/
    // ELEM_OPT_TLV(0x45, , DE_NETWORK_NAME, " - Short Name");
    consumed = dissect_opt_tlv(nullptr, &short_name_network, d, ctx);
    d.step(consumed);

    /*46    Local time zone    Time zone     9.11.3.52    O    TV    2*/
    // ELEM_OPT_TV(0x46, , DE_TIME_ZONE, " - Local");
    consumed = dissect_opt_tv(nullptr, &local_timezone, d, ctx);
    d.step(consumed);

    /*47  Universal time and local time zone  Time zone and time  9.11.3.53  O TV  8*/
    /*ELEM_OPT_TV(0x47,,DE_TIME_ZONE_TIME," - Universal Time and Local Time Zone");*/
    consumed = dissect_opt_tv(nullptr, &timezone_time, d, ctx);
    d.step(consumed);

    /*49 Network daylight saving time Daylight saving time 9.11.3.19 O TLV 3*/
    consumed = dissect_opt_tlv(nullptr, &day_saving_time, d, ctx);
    d.step(consumed);

    /*79    LADN information 9.11.3.30    O    TLV-E    11-1579*/
    consumed = dissect_opt_tlv_e(nullptr, &ladn_information, d, ctx);
    d.step(consumed);

    /*B-    MICO indication  9.11.3.31    O    TV    1*/
    consumed = dissect_opt_tv_short(nullptr, &mico_indication, d, ctx);
    d.step(consumed);

    // 9-	Network slicing indication	 9.11.3.36 O TV 1
    // ELEM_OPT_TV_SHORT(0x90, , DE_NAS_5GS_MM_NW_SLICING_IND, NULL);
    consumed = dissect_opt_tv_short(nullptr, &nw_slicing_ind, d, ctx);
    d.step(consumed);

    /*31    Configured NSSAI    NSSAI     9.11.3.37    O    TLV    4-74*/
    // ELEM_OPT_TLV(0x31, , DE_NAS_5GS_MM_NSSAI, " - Configured NSSAI");
    consumed = dissect_opt_tlv(nullptr, &configured_nssai, d, ctx);
    d.step(consumed);

    /*11    Rejected NSSAI   9.11.3.46   O   TLV   4-42*/
    // ELEM_OPT_TLV(0x11, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_REJ_NSSAI, NULL);
    consumed = dissect_opt_tlv(nullptr, &rejected_nssai, d, ctx);
    d.step(consumed);

    /* 76 Operator-defined access category definitions   9.11.3.38   O   TLV-E  3-n */
    // ELEM_OPT_TLV_E(0x76, , DE_NAS_5GS_MM_OP_DEF_ACC_CAT_DEF, NULL);
    consumed = dissect_opt_tlv_e(nullptr, &operator_defined_access_category_defs, d, ctx);
    d.step(consumed);

    /* F-    SMS indication    SMS indication 9.10.3.50A    O    TV    1 */
    // ELEM_OPT_TV_SHORT(0xF0, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_SMS_IND, NULL);
    consumed = dissect_opt_tv_short(nullptr, &sms_ind, d, ctx);
    d.step(consumed);

    // Tbd	T3447 value	GPRS timer 3    9.11.2.5 O TLV 3

    return uc.length;
}

namespace mm {

extern const element_meta sms_ind = {
    0xF0,
    "SMS indication",
    dissect_sms_indication,
    nullptr,

};

const field_meta hf_conf_upd_ind_reg_b1 = {
    "Registration",
    "nas.nr.configure.update.indication.reg",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_requested_or_not,
    nullptr,
    0x02,
};
const field_meta hf_conf_upd_ind_ack_b0 = {
    "Acknowledgement",
    "nas.nr.mm.configure.update.indication.ack",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_requested_or_not,
    nullptr,
    0x01,
};


/*
 * [3] 10.5.3.12 Daylight Saving Time
 */
static const value_string gsm_a_dtap_dst_adjustment_vals[] = {
    {0, "No adjustment for Daylight Saving Time"},
    {1, "+1 hour adjustment for Daylight Saving Time"},
    {2, "+2 hours adjustment for Daylight Saving Time"},
    {3, "Reserved"},
    {0, nullptr},
};
const field_meta hf_dst_adjustment = {
    "DST Adjustment",
    "gsm_a.dtap.dst_adjustment",
    ft::ft_uint8,
    fd::base_dec,
    gsm_a_dtap_dst_adjustment_vals,
    nullptr,
    nullptr,
    0x03,
};


/* [3] 10.5.3.5a Network Name */
static const value_string gsm_a_dtap_number_of_spare_bits_vals[] = {
    {0, "this field carries no information about the number of spare bits in octet n"},
    {1, "bit 8 is spare and set to '0' in octet n"},
    {2, "bits 7 and 8 are spare and set to '0' in octet n"},
    {3, "bits 6 to 8(inclusive) are spare and set to '0' in octet n"},
    {4, "bits 5 to 8(inclusive) are spare and set to '0' in octet n"},
    {5, "bits 4 to 8(inclusive) are spare and set to '0' in octet n"},
    {6, "bits 3 to 8(inclusive) are spare and set to '0' in octet n"},
    {7, "bits 2 to 8(inclusive) are spare and set to '0' in octet n"},
    {0, nullptr},
};

const true_false_string tfs_add_ci = {
    "The MS should add the letters for the Country's Initials and a separator (e.g. a "
    "space) to the text string",
    "The MS should not add the letters for the Country's Initials to the text string",
};

static const value_string gsm_a_dtap_coding_scheme_vals[] = {
    {0,
     "Cell Broadcast data coding scheme, GSM default alphabet, language unspecified, "
        "defined in 3GPP TS 23.038",
    },
    {1, "UCS2 (16 bit)"},
    {2, "Reserved"},
    {3, "Reserved"},
    {4, "Reserved"},
    {5, "Reserved"},
    {6, "Reserved"},
    {7, "Reserved"},
    {0, nullptr},
};

static const true_false_string gsm_a_extension_value = {"No Extension", "Extended"};

const field_meta hf_extension = {
    "Extension",
    "gsm.extension",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &gsm_a_extension_value,
    nullptr,
    0x80,
};

const field_meta hf_coding_scheme = {
    "Coding Scheme",
    "gsm_a.dtap.coding_scheme",
    ft::ft_uint8,
    fd::base_dec,
    gsm_a_dtap_coding_scheme_vals,
    nullptr,
    nullptr,
    0x70,
};

const field_meta hf_add_ci = {
    "Add CI",
    "gsm_a.dtap.add_ci",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_add_ci,
    nullptr,
    0x08,
};

const field_meta hf_number_of_spare_bits = {
    "Number of spare bits in last octet",
    "gsm_a.dtap.number_of_spare_bits",
    ft::ft_uint8,
    fd::base_dec,
    gsm_a_dtap_number_of_spare_bits_vals,
    nullptr,
    nullptr,
    0x07,
};

const field_meta hf_text_string = {
    "Text String",
    "gsm_a.dtap.text_string",
    ft::ft_bytes,
    fd::bits7,
    nullptr,nullptr,nullptr,
    0x0,
};




}
