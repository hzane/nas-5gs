#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.2.16 Service request page.317 */
result_t de_service_request(dissector d, context* ctx, service_request_t* ret) {
    const use_context uc(&d, ctx, "service-request", 0);
    // UE to network
    up_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.16.1.1: SERVICE REQUEST message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Service request message identity	Message type	9.7	M	V	1

    */
    // ngKSI 	NAS key set identifier	9.11.3.32	M	V	1/2
    de_nibble(d, ctx, &ret->nksi);

    // Service type	Service type	9.11.3.50	M	V	1/2
    de_nibble(d, ctx, &ret->type).step(d);

    // 5G-S-TMSI	5GS mobile identity	9.11.3.4	M	LV-E	9
    de_le_fixed(d, ctx, ret->tmsi_nmid).step(d);

    // 40	Uplink data status	Uplink data status	9.11.3.57	O	TLV	4-34
    de_tl_octet(d, ctx, 0x40, &ret->uplink_data_status).step(d);

    // 50	PDU session status	PDU session status	9.11.3.44	O	TLV	4-34
    de_tl_octet(d, ctx, 0x50, &ret->pdu_session_status).step(d);

    // 25	Allowed PDU session status	9.11.3.13	O	TLV	4-34
    de_tl_octet(d, ctx, 0x25, &ret->allowed_pdu_session_status).step(d);

    // 71	NAS message container	9.11.3.33	O	TLV-E	4-n
    de_tle_octet(d, ctx, 0x71, &ret->message).step(d);
    return {uc.consumed()};
}