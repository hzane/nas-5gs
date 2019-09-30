#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"


using namespace mm;
using namespace nas;

/* 8.2.19 Configuration update command */
int mm::dissect_configuration_update_command(dissector d, context* ctx) {
    use_context uc(ctx, "configuration-update-command", d, 3);
    // network to UE
    down_link(d.packet);

    /*D-    Configuration update indication 9.11.3.18 O    TV    1 */
    auto consumed = dissect_opt_tv_short( &configure_update_indication, d, ctx);
    d.step(consumed);

    /*77    5G-GUTI    5GS mobile identity     9.11.3.4    O    TLV    TBD*/
    consumed = dissect_opt_tlv_e( &guti_mobile_id, d, ctx);
    d.step(consumed);

    /*54    TAI list    Tracking area identity list     9.11.3.9    O    TLV    8-98*/
    consumed = dissect_opt_tlv( &tracking_area_id_list, d, ctx);
    d.step(consumed);

    /*15    Allowed NSSAI    NSSAI     9.11.3.37    O    TLV    4-74*/
    // ELEM_OPT_TLV(0x15, , DE_NAS_5GS_MM_NSSAI, " - Allowed NSSAI");
    consumed = dissect_opt_tlv( &allowed_nssai, d, ctx);
    d.step(consumed);

    /*27    Service area list    9.11.3.49    O    TLV    6-114 */
    consumed = dissect_opt_tlv( &service_area_list, d, ctx);
    d.step(consumed);

    /*43  Full name for network   Network name    9.11.3.35   O   TLV    3-n*/
    // ELEM_OPT_TLV(0x43, , DE_NETWORK_NAME, " - Full name for network");
    consumed = dissect_opt_tlv( &full_name_network, d, ctx);
    d.step(consumed);

    /*45    Short name for network    Network name     9.11.3.35    O    TLV    3-n*/
    // ELEM_OPT_TLV(0x45, , DE_NETWORK_NAME, " - Short Name");
    consumed = dissect_opt_tlv( &short_name_network, d, ctx);
    d.step(consumed);

    /*46    Local time zone    Time zone     9.11.3.52    O    TV    2*/
    // ELEM_OPT_TV(0x46, , DE_TIME_ZONE, " - Local");
    consumed = dissect_opt_tv( &local_timezone, d, ctx);
    d.step(consumed);

    /*47  Universal time and local time zone  Time zone and time  9.11.3.53  O TV  8*/
    /*ELEM_OPT_TV(0x47,,DE_TIME_ZONE_TIME," - Universal Time and Local Time Zone");*/
    consumed = dissect_opt_tv( &timezone_time, d, ctx);
    d.step(consumed);

    /*49 Network daylight saving time Daylight saving time 9.11.3.19 O TLV 3*/
    consumed = dissect_opt_tlv( &daylight_saving_time, d, ctx);
    d.step(consumed);

    /*79    LADN information 9.11.3.30    O    TLV-E    11-1579*/
    consumed = dissect_opt_tlv_e( &ladn_information, d, ctx);
    d.step(consumed);

    /*B-    MICO indication  9.11.3.31    O    TV    1*/
    consumed = dissect_opt_tv_short( &mico_indication, d, ctx);
    d.step(consumed);

    // 9-	Network slicing indication	 9.11.3.36 O TV 1
    // ELEM_OPT_TV_SHORT(0x90, , DE_NAS_5GS_MM_network_slicing_indication, NULL);
    consumed = dissect_opt_tv_short( &network_slicing_indication, d, ctx);
    d.step(consumed);

    /*31    Configured NSSAI    NSSAI     9.11.3.37    O    TLV    4-74*/
    // ELEM_OPT_TLV(0x31, , DE_NAS_5GS_MM_NSSAI, " - Configured NSSAI");
    consumed = dissect_opt_tlv( &configured_nssai, d, ctx);
    d.step(consumed);

    /*11    Rejected NSSAI   9.11.3.46   O   TLV   4-42*/
    // ELEM_OPT_TLV(0x11, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_REJ_NSSAI, NULL);
    consumed = dissect_opt_tlv( &rejected_nssai, d, ctx);
    d.step(consumed);

    /* 76 Operator-defined access category definitions   9.11.3.38   O   TLV-E  3-n */
    // ELEM_OPT_TLV_E(0x76, , DE_NAS_5GS_MM_OP_DEF_ACC_CAT_DEF, NULL);
    consumed = dissect_opt_tlv_e( &operator_defined_access_category_defs, d, ctx);
    d.step(consumed);

    /* F-    SMS indication    SMS indication 9.10.3.50A    O    TV    1 */
    // ELEM_OPT_TV_SHORT(0xF0, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_SMS_IND, NULL);
    consumed = dissect_opt_tv_short( &sms_indication, d, ctx);
    d.step(consumed);

    // Tbd	T3447 value	GPRS timer 3    9.11.2.5 O TLV 3

    return uc.length;
}

static const char* req = "Requested";
static const char* nreq = "Not requested";





const tag_field hf_number_of_spare_bits = {
    "Number of spare bits in last octet",
    0x07,
    (const v_string[]){
        {0, "this field carries no information about the number of spare bits in octet n"},
        {1, "bit 8 is spare and set to '0' in octet n"},
        {2, "bits 7 and 8 are spare and set to '0' in octet n"},
        {3, "bits 6 to 8(inclusive) are spare and set to '0' in octet n"},
        {4, "bits 5 to 8(inclusive) are spare and set to '0' in octet n"},
        {5, "bits 4 to 8(inclusive) are spare and set to '0' in octet n"},
        {6, "bits 3 to 8(inclusive) are spare and set to '0' in octet n"},
        {7, "bits 2 to 8(inclusive) are spare and set to '0' in octet n"},
        {0, nullptr},
    },
};

