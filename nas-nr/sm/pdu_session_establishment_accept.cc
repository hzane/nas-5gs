#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.3.2 PDU session establishment accept */
result_t de_pdu_session_establishment_accept(dissector                           d,
                                             context*                            ctx,
                                             pdu_session_establishment_accept_t* ret) {
    const use_context uc(&d, ctx, "pdu-session-establishment-accept", 0);
    /* Direction: network to UE */
    down_link(d.pinfo);

    de_nsm_header(d, ctx,&ret->header).step(d);

    /*
    Table 8.3.2.1.1: PDU SESSION ESTABLISHMENT ACCEPT message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        PDU session ID	PDU session identity	9.4	M	V	1
        PTI	Procedure transaction identity	9.6	M	V	1
        PDU SESSION ESTABLISHMENT ACCEPT message identity	Message type	9.7	M	V	1
    */
    // Selected PDU session type	PDU session type	9.11.4.11	M	V	1/2
    de_nibble(d, ctx, &ret->selected_pdu_session_type);

    // Selected SSC mode	SSC mode	9.11.4.16	M	V	1/2
    de_nibble(d, ctx, &ret->selected_ssc_mode).step(d);

    // Authorized QoS rules	QoS rules	9.11.4.13	M	LV-E	6-65538
    de_le_octet(d, ctx, &ret->authorized_qos_rules).step(d);

    // Session AMBR	Session-AMBR	9.11.4.14	M	LV	7
    de_l_fixed(d, ctx, ret->session_ambr).step(d);

    // 59	5GSM cause	5GSM cause	9.11.4.2	O	TV	2
    de_t_uint8(d, ctx, 0x59, &ret->cause).step(d);

    // 29	PDU address	PDU address	9.11.4.10	O	TLV	7, 11 or 15
    de_tl_octet(d, ctx, 0x29, &ret->pdu_address).step(d);

    // 56	RQ timer value	GPRS timer	9.11.2.3	O	TV	2
    de_t_uint8(d, ctx, 0x56, &ret->rq_timer).step(d);

    // 22	S-NSSAI	S-NSSAI	9.11.2.8	O	TLV	3-10
    de_tl_octet(d, ctx, 0x22, &ret->s_nssai).step(d);

    // 8-	Always-on PDU session indication	9.11.4.3 O TV 1
    de_tv_short(d, ctx, 0x80, &ret->always_on_pdu_session_ind).step(d);

    // 75	Mapped EPS bearer contexts	9.11.4.8	O	TLV-E 7-65538
    de_tle_octet(d, ctx, 0x75, &ret->mapped_eps_bearer_contexts).step(d);

    // 78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
    de_tle_octet(d, ctx, 0x78, &ret->eap).step(d);

    // 79	Authorized QoS flow descriptions	9.11.4.12	O	TLV-E 6-65538
    de_tle_octet(d, ctx, 0x79, &ret->authorized_qos_flow_descs).step(d);

    // 7B	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
    de_tle_octet(d, ctx, 0x7b, &ret->extended_pco).step(d);

    // 25	DNN	DNN	9.11.2.1A	O	TLV	3-102
    de_tl_octet(d, ctx, 0x25, &ret->dnn).step(d);

    // xx	5GSM network feature support	9.11.4.18	O	TLV	3-15
    // xx Session-TMBR	Session-TMBR	9.11.4.19	O	TLV	8
    // TBD	Serving PLMN rate control Serving PLMN rate control	9.11.4.20	O	TLV	4
    // XX	ATSSS container	ATSSS container	9.11.4.22	O	TLV-E	3-65538
    // XX	Control plane only indication	9.11.4.23	O	TV	1
    return {uc.consumed()};
}