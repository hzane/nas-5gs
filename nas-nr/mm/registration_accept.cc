#include "../common/core.hh"
#include "../common/dissector.hh"
#include "../common/use_context.hh"
#include "../common/messages.hh"

/* 8.2.7    Registration accept */

result_t de_registration_accept(dissector d, context* ctx, registration_accept_t* ret) {
    const use_context uc(&d, ctx, "registration-accept", 0);

    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.7.1.1: REGISTRATION ACCEPT message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Registration accept message identity	Message type	9.7	M	V	1
    */
    // 5GS registration result	5GS registration result	9.11.3.6	M	LV	2
    d.step(1);
    de_uint8(d, ctx, &ret->nr_registration_result).step(d);

    // 77	5G-GUTI	5GS mobile identity	9.11.3.4	O	TLV-E	14
    de_tle_fixed(d, ctx, 0x77, &ret->guti_nr_mid).step(d);

    // 4A	Equivalent PLMNs	PLMN list	9.11.3.45	O	TLV	5-47
    de_tl_octet(d, ctx, 0x4a, &ret->equivalent_plmns).step(d);

    // 54	TAI list	5GS tracking area identity list	9.11.3.9	O	TLV	9-114
    de_tl_octet(d, ctx, 0x54, &ret->tai_list).step(d);

    // 15	Allowed NSSAI	NSSAI	9.11.3.37	O	TLV	4-74
    de_tl_octet(d, ctx, 0x15, &ret->allowed_nssai).step(d);

    // 11	Rejected NSSAI	Rejected NSSAI	9.11.3.46	O	TLV	4-42
    de_tl_octet(d, ctx, 0x11, &ret->rejected_nssai).step(d);

    // 31	Configured NSSAI	NSSAI	9.11.3.37	O	TLV	4-146
    de_tl_octet(d, ctx, 0x31, &ret->configured_nssai).step(d);

    // 21	5GS network feature support	9.11.3.5	O	TLV	3-5
    de_tl_octet(d, ctx, 0x21, &ret->nr_network_feature_support).step(d);

    // 50	PDU session status	PDU session status	9.11.3.44	O	TLV	4-34
    de_tl_octet(d, ctx, 0x50, &ret->pdu_session_status).step(d);

    // 26	PDU session reactivation result	9.11.3.42	O TLV 4-34
    de_tl_octet(d, ctx, 0x26, &ret->pdu_session_reactivation_result).step(d);

    // 72	PDU session reactivation result error cause	9.11.3.43	O	TLV-E	5-515
    de_tle_octet(d, ctx, 0x72, &ret->pdu_session_reactivation_result_error_cause).step(d);

    // 79	LADN information	LADN information	9.11.3.30	O	TLV-E	12-1715
    de_tle_octet(d, ctx, 0x79, &ret->ladn_information).step(d);

    // B-	MICO indication	MICO indication	9.11.3.31	O	TV	1
    de_tv_short(d, ctx, 0xb0, &ret->mico_ind).step(d);

    // 9-	Network slicing indication	9.11.3.36	O	TV	1
    de_tv_short(d, ctx, 0x90, &ret->network_slicing_ind).step(d);

    // 27	Service area list	Service area list	9.11.3.49	O	TLV	6-114
    de_tl_octet(d, ctx, 0x27, &ret->service_area_list).step(d);

    // 5E	T3512 value	GPRS timer 3	9.11.2.5	O	TLV	3
    de_tl_uint8(d, ctx, 0x5e, &ret->t3512).step(d);

    // 5D	Non-3GPP de-registration GPRS timer 2	9.11.2.4	O	TLV	3
    de_tl_uint8(d, ctx, 0x5d, &ret->n3_deregistration_timer).step(d);

    // 16	T3502 value	GPRS timer 2	9.11.2.4	O	TLV	3
    de_tl_uint8(d, ctx, 0x16, &ret->t3502).step(d);

    // 34	Emergency number list	9.11.3.23	O	TLV	5-50
    de_tl_octet(d, ctx, 0x34, &ret->emergency_numbers).step(d);

    // 7A	Extended emergency number list	9.11.3.26	O TLV-E 7-65538
    de_tl_octet(d, ctx, 0x7a, &ret->extended_emergency_numbers).step(d);

    // 73	SOR transparent container 9.11.3.51	O TLV-E 20-n
    de_tle_octet(d, ctx, 0x73, &ret->sor_container).step(d);

    // 78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
    de_tle_octet(d, ctx, 0x78, &ret->eap).step(d);

    // A-	NSSAI inclusion mode	9.11.3.37A	O	TV	1
    de_tv_short(d, ctx, 0xa0, &ret->nssai_inclusion_mode).step(d);

    // 76	Operator-defined access category definitions	9.11.3.38	O	TLV-E	3-n
    de_tle_octet(d, ctx, 0x76, &ret->access_categories).step(d);

    // 51  5GS DRX parameters	9.11.3.2A	O	TLV	3
    de_tl_uint8(d, ctx, 0x51, &ret->negotiated_drx_parameters).step(d);

    // D-	Non-3GPP NW provided policies	9.11.3.58	O	TV	1
    de_tv_short(d, ctx, 0xd0, &ret->n3_nw_provided_policies).step(d);

    // 60	EPS bearer context status	9.11.3.59	O	TLV	4
    de_tl_uint16(d, ctx, 0x60, &ret->eps_bearer_context_status).step(d);

    // xx	Extended DRX parameters	9.11.3.60	O	TLV	3
    // tbd	T3447 value	GPRS timer 3	9.11.2.5	O	TLV	3
    // XX	T3448 value	GPRS timer 3	9.11.2.4	O	TLV	3
    // TBD T3324 value	GPRS timer 3	9.11.2.5	O	TLV	3
    /**/

    return {d.offset - uc.offset};
}