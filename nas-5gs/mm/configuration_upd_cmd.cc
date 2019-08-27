#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_conf_upd_cmd {
extern const element_meta conf_upd_ind;
extern const element_meta guti;

extern const element_meta allowed_nssai;
extern const element_meta day_saving_time;
extern const element_meta ladn_inf;
extern const element_meta mico_ind;
extern const element_meta rej_nssai;
extern const element_meta service_area_list;
extern const element_meta full_name_network;
extern const element_meta short_name_network;
extern const element_meta local_time_zone;
extern const element_meta u_time_zone_time;
extern const element_meta configured_nssai;
extern const element_meta op_def_acc_cat_def;
extern const element_meta sms_ind;
} // namespace mm_conf_upd_cmd

using namespace mm;

/*
 * 8.2.19 Configuration update command
 */
int mm::conf_upd_cmd(dissector d, context* ctx) {
    use_context uc(ctx, "configuration-update-command");

    using namespace mm_conf_upd_cmd;

    /*D-    Configuration update indication    Configuration update indication 9.11.3.16
     * O    TV    1 */
    // ELEM_OPT_TV_SHORT(0xD0, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_CONF_UPD_IND, NULL);
    auto consumed = dissect_opt_elem_tv_short(nullptr, &conf_upd_ind, d, ctx);
    d.step(consumed);

    /*77    5G-GUTI    5GS mobile identity     9.11.3.4    O    TLV    TBD*/
    // ELEM_OPT_TLV_E(0x77, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_5GS_MOBILE_ID, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &mobile_id, d, ctx);
    d.step(consumed);

    /*54    TAI list    Tracking area identity list     9.11.3.45    O    TLV    8-98*/
    // ELEM_OPT_TLV(0x54, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_5GS_TA_ID_LIST, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ta_id_list, d, ctx);
    d.step(consumed);

    /*15    Allowed NSSAI    NSSAI     9.11.3.28    O    TLV    4-74*/
    // ELEM_OPT_TLV(0x15, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NSSAI, " - Allowed NSSAI");
    consumed = dissect_opt_elem_tlv(nullptr, &allowed_nssai, d, ctx);
    d.step(consumed);

    /*27    Service area list    Service area list     9.11.3.39    O    TLV    6-194 */
    // ELEM_OPT_TLV(0x70, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_SAL, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &service_area_list, d, ctx);
    d.step(consumed);

    /*43    Full name for network    Network name     9.11.3.26    O    TLV    3-n*/
    // ELEM_OPT_TLV(0x43, , DE_NETWORK_NAME, " - Full name for network");
    consumed = dissect_opt_elem_tlv(nullptr, &full_name_network, d, ctx);
    d.step(consumed);

    /*45    Short name for network    Network name     9.11.3.26    O    TLV    3-n*/
    // ELEM_OPT_TLV(0x45, GSM_A_PDU_TYPE_DTAP, DE_NETWORK_NAME, " - Short Name");
    consumed = dissect_opt_elem_tlv(nullptr, &short_name_network, d, ctx);
    d.step(consumed);

    /*46    Local time zone    Time zone     9.11.3.46    O    TV    2*/
    // ELEM_OPT_TV(0x46, GSM_A_PDU_TYPE_DTAP, DE_TIME_ZONE, " - Local");
    consumed = dissect_opt_elem_tv(nullptr, &local_time_zone, d, ctx);
    d.step(consumed);

    /*47    Universal time and local time zone    Time zone and time     9.11.3.47    O
     * TV    8*/
    /*ELEM_OPT_TV(0x47,GSM_A_PDU_TYPE_DTAP,DE_TIME_ZONE_TIME," - Universal Time and Local
     * Time Zone");*/

    consumed = dissect_opt_elem_tv(nullptr, &u_time_zone_time, d, ctx);
    d.step(consumed);

    /*49    Network daylight saving time    Daylight saving time     9.11.3.11    O    TLV
     * 3*/
    // ELEM_OPT_TLV(0x49, GSM_A_PDU_TYPE_DTAP, DE_DAY_SAVING_TIME, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &day_saving_time, d, ctx);
    d.step(consumed);

    /*79    LADN information    LADN information     9.11.3.19    O    TLV-E    11-1579*/
    // ELEM_OPT_TLV_E(0x79, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_LADN_INF, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ladn_inf, d, ctx);
    d.step(consumed);

    /*B-    MICO indication    MICO indication     9.11.3.21    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0xB0, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_MICO_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &mico_ind, d, ctx);
    d.step(consumed);

    /*31    Configured NSSAI    NSSAI     9.11.3.28    O    TLV    4-74*/
    // ELEM_OPT_TLV(0x31, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NSSAI, " - Configured
    // NSSAI");
    consumed = dissect_opt_elem_tlv(nullptr, &configured_nssai, d, ctx);
    d.step(consumed);

    /*11    Rejected NSSAI     Rejected NSSAI   9.11.3.42   O   TLV   4-42*/
    // ELEM_OPT_TLV(0x11, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_REJ_NSSAI, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &rej_nssai, d, ctx);
    d.step(consumed);

    /* 76    Operator-defined access category definitions    Operator-defined access
     * category definitions 9.11.3.38    O    TLV-E    3-TBD */
    // ELEM_OPT_TLV_E(0x76, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_OP_DEF_ACC_CAT_DEF, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &op_def_acc_cat_def, d, ctx);
    d.step(consumed);

    /* F-    SMS indication    SMS indication 9.10.3.50A    O    TV    1 */
    // ELEM_OPT_TV_SHORT(0xF0, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_SMS_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &sms_ind, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return d.tvb->reported_length;
}

