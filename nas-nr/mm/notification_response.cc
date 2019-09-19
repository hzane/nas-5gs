#include "../dissect_mm_msg.hh"
#include "../ber.hh"

/* 8.2.24 Notification response */
int mm::dissect_notification_resp(dissector d, context* ctx) {
    const use_context uc(ctx, "notification-response", d, 0);
    // UE to network
    up_link(d.pinfo);

    /* 50 PDU session status 9.11.3.44    O    TLV    4-34 */
    const auto consumed = dissect_opt_tlv(nullptr, &pdu_session_status, d, ctx);
    d.step(consumed);

    return uc.length;
}

struct pdu_session_status_t{

};
struct notification_response_t {
    optional< pdu_session_status_t > pdu_session_status;
};
