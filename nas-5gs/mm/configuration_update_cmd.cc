#include <ctime>
#include "../dissect_mm_msg.hh"
#include "../gsm.hh"
#include "../ts24007.hh"

using namespace cmn;
using namespace mm;
using namespace nas;

/* 8.2.19 Configuration update command */
int mm::dissect_conf_upd_cmd(dissector d, context* ctx) {
    use_context uc(ctx, "configuration-update-command", d, 3);
    // network to UE
    down_link(d.pinfo);

    /*D-    Configuration update indication 9.11.3.18 O    TV    1 */
    // ELEM_OPT_TV_SHORT(0xD0, , DE_NAS_5GS_MM_CONF_UPD_IND, NULL);
    auto consumed = dissect_opt_elem_tv_short(nullptr, &conf_upd_ind, d, ctx);
    d.step(consumed);

    /*77    5G-GUTI    5GS mobile identity     9.11.3.4    O    TLV    TBD*/
    // ELEM_OPT_TLV_E(0x77, , DE_NAS_5GS_MM_5GS_MOBILE_ID, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &guti, d, ctx);
    d.step(consumed);

    /*54    TAI list    Tracking area identity list     9.11.3.9    O    TLV    8-98*/
    // ELEM_OPT_TLV(0x54, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_5GS_TA_ID_LIST, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ta_id_list, d, ctx);
    d.step(consumed);

    /*15    Allowed NSSAI    NSSAI     9.11.3.37    O    TLV    4-74*/
    // ELEM_OPT_TLV(0x15, , DE_NAS_5GS_MM_NSSAI, " - Allowed NSSAI");
    consumed = dissect_opt_elem_tlv(nullptr, &allowed_nssai, d, ctx);
    d.step(consumed);

    /*27    Service area list    9.11.3.49    O    TLV    6-194 */
    // ELEM_OPT_TLV(0x70, , DE_NAS_5GS_MM_SAL, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &service_area_list, d, ctx);
    d.step(consumed);

    /*43  Full name for network   Network name    9.11.3.35   O   TLV    3-n*/
    // ELEM_OPT_TLV(0x43, , DE_NETWORK_NAME, " - Full name for network");
    consumed = dissect_opt_elem_tlv(nullptr, &full_name_network, d, ctx);
    d.step(consumed);

    /*45    Short name for network    Network name     9.11.3.35    O    TLV    3-n*/
    // ELEM_OPT_TLV(0x45, , DE_NETWORK_NAME, " - Short Name");
    consumed = dissect_opt_elem_tlv(nullptr, &short_name_network, d, ctx);
    d.step(consumed);

    /*46    Local time zone    Time zone     9.11.3.52    O    TV    2*/
    // ELEM_OPT_TV(0x46, , DE_TIME_ZONE, " - Local");
    consumed = dissect_opt_elem_tv(nullptr, &local_time_zone, d, ctx);
    d.step(consumed);

    /*47  Universal time and local time zone  Time zone and time  9.11.3.53  O TV  8*/
    /*ELEM_OPT_TV(0x47,,DE_TIME_ZONE_TIME," - Universal Time and Local Time Zone");*/
    consumed = dissect_opt_elem_tv(nullptr, &u_time_zone_time, d, ctx);
    d.step(consumed);

    /*49 Network daylight saving time Daylight saving time 9.11.3.19 O TLV 3*/
    // ELEM_OPT_TLV(0x49, , DE_DAY_SAVING_TIME, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &day_saving_time, d, ctx);
    d.step(consumed);

    /*79    LADN information 9.11.3.30    O    TLV-E    11-1579*/
    // ELEM_OPT_TLV_E(0x79, , DE_NAS_5GS_MM_LADN_INF, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ladn_inf, d, ctx);
    d.step(consumed);

    /*B-    MICO indication  9.11.3.31    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0xB0, , DE_NAS_5GS_MM_MICO_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &mico_ind, d, ctx);
    d.step(consumed);

    // 9-	Network slicing indication	 9.11.3.36 O TV 1
    // ELEM_OPT_TV_SHORT(0x90, , DE_NAS_5GS_MM_NW_SLICING_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &nw_slicing_ind, d, ctx);
    d.step(consumed);

    /*31    Configured NSSAI    NSSAI     9.11.3.37    O    TLV    4-74*/
    // ELEM_OPT_TLV(0x31, , DE_NAS_5GS_MM_NSSAI, " - Configured NSSAI");
    consumed = dissect_opt_elem_tlv(nullptr, &configured_nssai, d, ctx);
    d.step(consumed);

    /*11    Rejected NSSAI   9.11.3.46   O   TLV   4-42*/
    // ELEM_OPT_TLV(0x11, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_REJ_NSSAI, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &rej_nssai, d, ctx);
    d.step(consumed);

    /* 76 Operator-defined access category definitions   9.11.3.38   O   TLV-E  3-n */
    // ELEM_OPT_TLV_E(0x76, , DE_NAS_5GS_MM_OP_DEF_ACC_CAT_DEF, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &op_def_acc_cat_def, d, ctx);
    d.step(consumed);

    /* F-    SMS indication    SMS indication 9.10.3.50A    O    TV    1 */
    // ELEM_OPT_TV_SHORT(0xF0, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_SMS_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &sms_ind, d, ctx);
    d.step(consumed);

    // Tbd	T3447 value	GPRS timer 3    9.11.2.5 O TLV 3

    return uc.length;
}

