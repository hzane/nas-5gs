#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.3.1 PDU session establishment request */
result_t de_pdu_session_establishment_request(dissector                            d,
                                              context*                             ctx,
                                              pdu_session_establishment_request_t* ret) {
    const use_context uc(&d, ctx, "pdu-session-establishment-request", 0);
    /* Direction: UE to network*/
    up_link(d.pinfo);

    de_nsm_header(d, ctx, &ret->header).step(d);
    /*
    Table 8.3.1.1.1: PDU SESSION ESTABLISHMENT REQUEST message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        PDU session ID	PDU session identity	9.4	M	V	1
        PTI	Procedure transaction identity	9.6	M	V	1
        PDU SESSION ESTABLISHMENT REQUEST message identity	Message type	9.7	M	V	1
    */
    //        Integrity protection maximum data rate	 9.11.4.7	M	V	2
    de_uint16(d, ctx, &ret->integrity_max_data_rate).step(d);

    // 9-	PDU session type	PDU session type	9.11.4.11	O	TV	1
    de_tv_short(d, ctx, 0x90, &ret->pdu_session_type).step(d);

    // A-	SSC mode	SSC mode	9.11.4.16	O	TV	1
    de_tv_short(d, ctx, 0xA0, &ret->ssc_mode);

    // 28	5GSM capability	5GSM capability	9.11.4.1	O	TLV	3-15
    de_tl_octet(d, ctx, 0x28, &ret->nsm_capabilities).step(d);

    // 55	Maximum number of supported packet filters	 9.11.4.9	O	TV	3
    de_t_uint16(d, ctx, 0x55, &ret->supported_packet_filters_max_n).step(d);

    // B-	Always-on PDU session requested	O	TV	1
    de_tv_short(d, ctx, 0xb0, &ret->always_on_pdu_session_requested).step(d);

    // 39	SM PDU DN request container	9.11.4.15	O	TLV	3-255
    de_tl_octet(d, ctx, 0x39, &ret->sm_pdu_dn_request_container).step(d);

    // 7B	Extended protocol configuration options 	9.11.4.6	O	TLV-E	4-65538
    de_tle_octet(d, ctx, 0x7b, &ret->extended_pco).step(d);
    return {uc.consumed()};
}