#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

/* 8.2.24 Notification response */
int mm::dissect_notification_response(dissector d, context* ctx) {
    const use_context uc(ctx, "notification-response", d, 0);
    // UE to network
    up_link(d.packet);

    /* 50 PDU session status 9.11.3.44    O    TLV    4-34 */
    const auto consumed = dissect_opt_tlv(nullptr, &pdu_session_status, d, ctx);
    d.step(consumed);

    return uc.length;
}

