#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.3.7 PDU session modification request */
result_t de_pdu_session_modification_request(dissector                           d,
                                             context*                            ctx,
                                             pdu_session_modification_request_t* ret) {
    const use_context uc(&d, ctx, "pdu-session-modification-request", 0);
    /* Direction: UE to network */
    up_link(d.pinfo);
    de_nsm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.3.7.1.1: PDU SESSION MODIFICATION REQUEST message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        PDU session ID	PDU session identity	9.4	M	V	1
        PTI	Procedure transaction identity	9.6	M	V	1
        PDU SESSION MODIFICATION REQUEST message identity	Message type	9.7	M	V	1
    */
    // 28	5GSM capability	5GSM capability	9.11.4.1	O	TLV	3-15
    de_tl_octet(d, ctx, 0x28, &ret->nsm_capabilities).step(d);

    // 59	5GSM cause	5GSM cause	9.11.4.2	O	TV	2
    de_t_uint8(d, ctx, 0x59, &ret->nsm_cause).step(d);

    // 55	Maximum number of supported packet filters	9.11.4.9	O	TV	3
    de_t_uint16(d, ctx, 0x55, &ret->supported_packet_filters_max_n).step(d);

    // B-	Always-on PDU session requested	9.11.4.4	O	TV	1
    de_tv_short(d, ctx, 0xb0, &ret->always_on_pdu_session_requested).step(d);

    // 13	Integrity protection maximum data rate	9.11.4.7	O	TV	3
    de_t_uint16(d, ctx, 0x13, &ret->integrity_max_data_rate).step(d);

    // 7A	Requested QoS rules	QoS rules	9.11.4.13	O	TLV-E	7-65538
    de_tle_octet(d, ctx, 0x7a, &ret->requested_qos_rules).step(d);

    // 79	Requested QoS flow descriptions	9.11.4.12	O	TLV-E	6-65538
    de_tle_octet(d, ctx, 0x79, &ret->requested_qos_flow_desces).step(d);

    // 75	Mapped EPS bearer contexts	9.11.4.8	O	TLV-E	7-65538
    de_tle_octet(d, ctx, 0x75, &ret->mapped_eps_bearer_contexts).step(d);

    // 7B	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
    de_tle_octet(d, ctx, 0x7b, &ret->extended_pco).step(d);
    return {uc.consumed()};
}