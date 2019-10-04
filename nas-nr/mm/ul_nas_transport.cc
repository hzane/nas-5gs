#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.2.10    UL NAS transport */
result_t de_ul_nas_transport(dissector d, context* ctx, ul_nas_transport_t* ret) {
    const use_context uc(&d, ctx, "ul-nas-transport", 0);
    /* Direction: UE to network */
    up_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.10.1.1: UL NAS TRANSPORT message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        UL NAS TRANSPORT message identity	Message type	9.7	M	V	1

    */
    // Payload container type	Payload container type	9.11.3.40	M	V	1/2
    de_nibble(d, ctx, &ret->payload_container_type).step(d);
    // Spare half octet Spare half octet 9.5 M V 1 / 2

    // Payload container	Payload container	9.11.3.39	M	LV-E	3-65537
    de_le_octet(d, ctx, &ret->payload_container).step(d);

    // 12	PDU session ID	PDU session identity 2	9.11.3.41	C	TV	2
    de_t_uint8(d, ctx, 0x12, &ret->pdu_session_id).step(d);

    // 59	Old PDU session ID	PDU session identity 2	9.11.3.41	O	TV	2
    de_t_uint8(d, ctx, 0x59, &ret->old_pdu_session_id).step(d);

    // 8	Request type	Request type	9.11.3.47	O	TV	1
    de_tv_short(d, ctx, 0x80, &ret->request_type).step(d);

    // 22	S-NSSAI	S-NSSAI	9.11.2.8	O	TLV	3-10
    de_tl_octet(d, ctx, 0x22, &ret->s_nssai).step(d);

    // 25	DNN	DNN	9.11.2.1A	O	TLV	3-102
    de_tl_octet(d, ctx, 0x25, &ret->dnn).step(d);

    // 24	Additional information	Additional information	9.11.2.1	O	TLV	3-n
    de_tl_octet(d, ctx, 0x24, &ret->additional_information).step(d);

    // Z	MA PDU session information	MA PDU session information	O	TV	1
    return {uc.consumed()};
}