namespace mm {


extern const element_meta guti = {
    0x77,
    "5GS mobile identity - 5G-GUTI",
    dissect_guti,
    nullptr,
};



extern const element_meta service_area_list = {
    0x70,
    "Service area list",
    dissect_sal,
    nullptr,

};

extern const element_meta local_time_zone = {
    0x46,
    "Local time zone",
    dissect_local_time_zone,
    nullptr,

};

// 9.11.3.53
extern const element_meta u_time_zone_time = {
    0x47,
    "Time zone and time - Universal time and local time zone",
    dissect_time_zone_time,
    nullptr,

};


extern const element_meta op_def_acc_cat_def = {
    0x76,
    "Operator-defined access category definitions",
    dissect_op_def_acc_cat_def,
    nullptr,

};

extern const element_meta sms_ind = {
    0xF0,
    "SMS indication",
    dissect_sms_ind,
    nullptr,

};

const field_meta hf_conf_upd_ind_red_b1 = {
    "Registration",
    "nas_5gs.mm.conf_upd_ind.red",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_requested_or_not,
    nullptr,
    0x02,
};
const field_meta hf_conf_upd_ind_ack_b0 = {
    "Acknowledgement",
    "nas_5gs.mm.conf_upd_ind.ack",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_requested_or_not,
    nullptr,
    0x01,
};


int dissect_guti(dissector d, context* ctx) { return dissect_mobile_id(d, ctx); }

string abs_time_str(tm t) {
    const char* ts = asctime(&t);
    return ts ? string(ts) : string();
}
/* [3] 10.5.3.9 Time Zone and Time */
int dissect_time_zone_time(dissector d, context* ctx) {
    // auto len = d.length;
    tm   t   = {0, 0, 0, 0, 0, 0, 0, 0, -1};

    auto oct = static_cast< int >(d.tvb->uint8(d.offset));
    t.tm_year = (oct & 0x0f) * 10 + ((oct & 0xf0) >> 4) * 100;

    oct = d.tvb->uint8(d.offset + 1);
    t.tm_mon = (oct & 0x0f) * 10 + ((oct & 0xf0) >> 4) - 1;

    oct = d.tvb->uint8(d.offset + 2);
    t.tm_mday = (oct & 0x0f) * 10 + ((oct & 0xf0) >> 4);

    oct = d.tvb->uint8(d.offset + 3);
    t.tm_hour = (oct & 0x0f) * 10 + ((oct & 0xf0) >> 4);

    oct       = d.tvb->uint8(d.offset + 4);
    t.tm_min= (oct & 0x0f) * 10 + ((oct & 0xf0) >> 4);

    oct       = d.tvb->uint8(d.offset + 5);
    t.tm_sec = (oct & 0x0f) * 10 + ((oct & 0xf0) >> 4);

    d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 6, abs_time_str(t).c_str());
    d.step(6);

    oct = d.tvb->uint8(d.offset);
    const auto sign = (oct & 0x08) ? '-' : '+';
    oct       = (oct >> 4) + (oct & 0x07) * 10;
    d.tree->add_subtree(d.pinfo,
                        d.tvb,
                        d.offset,
                        1,
                        "GMT %c %d hours %d minutes",
                        sign,
                        oct / 4,
                        oct % 4 * 15);
    d.step(1);

    /* no length check possible */
    return 7;
}

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

