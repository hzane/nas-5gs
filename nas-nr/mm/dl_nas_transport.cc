#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/*  8.2.11 DL NAS transport */
result_t de_dl_nas_transport(dissector d, context* ctx, dl_nas_transport_t* ret) {
    const use_context uc(&d, ctx, "dl-nas-transport", 0);
    // network to UE
    down_link(d.pinfo);
    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.11.1.1: DL NAS TRANSPORT message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        DL NAS TRANSPORT message identity	Message type	9.7	M	V	1
    */
    // Payload container type	Payload container type	9.11.3.40	M	V	1/2
    de_nibble(d, ctx, &ret->payload_container_type).step(d);

    // Spare half octet	Spare half octet	9.5	M	V	1/2

    // Payload container	Payload container	9.11.3.39	M	LV-E	3-65537
    de_le_octet(d, ctx, &ret->payload_container).step(d);

    // 12	PDU session ID	PDU session identity 2	9.11.3.41	C	TV	2
    de_t_uint8(d, ctx, 0x12, &ret->pdu_session_id).step(d);

    // 24	Additional information	Additional information	9.11.2.1	O	TLV	3-n
    de_tl_octet(d, ctx, 0x24, &ret->additional_information).step(d);

    // 58	5GMM cause	5GMM cause	9.11.3.2	O	TV	2
    de_t_uint8(d, ctx, 0x58, &ret->cause).step(d);

    // 37	Back-off timer value	GPRS timer 3	9.11.2.5	O	TLV	3
    de_tl_uint8(d, ctx, 0x37, &ret->backoff_timer).step(d);
    return {uc.consumed()};
}