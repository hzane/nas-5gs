#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.2.24 Notification response */
result_t de_notification_response(dissector                d,
                                  context*                 ctx,
                                  notification_response_t* ret) {
    const use_context uc(&d, ctx, "notification-response", 0);
    // UE to network
    up_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.2341.1: NOTIFICATION RESPONSE message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Notification response message identity	Message type	9.7	M	V	1
    */
    // 50	PDU session status	PDU session status	9.11.3.44	O	TLV	4-34
    de_tl_octet(d, ctx, 0x50, &ret->pdu_session_status).step(d);
    return {uc.consumed()};
}