const field_meta hf_a_extension = {
    "Extension",
    "gsm_a.extension",
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


/* 3GPP TS 23.040 version 6.6.0 Release 6
 * [3] 10.5.3.8 Time Zone */
int dissect_local_time_zone(dissector d, context* ctx) {
    const use_context uc(ctx, "local-time-zone", d, -1);

    /* 3GPP TS 23.040 version 6.6.0 Release 6
     * 9.2.3.11 TP-Service-Centre-Time-Stamp (TP-SCTS)
     * :
     * The Time Zone indicates the difference, expressed in quarters of an hour,
     * between the local time and GMT. In the first of the two semi-octets,
     * the first bit (bit 3 of the seventh octet of the TP-Service-Centre-Time-Stamp
     * field) represents the algebraic sign of this difference (0: positive, 1: negative).
     */
    auto oct = d.tvb->uint8(d.offset);
    const auto sign = (oct & 0x08) ? '-' : '+';

    oct = (oct >> 4) + (oct & 0x07) * 10;

    auto n = d.add_item(1, "GMT %c %d hours %d minutes", sign, oct / 4, oct % 4 * 15);

    unused(n);
    /* no length check possible */
    return 1;
}


const field_meta hf_precedence = {
    "Precedence",
    "nas_5gs.mm.precedence",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

// Operator-defined access category number
const field_meta hf_access_cat_n = {
    "Operator-defined access category number",
    "nas_5gs.mm.conf.update.operator.access.category.number",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x1f,
};
const tf_string  tfs_standardized_category_field = {
    "Standardized access category field is included",
    "Standardized access category field is not included",
};

const field_meta hf_psac = {
    "Presence of standardized access category (PSAC)",
    "nas_5gs.mm.conf.update.operator.access.category.psac",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_standardized_category_field,
    nullptr,
    0x80,
};
const field_meta hf_criteria_length = {
    "Length",
    "nas_5gs.mm.conf.update.operator.access.criteria.length",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0,
};

const field_meta hf_criteria= {
    "Criteria",
    "nas_5gs.mm.conf.update.operator.access.criteria",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0,
};

const field_meta hf_standardize_access_cat = {
    "Standardized access category",
    "nas_5gs.mm.conf.update.operator.access.category.type",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x1f,
};

/*  9.11.3.38    Operator-defined access category definitions */
int dissect_op_def_acc_cat_def(dissector d, context* ctx) {
    const use_context uc(ctx, "operator-defined-access-category-definitions", d, 0);

    auto i   = 1;
    while (d.length > 0) {
        const auto length  = static_cast< int >(d.tvb->uint8(d.offset));
        auto       sd      = d.slice(length + 1);
        const auto subtree = d.add_item(
            length + 1, "Operator-defined access category definition  %u", i++);
        use_tree ut(sd, subtree);
        use_context suc(ctx, "operator-defined-access-category-definition", sd, 0);

        auto n = sd.add_item(1, &hf_mm_length, enc::be);
        sd.step(1);

        /* Precedence value */
        n = sd.add_item(1, &hf_precedence, enc::be);
        sd.step(1);

        /* PSAC    0 Spare    0 Spare    Operator-defined access category number */
        auto psac = (sd.uint8() & 0x80u) ;
        n = sd.add_item(1, &hf_access_cat_n, enc::be);
        n = sd.add_item(1, &hf_psac, enc::be);
        sd.step(1);

        /* Length of criteria */
        const auto cl = static_cast< int >(sd.uint8());
        n = sd.add_item(1, &hf_criteria_length, enc::be);
        sd.step(1);

        /* Criteria */
        n = sd.add_item(cl, &hf_criteria, enc::na);

        /* Spare Spare Spare    Standardized access category a* */
        if (psac) {
            n = sd.add_item(1, &hf_standardize_access_cat, enc::be);
            sd.step(1);
        }

        d.step(length+1);

        unused(n);
    }
    return uc.length;
}
namespace {
    static const true_false_string tfs_allowed_or_not = {
        "Allowed",
        "Not Allowed",
    };
}
const field_meta hf_sms_indic_sai = {
    "SMS over NAS",
    "nas_5gs.mm.ms_indic.sai",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_allowed_or_not,
    nullptr,
    0x01,
};

/*
 *   9.11.3.50A    SMS indication
 */
int dissect_sms_ind(dissector d, context* ctx) {
    d.add_item(1, &hf_sms_indic_sai, enc::be);
    return 1;
}


} // namespace
