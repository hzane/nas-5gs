#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_service_req {
extern const field_meta*  hf_service_type;
extern const element_meta key_set_id;
extern const element_meta s_tmsi;
extern const element_meta uplink_data_status;
extern const element_meta allowed_pdu_ses_status;
} // namespace mm_service_req

/*
 * 8.2.16 Service request
 */
int mm::service_req(dissector d, context* ctx) {
    use_context uc(ctx, "service-request");

    using namespace mm_service_req;

    /* Service type    Service type 9.11.3.46    M    V    1/2 */
    // proto_tree_add_item(
    //    tree, hf_nas_5gs_mm_serv_type, tvb, curr_offset, 1, ENC_BIG_ENDIAN);
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_service_type, enc::be);

    /*  ELEM_MAND_V(,DE_NAS_5GS_MM_NAS_KEY_SET_ID," - ngKSI", );*/
    /* ngKSI     NAS key set identifier 9.11.3.29    M    V    1/2 */
    auto consumed = dissect_elem_v(nullptr, &key_set_id, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* 5G-S-TMSI    5GS mobile identity 9.11.3.4    M    LV    6 */
    /*ELEM_MAND_LV_E(,DE_NAS_5GS_MM_5GS_MOBILE_ID, );*/
    consumed = dissect_elem_lv_e(nullptr, &s_tmsi, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*40    Uplink data status    Uplink data status         9.11.3.53    O    TLV    4 -
     * 34*/
    // ELEM_OPT_TLV(0x40, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_UL_DATA_STATUS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &uplink_data_status, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*50    PDU session status    PDU session status         9.11.3.40    O    TLV    4 -
     * 34*/
    // ELEM_OPT_TLV(0x50, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &pdu_ses_status, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*25    Allowed PDU session status    Allowed PDU session status         9.11.3.11
     * O    TLV    4 - 34*/
    // ELEM_OPT_TLV(0x25, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_ALLOW_PDU_SES_STS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &allowed_pdu_ses_status, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* 71    NAS message container    NAS message container 9.11.3.33    O    TLV-E    4-n
     */
    // ELEM_OPT_TLV_E(0x71, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NAS_MSG_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &nas_msg_cont, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    // EXTRANEOUS_DATA_CHECK(curr_len, 0, pinfo, &ei_nas_5gs_extraneous_data);
    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);

    return d.tvb->reported_length;
}
namespace mm_service_req {
/*
 *     9.11.3.50    Service type
 */

/* Used inline as H1 (Upper nibble)*/
const val_string nas_5gs_mm_serv_type_vals[] = {
    {0x00, "Signalling"},
    {0x01, "Data"},
    {0x02, "Mobile terminated services"},
    {0x03, "Emergency services"},
    {0x04, "Emergency services fallback"},
    {0x05, "High priority access"},
    {0, nullptr},
};

extern const field_meta hfm_service_type = {
    "Service type",
    "nas_5gs.mm.serv_type",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_serv_type_vals,
    nullptr,
    nullptr,
    0x70,
};
const field_meta* hf_service_type = &hfm_service_type;

int                dissect_key_set_id(dissector d, context* ctx);
const element_meta key_set_id = {
    0xff,
    "NAS key set identifier - ngKSI",
    dissect_key_set_id,
};

int                dissect_s_tmsi(dissector d, context* ctx);
const element_meta s_tmsi = {
    0xff,
    "5G-S-TMSI",
    dissect_s_tmsi,
};

int                dissect_uplink_data_status(dissector d, context* ctx);
const element_meta uplink_data_status = {
    0x40,
    "Uplink data status",
    dissect_uplink_data_status,
};

int                dissect_allowed_pdu_ses_status(dissector d, context* ctx);
const element_meta allowed_pdu_ses_status = {
    0x25,
    "Allowed PDU session status",
    dissect_allowed_pdu_ses_status,
};

int dissect_key_set_id(dissector d, context* ctx) { return 0; }

int dissect_s_tmsi(dissector d, context* ctx) { return 0; }

int dissect_uplink_data_status(dissector d, context* ctx) { return 0; }

int dissect_allowed_pdu_ses_status(dissector d, context* ctx) { return 0; }

} // namespace mm_service_req
