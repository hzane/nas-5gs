#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* * 8.2.6 Registration request */
result_t de_registration_request(dissector d, context* ctx, registration_request_t* ret) {
    const use_context uc(&d, ctx, "registration-request", 0);
    // UE to network
    up_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.6.1.1: REGISTRATION REQUEST message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended Protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Registration request message identity	Message type	9.7	M	V	1

    */

    // 5GS registration type	5GS registration type	9.11.3.7	M	V	1/2
    de_nibble(d, ctx, &ret->nregistration_type);

    // ngKSI	NAS key set identifier	9.11.3.32	M	V	1/2
    de_nibble(d, ctx, &ret->nksi).step(d);

    // 5GS mobile identity	5GS mobile identity	9.11.3.4	M	LV-E	6-n
    de_le_octet(d, ctx, &ret->nmid).step(d);

    // C-	Non-current native NAS key set identifier	9.11.3.32 O	TV	1
    de_tv_short(d, ctx, 0xc0, &ret->native_nksi).step(d);

    // 10	5GMM capability	5GMM capability	9.11.3.1	O	TLV	3-15
    de_tl_octet(d, ctx, 0x10, &ret->nmm_capability).step(d);

    // 2E	UE security capability	UE security capability	9.11.3.54	O	TLV	4-10
    de_tl_octet(d, ctx, 0x2e, &ret->security_capability).step(d);

    // 2F	Requested NSSAI	NSSAI	9.11.3.37	O	TLV	4-74
    de_tl_octet(d, ctx, 0x2f, &ret->requested_nssai).step(d);

    // 52	Last visited registered TAI	9.11.3.8	O	TV	7
    de_t_fixed(d, ctx, 0x52, &ret->last_visited_tai).step(d);

    // 17	S1 UE network capability	9.11.3.48	O	TLV	4-15
    de_tl_octet(d, ctx, 0x17, &ret->s1_ue_network_capability).step(d);

    // 40	Uplink data status	9.11.3.57	O	TLV	4-34
    de_tl_octet(d, ctx, 0x40, &ret->uplink_data_status).step(d);

    // 50	PDU session status	9.11.3.44	O	TLV	4-34
    de_tl_octet(d, ctx, 0x50, &ret->pdu_session_status).step(d);

    // B-	MICO indication	9.11.3.31	O	TV	1
    de_tv_short(d, ctx, 0xb0, &ret->mico_ind).step(d);

    // 2B	UE status	UE status	9.11.3.56	O	TLV	3
    de_tl_uint8(d, ctx, 0x2b, &ret->ue_status).step(d);

    // 77	Additional GUTI	5GS mobile identity	9.11.3.4	O	TLV-E	14
    de_tle_fixed(d, ctx, 0x77, &ret->additional_guti_mid).step(d);

    // 25	Allowed PDU session status	9.11.3.13	O	TLV	4-34
    de_tl_octet(d, ctx, 0x25, &ret->allowed_pdu_session_status).step(d);

    // 18	UE's usage setting	9.11.3.55	O	TLV	3
    de_tl_uint8(d, ctx, 0x18, &ret->ue_usage_setting).step(d);

    // 51	Requested DRX parameters	9.11.3.2A	O	TLV	3
    de_tl_uint8(d, ctx, 0x51, &ret->requested_drx_parameters).step(d);

    // 70	EPS NAS message container	9.11.3.24	O	TLV-E	4-n
    de_tle_octet(d, ctx, 0x70, &ret->eps_nas_container).step(d);

    // 74	LADN indication	LADN indication	9.11.3.29	O	TLV-E	3-811
    de_tle_octet(d, ctx, 0x74, &ret->ladn_ind).step(d);

    // 8-	Payload container type	9.11.3.40	O	TV	1
    de_tv_short(d, ctx, 0x80, &ret->payload_container_type).step(d);

    // 7B	Payload container	9.11.3.39	O	TLV-E	4-65538
    de_tle_octet(d, ctx, 0x7b, &ret->payload_container).step(d);

    // 9-	Network slicing indication	9.11.3.36	O	TV	1
    de_tv_short(d, ctx, 0x90, &ret->network_slicing_ind).step(d);

    // 53	5GS update type	9.11.3.9A	O	TLV	3
    de_tl_uint8(d, ctx, 0x53, &ret->nupdate_type).step(d);

    // TBD	Mobile station classmark 2	9.11.3.61	O	TLV	5
    // TBD	Supported codecs	9.11.3.62	O	TLV	5-n

    // 71	NAS message container	9.11.3.33	O	TLV-E	4-n
    de_tle_octet(d, ctx, 0x71, &ret->nas_message_container).step(d);

    // 60	EPS bearer context status	9.11.3.60	O	TLV	4
    de_tl_uint16(d, ctx, 0x60, &ret->eps_bearer_context_status).step(d);

    // XX	Requested extended DRX parameters	9.11.3.60	O	TLV	3

    // TBD	T3324 value	GPRS timer 3	9.11.2.5	O	TLV	3
    return {d.offset - uc.offset};
}