namespace mm_conf_upd_cmd {
int dissect_conf_upd_ind(dissector d, context* ctx);
int dissect_guti(dissector d, context* ctx);
int dissect_sal(dissector d, context* ctx);
int dissect_time_zone_time(dissector d, context* ctx);
int dissect_day_saving_time(dissector d, context* ctx);
int dissect_ladn_inf(dissector d, context* ctx);
int dissect_mico_ind(dissector d, context* ctx);
int dissect_rej_nssai(dissector d, context* ctx);
int dissect_full_name_network(dissector d, context* ctx);
int dissect_short_name_network(dissector d, context* ctx);
int dissect_local_time_zone(dissector d, context* ctx);
int dissect_configured_nssai(dissector d, context* ctx);
int dissect_op_def_acc_cat_def(dissector d, context* ctx);
int dissect_sms_ind(dissector d, context* ctx);

extern const element_meta conf_upd_ind = {
    0xD0,
    "Configuration update indication",
    dissect_conf_upd_ind,
};

extern const element_meta guti = {
    0x77,
    "5GS mobile identity - 5G-GUTI",
    dissect_guti,
};



extern const element_meta service_area_list = {
    0x70,
    "Service area list",
    dissect_sal,
};

extern const element_meta full_name_network = {
    0x43,
    "Full name for network",
    dissect_full_name_network,
};

extern const element_meta short_name_network = {
    0x45,
    "Short name for network",
    dissect_short_name_network,
};

extern const element_meta local_time_zone = {
    0x46,
    "Local time zone",
    dissect_local_time_zone,
};

extern const element_meta u_time_zone_time = {
    0x47,
    "Universal time and local time zone",
    dissect_time_zone_time,
};

extern const element_meta day_saving_time = {
    0x49,
    "Network daylight saving time",
    dissect_day_saving_time,
};

extern const element_meta ladn_inf = {
    0x79,
    "LADN information",
    dissect_ladn_inf,
};

extern const element_meta mico_ind = {
    0xB0,
    "MICO indication",
    dissect_mico_ind,
};

extern const element_meta configured_nssai = {
    0x31,
    "Configured NSSAI",
    dissect_configured_nssai,
};

extern const element_meta rej_nssai = {
    0x11,
    "Rejected NSSAI",
    dissect_rej_nssai,
};

extern const element_meta op_def_acc_cat_def = {
    0x76,
    "Operator-defined access category definitions",
    dissect_op_def_acc_cat_def,
};

extern const element_meta sms_ind = {
    0xF0,
    "SMS indication",
    dissect_sms_ind,
};

const field_meta hf_conf_upd_ind_red_b1 = {
    "Registration",
    "nas_5gs.mm.conf_upd_ind.red",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, 
    &tfs_requested_not_requested,
    nullptr,
    0x02,
};
const field_meta hf_conf_upd_ind_ack_b0 = {
    "Acknowledgement",
    "nas_5gs.mm.conf_upd_ind.ack",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_requested_not_requested,
    nullptr,
    0x01,
};
/*
 *   9.11.3.18    Configuration update indication
 */
int dissect_conf_upd_ind(dissector d, context* ctx) {
    static const field_meta* flags[] = {
        &hf_nas_5gs_spare_b3,
        &hf_nas_5gs_spare_b2,
        &hf_conf_upd_ind_red_b1,
        &hf_conf_upd_ind_ack_b0,
        nullptr,
    };
    d.add_bits(flags);

    return 1;
}

int dissect_guti(dissector d, context* ctx) { return 0; }



/*
 *     9.11.3.49    Service area list
 */
static true_false_string tfs_nas_5gs_sal_al_t = {
    "TAIs in the list are in the non-allowed area",
    "TAIs in the list are in the allowed area"};

static const value_string nas_5gs_mm_sal_t_li_values[] = {
    {0x00, "list of TACs belonging to one PLMN, with non-consecutive TAC values"},
    {0x01, "list of TACs belonging to one PLMN, with consecutive TAC values"},
    {0x02, "list of TAIs belonging to different PLMNs"},
    {0x03, "All TAIs belonging to the PLMN are in the allowed area"},
    {0, nullptr},
};

const field_meta hf_sal_al_t = {
    "Allowed type",
    "nas_5gs.mm.sal_al_t",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_sal_al_t,
    nullptr,
    0x80,
};
const field_meta hf_sal_t_li = {
    "Type of list",
    "nas_5gs.mm.sal_t_li",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_sal_t_li_values,
    nullptr,
    nullptr,
    0x60,
};
const field_meta hf_sal_num_e = {
    "Number of elements",
    "nas_5gs.mm.sal_num_e",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x1f,
};

int dissect_sal(dissector d, context* ctx) {
    auto len = d.length;
    static const field_meta* flags[] = {
        &hf_sal_al_t,
        &hf_sal_t_li,
        &hf_sal_num_e,
        nullptr,
    };
    auto num_par_sal = 1;
    /*Partial service area list*/
    while(d.length>0){
        auto start = d.offset;
        auto subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, "Partial service area list  %u", num_par_sal);
        d.tree = subtree;
        /*Head of Partial service area list*/
        /* Allowed type    Type of list    Number of elements    octet 1 */
        auto sal_head = d.tvb->get_uint8(d.offset);
        auto sal_t_li  = (sal_head & 0x60) >> 5;
        auto sal_num_e = (sal_head & 0x1f) + 1;
        d.add_bits(flags);
        d.step(1);
        switch (sal_t_li) {
        case 0: {
            /*octet 2  MCC digit2  MCC digit1*/
            /*octet 3  MNC digit3  MCC digit3*/
            /*octet 4  MNC digit2  MNC digit1*/
            dissect_e212_mcc_mnc(d, ctx);
            d.step(3);
            while(sal_num_e>0){
                d.add_item(3, &hf_tac, enc::be);
                d.step(3);
                --sal_num_e;
            }
        } break;
        case 1: {
            /*octet 2  MCC digit2  MCC digit1*/
            /*octet 3  MNC digit3  MCC digit3*/
            /*octet 4  MNC digit2  MNC digit1*/
            dissect_e212_mcc_mnc(d, ctx);
            d.step(3);

            /*octet 5  TAC 1*/
            d.add_item(3, &hf_tac, enc::be);
            d.step(3);
        } break;
        case 2: {
            while(sal_num_e>0){
                /*octet 2  MCC digit2  MCC digit1*/
                /*octet 3  MNC digit3  MCC digit3*/
                /*octet 4  MNC digit2  MNC digit1*/
                dissect_e212_mcc_mnc(d, ctx);
                d.step(3);

                /*octet 5  TAC 1*/
                d.add_item(3, &hf_tac, enc::be);
                d.step(3);
                --sal_num_e;
            }
        } break;
        case 3: {
            dissect_e212_mcc_mnc(d, ctx);
            d.step(3);
        } break;
        default:
            d.tree->add_expert(d.pinfo, d.tvb, d.offset, d.length, nullptr);
            break;
        }

        /*calculate the length of IE?*/
        d.tree->set_length(d.offset - start);        
        /*calculate the number of Partial service area list*/
        num_par_sal++;
    }
    return len;
}

