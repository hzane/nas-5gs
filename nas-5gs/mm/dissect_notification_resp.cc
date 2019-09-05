#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/* 8.2.24 Notification response */
int mm::dissect_notification_resp(dissector d, context* ctx) {
    const use_context uc(ctx, "notification-response", d, 0);

    /* 50 PDU session status 9.11.3.44    O    TLV    4-34 */    
    const auto consumed = dissect_opt_elem_tlv(nullptr, &pdu_ses_status, d, ctx);
    d.step(consumed);
   
    return uc.length;
}
