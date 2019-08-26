#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_conf_upd_cmd {
extern const element_meta conf_upd_ind;
extern const element_meta guti;
extern const element_meta ta_id_list;
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
    // ELEM_OPT_TLV(0x43, GSM_A_PDU_TYPE_DTAP, DE_NETWORK_NAME, " - Full name for
    // network");
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
int dissect_ta_id_list(dissector d, context* ctx);
int dissect_allowed_nssai(dissector d, context* ctx);
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
    "5G-GUTI",
    dissect_guti,
};

extern const element_meta ta_id_list = {
    0x54,
    "TAI list",
    dissect_ta_id_list,
};

extern const element_meta allowed_nssai = {
    0x15,
    "Allowed NSSAI",
    dissect_allowed_nssai,
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

int dissect_ta_id_list(dissector d, context* ctx) { return 0; }

int dissect_allowed_nssai(dissector d, context* ctx) { return 0; }

int dissect_sal(dissector d, context* ctx) { return 0; }

int dissect_time_zone_time(dissector d, context* ctx) { return 0; }

int dissect_day_saving_time(dissector d, context* ctx) { return 0; }

int dissect_ladn_inf(dissector d, context* ctx) { return 0; }

int dissect_mico_ind(dissector d, context* ctx) { return 0; }

int dissect_rej_nssai(dissector d, context* ctx) { return 0; }

int dissect_full_name_network(dissector d, context* ctx) { return 0; }

int dissect_short_name_network(dissector d, context* ctx) { return 0; }

int dissect_local_time_zone(dissector d, context* ctx) { return 0; }

int dissect_configured_nssai(dissector d, context* ctx) { return 0; }

int dissect_op_def_acc_cat_def(dissector d, context* ctx) { return 0; }

int dissect_sms_ind(dissector d, context* ctx) { return 0; }

} // namespace mm_conf_upd_cmd
