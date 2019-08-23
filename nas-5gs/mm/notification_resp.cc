#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/*
 * 8.2.24 Notification response
 */
int mm::notification_resp(dissector d, context* ctx) {
    use_context uc(ctx, "notification-response");

    /* 50    PDU session status    PDU session status 9.11.3.40    O    TLV    4-34 */
    // ELEM_OPT_TLV(0x50, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    auto consumed = dissect_opt_elem_tlv(nullptr, &pdu_ses_status, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}