int dissect_time_zone_time(dissector d, context* ctx) { return 0; }

int dissect_day_saving_time(dissector d, context* ctx) { return 0; }

int dissect_ladn_inf(dissector d, context* ctx) { return 0; }

int dissect_mico_ind(dissector d, context* ctx) { return 0; }

int dissect_rej_nssai(dissector d, context* ctx) { return 0; }


/*
 * [3] 10.5.3.5a Network Name
 */
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
     "defined in 3GPP TS 23.038"},
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
    fd::base_string,
    nullptr,nullptr,nullptr,
    0x0,
};

int dissect_full_name_network(dissector d, context* ctx) {
    auto len = d.length;
    auto oct = d.tvb->get_uint8(d.offset);
    d.add_item(1, &hf_a_extension, enc::be);
    auto code_scheme = (oct & 0x70) >> 4;
    d.add_item(1, &hf_coding_scheme, enc::be);
    d.add_item(1, &hf_add_ci, enc::be);

    auto num_spare_bits = oct & 0x07;
    auto item           = d.add_item(1, &hf_number_of_spare_bits, enc::be);
    d.step(1);
    if (len <= 1) return len;

    switch (code_scheme) {
    case 0: {
        /* Check if there was a reasonable value for number of spare bits in last octet */
        auto num_text_bits = (d.length << 3) - num_spare_bits;
        if (num_text_bits && (num_text_bits % 7)){
            // text string must be multiple of 7
            bug("num of text bits %d must be multiple of 7\n", num_text_bits);
        }
        auto item = d.add_item(d.length, &hf_text_string, enc::none);
        // 3GPP TS 23.038 7 bits        alphabet
        auto str = ts_23_038_7bits_string(d.safe_ptr(), 0, num_text_bits / 7);
        item->set_string(string(str.begin(), str.end()));
    } break;
    case 1: {
        d.add_item(d.length, &hf_text_string, enc::be);
    } break;
    default:
        // d.add_expert("invalid code scheme %d", code_scheme);
        bug("invalid code scheme %d\n", code_scheme);
    }
    return len;
}

int dissect_short_name_network(dissector d, context* ctx) { return 0; }

int dissect_local_time_zone(dissector d, context* ctx) { return 0; }

int dissect_configured_nssai(dissector d, context* ctx) { return 0; }

int dissect_op_def_acc_cat_def(dissector d, context* ctx) { return 0; }

int dissect_sms_ind(dissector d, context* ctx) { return 0; }

} // namespace mm_conf_upd_cmd
