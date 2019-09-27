#pragma once
#include <cstdint>
#include "common/nas.hh"
#include "common/definitions.hh"
#include "ies.hh"

using bit4_t = uint8_t;
using octet_16 = uint8_t[16];

/*
Table 8.2.1.1.1: AUTHENTICATION REQUEST message content
IEI	Information Element	Type/Reference	Presence	Format	Length
	Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
	Security header type	Security header type	9.3	M	V	1/2
	Spare half octet	Spare half octet	9.5	M	V	1/2
	Authentication request message identity	Message type	9.7	M	V	1
	ngKSI 	NAS key set identifier	9.11.3.32	M	V	1/2
	Spare half octet	Spare half octet	9.5	M	V	1/2
	ABBA	ABBA	9.11.3.10	M	LV	3-n
21	Authentication parameter RAND (5G authentication challenge)	Authentication parameter RAND	9.11.3.16	O	TV	17
20	Authentication parameter AUTN (5G authentication challenge)	Authentication parameter AUTN	9.11.3.15	O	TLV	18
78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
*/
struct authenticaion_request_t {
    nmm_header_t      header = {};
    bit4_t            nksi;
    octet_t           abba;
    opt_t< octet_16 > rand;
    opt_t< octet_16 > autn;
    opt_t< octet_t >  eap;
};
/*
Table 8.2.2.1.1: AUTHENTICATION RESPONSE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Authentication response message identity	Message type	9.7	M	V	1
2D	Authentication response parameter	Authentication response parameter	9.11.3.17 O TLV	18
78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
*/
struct authentication_response_t{
    nmm_header_t     header    = {};
    octet_16         parameter = {};
    opt_t< octet_t > eap       = {};
};

/*
Table 8.2.3.1.1: AUTHENTICATION RESULT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Authentication result message identity	Message type	9.7	M	V	1
    ngKSI 	NAS key set identifier	9.11.3.32	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    EAP message	EAP message	9.11.2.2	M	LV-E	6-1502
38	ABBA	ABBA	9.11.3.10	O	TLV	4-n
*/
struct authentication_result_t {
    nmm_header_t     header = {};
    bit4_t           nksi;
    octet_t          eap;
    opt_t< octet_t > abba;
};

using octet_14 = uint8_t[14];

/*
Table 8.2.4.1.1: AUTHENTICATION FAILURE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Authentication failure message identity	Message type	9.7	M	V	1
    5GMM cause	5GMM cause	9.11.3.2	M	V	1
30	Authentication failure parameter	Authentication failure parameter	9.11.3.14 O TLV	16
*/
struct authentication_failure_t {
    nmm_header_t header = {};
    uint8_t      cause;
    opt_t< octet_14 > parameter;// octet_16?
};

/*
Table 8.2.5.1.1: AUTHENTICATION REJECT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Authentication reject message identity	Message type	9.7	M	V	1
78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
*/
struct authentication_reject_t {
    nmm_header_t     header;
    opt_t< octet_t > eap;
};

using octet_6 = uint8_t[6];
using octet_b = uint8_t[11];

/*
Table 8.2.6.1.1: REGISTRATION REQUEST message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended Protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Registration request message identity	Message type	9.7	M	V	1
    5GS registration type	5GS registration type	9.11.3.7	M	V	1/2
    ngKSI	NAS key set identifier	9.11.3.32	M	V	1/2
    5GS mobile identity	5GS mobile identity	9.11.3.4	M	LV-E	6-n
C-	Non-current native NAS key set identifier	NAS key set identifier	9.11.3.32 O	TV	1
10	5GMM capability	5GMM capability	9.11.3.1	O	TLV	3-15
2E	UE security capability	UE security capability	9.11.3.54	O	TLV	4-10
2F	Requested NSSAI	NSSAI	9.11.3.37	O	TLV	4-74
52	Last visited registered TAI	5GS tracking area identity	9.11.3.8	O	TV	7
17	S1 UE network capability	S1 UE network capability	9.11.3.48	O	TLV	4-15
40	Uplink data status	Uplink data status	9.11.3.57	O	TLV	4-34
50	PDU session status	PDU session status	9.11.3.44	O	TLV	4-34
B-	MICO indication	MICO indication	9.11.3.31	O	TV	1
2B	UE status	UE status	9.11.3.56	O	TLV	3
77	Additional GUTI	5GS mobile identity	9.11.3.4	O	TLV-E	14
25	Allowed PDU session status	Allowed PDU session status	9.11.3.13	O	TLV	4-34
18	UE's usage setting	UE's usage setting	9.11.3.55	O	TLV	3
51	Requested DRX parameters	5GS DRX parameters	9.11.3.2A	O	TLV	3
70	EPS NAS message container	EPS NAS message container	9.11.3.24	O	TLV-E	4-n
74	LADN indication	LADN indication	9.11.3.29	O	TLV-E	3-811
8-	Payload container type	Payload container type	9.11.3.40	O	TV	1
7B	Payload container	Payload container	9.11.3.39	O	TLV-E	4-65538
9-	Network slicing indication	Network slicing indication	9.11.3.36	O	TV	1
53	5GS update type	5GS update type	9.11.3.9A	O	TLV	3
TBD	Mobile station classmark 2	Mobile station classmark 2	9.11.3.61	O	TLV	5
TBD	Supported codecs	Supported codec list	9.11.3.62	O	TLV	5-n
71	NAS message container	NAS message container	9.11.3.33	O	TLV-E	4-n
60	EPS bearer context status	EPS bearer context status	9.11.3.60	O	TLV	4
XX	Requested extended DRX parameters	Extended DRX parameters	9.11.3.60	O	TLV	3
TBD	T3324 value	GPRS timer 3	9.11.2.5	O	TLV	3
*/
struct registration_request_t {
    nmm_header_t header = {};
    bit4_t     nregistration_type = {};
    bit4_t     nksi = {};
    octet_t    nmid = {};
    opt_t< bit4_t >   native_nksi        = {};
    opt_t< octet_t >  nmm_capability;
    opt_t< octet_t >  security_capability;
    opt_t< octet_t >  requested_nssai;
    opt_t< octet_6 >  last_visited_tai;
    opt_t< octet_t >  s1_ue_network_capability;
    opt_t< octet_t >  uplink_data_status;
    opt_t< octet_t >  pdu_session_status;
    opt_t< bit4_t >   mico_ind;
    opt_t< uint8_t >  ue_status;
    opt_t< octet_b >  additional_guti_mid;
    opt_t< octet_t >  allowed_pdu_session_status;
    opt_t< uint8_t >  ue_usage_setting;
    opt_t< uint8_t >  requested_drx_parameters;
    opt_t< octet_t >  eap;
    opt_t< octet_t >  ladn_ind;
    opt_t< bit4_t >   payload_container_type;
    opt_t< octet_t >  payload_container;
    opt_t< bit4_t >   network_slicing_ind;
    opt_t< uint8_t >  nupdate_type;
    opt_t< octet_3 >  mobile_station_classmark2;
    opt_t< octet_t >  supported_codecs;
    opt_t< octet_t >  nas_message_container;
    opt_t< uint16_t > eps_bearer_context_status;
    opt_t< uint8_t >  requested_extended_drx_parameters;
    opt_t< uint8_t >  t3324;
};

/*
Table 8.2.7.1.1: REGISTRATION ACCEPT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Registration accept message identity	Message type	9.7	M	V	1
    5GS registration result	5GS registration result	9.11.3.6	M	LV	2
77	5G-GUTI	5GS mobile identity	9.11.3.4	O	TLV-E	14
4A	Equivalent PLMNs	PLMN list	9.11.3.45	O	TLV	5-47
54	TAI list	5GS tracking area identity list	9.11.3.9	O	TLV	9-114
15	Allowed NSSAI	NSSAI	9.11.3.37	O	TLV	4-74
11	Rejected NSSAI	Rejected NSSAI	9.11.3.46	O	TLV	4-42
31	Configured NSSAI	NSSAI	9.11.3.37	O	TLV	4-146
21	5GS network feature support	5GS network feature support	9.11.3.5	O	TLV	3-5
50	PDU session status	PDU session status	9.11.3.44	O	TLV	4-34
26	PDU session reactivation result	PDU session reactivation result	9.11.3.42	O TLV 4-34
72	PDU session reactivation result error cause	PDU session reactivation result error
cause	9.11.3.43	O	TLV-E	5-515
79	LADN information	LADN information	9.11.3.30	O	TLV-E	12-1715
B-	MICO indication	MICO indication	9.11.3.31	O	TV	1
9-	Network slicing indication	Network slicing indication	9.11.3.36	O	TV	1
27	Service area list	Service area list	9.11.3.49	O	TLV	6-114
5E	T3512 value	GPRS timer 3	9.11.2.5	O	TLV	3
5D	Non-3GPP de-registration timer value	GPRS timer 2	9.11.2.4	O	TLV	3
16	T3502 value	GPRS timer 2	9.11.2.4	O	TLV	3
34	Emergency number list	Emergency number list	9.11.3.23	O	TLV	5-50
7A	Extended emergency number list	Extended emergency number list	9.11.3.26	O TLV-E 7-65538
73	SOR transparent container	SOR transparent container	9.11.3.51	O TLV-E 20-n
78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
A-	NSSAI inclusion mode NSSAI inclusion mode	9.11.3.37A	O	TV	1
76	Operator-defined access category definitions	Operator-defined access category definitions	9.11.3.38	O	TLV-E	3-n
51 Negotiated DRX parameters	5GS DRX parameters	9.11.3.2A	O	TLV	3
D-	Non-3GPP NW policies	Non-3GPP NW provided policies	9.11.3.58	O	TV	1
60	EPS bearer context status	EPS bearer context status	9.11.3.59	O	TLV	4
xx	Negotiated extended DRX parameters	Extended DRX parameters	9.11.3.60	O	TLV	3
tbd	T3447 value	GPRS timer 3	9.11.2.5	O	TLV	3
XX	T3448 value	GPRS timer 3	9.11.2.4	O	TLV	3
TBD T3324 value	GPRS timer 3	9.11.2.5	O	TLV	3
*/
struct registration_accept_t {
    nmm_header_t header = {};
    uint8_t      nregistration_result;
    opt_t< octet_b > guti_nmid;
    opt_t< octet_t > equivalent_plmns;
    opt_t< octet_t > tai_list;
    opt_t< octet_t > allowed_nssai;
    opt_t< octet_t > rejected_nssai;
    opt_t< octet_t > configured_nssai;
    opt_t< octet_t > nnetwork_feature_support;
    opt_t< octet_t > pdu_session_status;
    opt_t< octet_t > pdu_session_reactivation_result;
    opt_t< octet_t > pdu_session_reactivation_result_error_cause;
    opt_t< octet_t > ladn_information;
    opt_t< bit4_t >  mico_ind;
    opt_t< bit4_t >  network_slicing_ind;
    opt_t< octet_t > service_area_list;
    opt_t< uint8_t > t3512;
    opt_t< uint8_t > n3_deregistration_timer;
    opt_t< uint8_t > t3502;
    opt_t< octet_t > emergency_numbers;
    opt_t< octet_t > extended_emergency_numbers;
    opt_t< octet_t > sor_container;
    opt_t< octet_t > eap;
    opt_t< bit4_t >  nssai_inclusion_mode;
    opt_t< octet_t > access_categories;
    opt_t< uint8_t > negotiated_drx_parameters;
    opt_t< bit4_t >  n3_nw_provided_policies;
    opt_t< uint16_t > eps_bearer_context_status;
    opt_t< uint8_t >  negotiated_extended_drx_parameters;
    opt_t< uint8_t >  t3447;
    opt_t< uint8_t >  t3348;
    opt_t< uint8_t >  t3324;
};

using octet_17 = uint8_t[17];

/*
Table 8.2.8.1.1: REGISTRATION COMPLETE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Registration complete message identity	Message type	9.7	M	V	1
73	SOR transparent container	SOR transparent container	9.11.3.51	O	TLV-E	20
*/
struct registration_complete_t {
    nmm_header_t header;
    opt_t< octet_t > sor_container;
};

/*
Table 8.2.9.1.1: REGISTRATION REJECT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Registration reject message identity	Message type	9.7	M	V	1
    5GMM cause	5GMM cause	9.11.3.2	M	V	1
5F	T3346 value	GPRS timer 2	9.11.2.4	O	TLV	3
16	T3502 value	GPRS timer 2	9.11.2.4	O	TLV	3
78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
*/
struct registration_reject_t {
    nmm_header_t header;
    uint8_t      cause;
    opt_t< uint8_t > t3346;
    opt_t< uint8_t > t3502;
    opt_t< octet_t > eap;
};

/*
Table 8.2.10.1.1: UL NAS TRANSPORT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    UL NAS TRANSPORT message identity	Message type	9.7	M	V	1
    Payload container type	Payload container type	9.11.3.40	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Payload container	Payload container	9.11.3.39	M	LV-E	3-65537
12	PDU session ID	PDU session identity 2	9.11.3.41	C	TV	2
59	Old PDU session ID	PDU session identity 2	9.11.3.41	O	TV	2
8	Request type	Request type	9.11.3.47	O	TV	1
22	S-NSSAI	S-NSSAI	9.11.2.8	O	TLV	3-10
25	DNN	DNN	9.11.2.1A	O	TLV	3-102
24	Additional information	Additional information	9.11.2.1	O	TLV	3-n
Z	MA PDU session information	MA PDU session information	O	TV	1
*/
struct ul_nas_transport_t {
    nmm_header_t header;
    bit4_t       payload_container_type;
    octet_t      payload_container;
    uint8_t      pdu_session_id;
    opt_t< uint8_t > old_pdu_session_id;
    opt_t< bit4_t >  request_type;
    opt_t< octet_t > s_nssai;
    opt_t< octet_t > dnn;
    opt_t< octet_t > additional_information;
    opt_t< bit4_t >  ma_pdu_session_information;
};

/*
Table 8.2.11.1.1: DL NAS TRANSPORT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    DL NAS TRANSPORT message identity	Message type	9.7	M	V	1
    Payload container type	Payload container type	9.11.3.40	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Payload container	Payload container	9.11.3.39	M	LV-E	3-65537
12	PDU session ID	PDU session identity 2	9.11.3.41	C	TV	2
24	Additional information	Additional information	9.11.2.1	O	TLV	3-n
58	5GMM cause	5GMM cause	9.11.3.2	O	TV	2
37	Back-off timer value	GPRS timer 3	9.11.2.5	O	TLV	3
*/
struct dl_nas_transport_t {
    nmm_header_t header;
    bit4_t       payload_container_type;
    octet_t      payload_container;
    opt_t< uint8_t > pdu_session_id;
    opt_t< octet_t > additional_infomation;
    opt_t< uint8_t > cause;
    opt_t< uint8_t > backoff_timer;
};

/*
Table 8.2.12.1.1: DEREGISTRATION REQUEST message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    De-registration request message identity	Message type	9.7	M	V	1
    De-registration type	De-registration type	9.11.3.20	M	V	1/2
    ngKSI	NAS key set identifier	9.11.3.32	M	V	1/2
    5GS mobile identity		5GS mobile identity	9.11.3.4	M	LV-E	6-n
*/
struct deregistration_request_t {
    nmm_header_t header;
    bit4_t       type;
    bit4_t       nksi;
    octet_t      nmid;
};

/*
Table 8.2.13.1.1: DEREGISTRATION ACCEPT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    De-registration accept message identity	Message type	9.7	M	V	1
*/
struct deregistration_accept_t {
    nmm_header_t header;
};

/*
Table 8.2.14.1.1: DEREGISTRATION REQUEST message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    De-registration request message identity	Message type	9.7	M	V	1
    De-registration type	De-registration type	9.11.3.20	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
58	5GMM cause	5GMM cause	9.11.3.2	O	TV	2
5F	T3346 value	GPRS timer 2	9.11.2.4	O	TLV	3
*/
struct deregistration_request_t {
    nmm_header_t header;
    bit4_t       type;
    opt_t< uint8_t > cause;
    opt_t< uint8_t > t3346;
};

/*
Table 8.2.15.1.1.1: DEREGISTRATION ACCEPT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    De-registration accept message identity	Message type	9.7	M	V	1
*/
struct deregistration_accept_t {
    nmm_header_t header;
};

using octet_8 = uint8_t[8];
using octet_7 = uint8_t[7];

/*
Table 8.2.16.1.1: SERVICE REQUEST message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Service request message identity	Message type	9.7	M	V	1
    ngKSI 	NAS key set identifier	9.11.3.32	M	V	1/2
    Service type	Service type	9.11.3.50	M	V	1/2
    5G-S-TMSI	5GS mobile identity	9.11.3.4	M	LV-E	9
40	Uplink data status	Uplink data status	9.11.3.57	O	TLV	4-34
50	PDU session status	PDU session status	9.11.3.44	O	TLV	4-34
25	Allowed PDU session status	Allowed PDU session status	9.11.3.13	O	TLV	4-34
71	NAS message container	NAS message container	9.11.3.33	O	TLV-E	4-n
*/
struct nas_message_t;

struct service_request_t {
    nmm_header_t header;
    bit4_t       nksi;
    bit4_t       type;
    octet_7      tmsi_nmid;
    opt_t< data_status_t >        uplink_data_status;
    opt_t< pdu_session_status_t > pdu_session_status;
    opt_t< allowed_pdu_session_status_t > allowed_pdu_session_status;
    opt_t< octet_t >                      message;
};

/*
Table 8.2.17.1.1: SERVICE ACCEPT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Service accept message identity	Message type	9.7	M	V	1
50	PDU session status	PDU session status	9.11.3.44	O	TLV	4-34
26	PDU session reactivation result	PDU session reactivation result	9.11.3.42	O TLV
4-34
72	PDU session reactivation result error cause	PDU session reactivation result error
cause	9.11.3.43	O	TLV-E	5-515
78	EAP message	EAP message	9.11.2.2	O	TLV-E 7-1503
XX	T3448 value	GPRS timer 3	9.11.2.4	O	TLV	3
*/
struct service_accept_t {
    nmm_header_t header;
    opt_t< pdu_session_status_t > pdu_session_status;
    opt_t< pdu_session_reactivation_result_t > pdu_session_reactivation_result;
    opt_t< pdu_session_reactivation_result_error_cause_t > result_error_cause;
    opt_t< eap_t >                                         eap;
    opt_t< uint8_t >                                       t3348;
};

/*
Table 8.2.18.1.1: SERVICE REJECT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Service reject message identity	Message type	9.7	M	V	1
    5GMM cause	5GMM cause	9.11.3.2	M	V	1
50	PDU session status	PDU session status	9.11.3.44	O	TLV	4-34
5F	T3346 value	GPRS timer 2	9.11.2.4	O	TLV	3
78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
XX	T3448 value	GPRS timer 3	9.11.2.4	O	TLV	3
*/
struct service_reject_t {
    nmm_header_t header;
    uint8_t      cause;
    opt_t< pdu_session_status_t > pdu_session_status;
    opt_t< uint8_t >              t3346;
    opt_t< eap_t >                eap;
    opt_t< uint8_t >              t3348;
};

/*
Table 8.2.19.1.1: CONFIGURATION UPDATE COMMAND message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Configuration update command message identity	Message type	9.7	M	V	1
D-	Configuration update indication	Configuration update indication	9.11.3.18	O	TV	1
77	5G-GUTI	5GS mobile identity	9.11.3.4	O	TLV-E	14
54	TAI list	5GS tracking area identity list	9.11.3.9	O	TLV	9-114
15	Allowed NSSAI	NSSAI	9.11.3.37	O	TLV	4-74
27	Service area list	Service area list	9.11.3.49	O	TLV	6-114
43	Full name for network	Network name	9.11.3.35	O	TLV	3-n
45	Short name for network	Network name	9.11.3.35	O	TLV	3-n
46	Local time zone	Time zone	9.11.3.52	O	TV	2
47	Universal time and local time zone	Time zone and time	9.11.3.53	O	TV	8
49	Network daylight saving time	Daylight saving time	9.11.3.19	O	TLV	3
79	LADN information	LADN information	9.11.3.30	O	TLV-E	3-1715
B-	MICO indication	MICO indication	9.11.3.31	O	TV	1
9-	Network slicing indication	Network slicing indication	9.11.3.36	O	TV	1
31	Configured NSSAI	NSSAI	9.11.3.37	O	TLV	4-146
11	Rejected NSSAI	Rejected NSSAI	9.11.3.46	O	TLV	4-42
76	Operator-defined access category definitions	Operator-defined access category
definitions	9.11.3.38	O	TLV-E	3-n
F-	SMS indication	SMS indication	9.11.3.50A O TV	1
Tbd	T3447 value	GPRS timer 3	9.11.2.5	O	TLV	3
*/
struct configuration_update_command_t {
    nmm_header_t header;
    opt_t< uint8_t > ind;
    opt_t< octet_b > nguti_nmid;
    opt_t< ntracking_area_id_list_t > tais;
    opt_t< nssai_t >                  allowed_nssai;
    opt_t< service_area_list_t >      service_areas;
    opt_t< octet_t >                  full_name;
    opt_t< octet_t >                  short_name;
    opt_t< uint8_t >                  local_time_zone;
    opt_t< octet_7 >                  utc;
    opt_t< uint8_t >                  daylight_saving_time;
    opt_t< ladn_information_t >       ladn_information;
    opt_t< bit4_t >                   mico_ind;
    opt_t< bit4_t >                   network_slicing_ind;
    opt_t< nssai_t >                  configured_nssai;
    opt_t< nssai_t >                  rejected_nssai;
    opt_t< octet_t >                  operator_defined_access_category_definitions;
    opt_t< bit4_t >                   sms_ind;
    opt_t< uint8_t >                  t3347;
};

/*
Table 8.2.20.1.1: CONFIGURATION UPDATE COMPLETE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Configuration update complete message identity	Message type	9.7	M	V	1
*/
struct configuration_update_complete_t {
    nmm_header_t header;
};

/*
Table 8.2.21.1.1: IDENTITY REQUEST message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Identity request message identity	Message type	9.7	M	V	1
    Identity type	5GS identity type	9.11.3.3	M	V	1/2
    Spare half octet	Spare half octet 	9.5	M	V	1/2
*/
struct identity_request_t {
    nmm_header_t header;
    bit4_t       nidentity_type;
};

/*
Table 8.2.22.1.1: IDENTITY RESPONSE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Identity response message identity	Message type	9.7	M	V	1
    Mobile identity	5GS mobile identity	9.11.3.4	M	LV-E	3-n
*/
struct identity_response_t {
    nmm_header_t header;
    octet_t      nmid;
};

/*
Table 8.2.23.1.1: NOTIFICATION message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Notification message identity	Message type	9.7	M	V	1
    Access type	Access type	9.11.3.11	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
*/
struct notification_t {
    nmm_header_t header;
    bit4_t       access_type;
};

/*
Table 8.2.2341.1: NOTIFICATION RESPONSE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Notification response message identity	Message type	9.7	M	V	1
50	PDU session status	PDU session status	9.11.3.44	O	TLV	4-34
*/
struct notification_response_t {
    nmm_header_t header;
    opt_t< pdu_session_status_t > pdu_session_status;
};

struct s1_ue_network_capability_t{};

/*
Table 8.2.25.1.1: SECURITY MODE COMMAND message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Security mode command message identity	Message type	9.7	M	V	1
    Selected NAS security algorithms	NAS security algorithms	9.11.3.34	M	V	1
    ngKSI	NAS key set identifier	9.11.3.32	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Replayed UE security capabilities	UE security capability	9.11.3.54	M	LV	3-9
E-	IMEISV request	IMEISV request	9.11.3.28	O	TV	1
57	Selected EPS NAS security algorithms	EPS NAS security algorithms	9.11.3.25 O	TV	2
36	Additional 5G security information	Additional 5G security information	9.11.3.12	O	TLV	3
78	EAP message	EAP message	9.11.2.2	O	TLV-E 7-1503
38	ABBA	ABBA	9.11.3.10	O	TLV	4-n
19	Replayed S1 UE security capabilities	S1 UE security capability	9.11.3.48A	O	TLV	4-7
*/
struct security_mode_command_t {
    nmm_header_t header;
    uint8_t      selected_security_algo;
    bit4_t       nksi;
    ue_security_capability_t replayed_ue_security_capabilities;
    opt_t< bit4_t >          imeisv_request;
    opt_t< uint8_t >         selected_eps_security_algo;
    opt_t< uint8_t >         additional_5g_security_information;
    opt_t< eap_t >           eap;
    opt_t< abba_t >          abba;
    opt_t< s1_ue_network_capability_t > replayed_s1_ue_security_capabilities;
};

/*
Table 8.2.26.1.1: SECURITY MODE COMPLETE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Security mode complete message identity	Message type	9.6	M	V	1
77	IMEISV	5G mobile identity	9.11.3.4	O	TLV-E	12
71	NAS message container	NAS message container	9.11.3.33	O	TLV-E	4-n
*/
struct security_mode_complete_t {
    nmm_header_t           header;
    opt_t< octet_b >       imeisv_nmid;
    opt_t< nas_message_t > message;
};

/*
Table 8.2.27.1.1: SECURITY MODE REJECT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Security mode reject message identity	Message type	9.6	M	V	1
    5GMM cause	5GMM cause	9.11.3.2	M	V	1
*/
struct security_mode_reject_t {
    nmm_header_t header;
    uint8_t      cause;
};

/*
Table 8.2.28.1.1: SECURITY PROTECTED 5GS NAS MESSAGE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Message authentication code	Message authentication code	9.8	M	V	4
    Sequence number	Sequence number	9.10	M	V	1
    Plain 5GS NAS message	Plain 5GS NAS message	9.9	M	V	3-n
*/
struct nas_message_protected_t;

/*
Table 8.2.29.1.1: 5GMM STATUS message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    5GMM STATUS message identity	Message type	9.7	M	V	1
    5GMM cause	5GMM cause	9.11.3.2	M	V	1
*/
struct nmm_status_t {
    nmm_header_t header;
    uint8_t      cause;
};

/*
Table 8.3.1.1.1: PDU SESSION ESTABLISHMENT REQUEST message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION ESTABLISHMENT REQUEST message identity	Message type	9.7	M	V	1
    Integrity protection maximum data rate	Integrity protection maximum data rate	9.11.4.7	M	V	2
9-	PDU session type	PDU session type	9.11.4.11	O	TV	1
A-	SSC mode	SSC mode	9.11.4.16	O	TV	1
28	5GSM capability	5GSM capability	9.11.4.1	O	TLV	3-15
55	Maximum number of supported packet filters	Maximum number of supported packet
filters	9.11.4.9	O	TV	3
B-	Always-on PDU session requested	Always-on PDU session requested	9.11.4.4	O	TV	1
39	SM PDU DN request container	SM PDU DN request container	9.11.4.15	O	TLV	3-255
7B	Extended protocol configuration options Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
*/
struct pdu_session_establishment_request_t {
    nsm_header_t header;
    uint16_t     integrity_max_data_rate;
    opt_t< bit4_t > pdu_sssion_type;
    opt_t< bit4_t > ssc_mode;
    opt_t< nsm_capability_t > nsm_capabilities;
    opt_t< uint16_t >         supported_packet_filters_max_n;
    opt_t< bit4_t >           always_on_pdu_session_requested;
    opt_t< octet_t >          sm_pdu_dn_request_container;
    opt_t< octet_t >          extended_pco;
};

// clang-format off
/*
Table 8.3.2.1.1: PDU SESSION ESTABLISHMENT ACCEPT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION ESTABLISHMENT ACCEPT message identity	Message type	9.7	M	V	1
    Selected PDU session type	PDU session type	9.11.4.11	M	V	1/2
    Selected SSC mode	SSC mode	9.11.4.16	M	V	1/2
    Authorized QoS rules	QoS rules	9.11.4.13	M	LV-E	6-65538
    Session AMBR	Session-AMBR	9.11.4.14	M	LV	7
59	5GSM cause	5GSM cause	9.11.4.2	O	TV	2
29	PDU address	PDU address	9.11.4.10	O	TLV	7, 11 or 15
56	RQ timer value	GPRS timer	9.11.2.3	O	TV	2
22	S-NSSAI	S-NSSAI	9.11.2.8	O	TLV	3-10
8-	Always-on PDU session indication	Always-on PDU session indication	9.11.4.3 O TV 1
75	Mapped EPS bearer contexts	Mapped EPS bearer contexts	9.11.4.8	O	TLV-E 7-65538
78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
79	Authorized QoS flow descriptions	QoS flow descriptions	9.11.4.12	O	TLV-E 6-65538
7B	Extended protocol configuration options	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
25	DNN	DNN	9.11.2.1A	O	TLV	3-102
xx	5GSM network feature support	5GSM network feature support	9.11.4.18	O	TLV	3-15
xx Session-TMBR	Session-TMBR	9.11.4.19	O	TLV	8
TBD	Serving PLMN rate control Serving PLMN rate control	9.11.4.20	O	TLV	4
XX	ATSSS container	ATSSS container	9.11.4.22	O	TLV-E	3-65538
XX	Control plane only indication	Control plane only indication	9.11.4.23	O	TV	1
*/
// clang-format on
struct pdu_session_establishment_accept_t {
    nms_header_t header;
    bit4_t       selected_pdu_session_type;
    bit4_t       ssc_mode;
    octet_t      authorized_qos_rules;
    octet_6      session_ambr;
    opt_t< uint8_t > cause;
    opt_t< octet_t > pdu_address;
    opt_t< uint8_t > rq_timer;
    opt_t< s_nssai_t > s_nssai;
    opt_t< bit4_t >    always_on_pdu_session_ind;
    opt_t< mapped_eps_bearer_contexts_t > mapped_eps_bearer_contexts;
    opt_t< eap_t >                        eap;
    opt_t< qos_flow_descriptions_t >      authorized_qos_flow_descs;
    opt_t< extended_pco_t >               extended_pco;
    opt_t< dnn_t >                        dnn;
    opt_t< nsm_network_feature_support_t > nsm_network_feature_support;
    opt_t< session_tmbr_t >                session_tmbr_t;
    opt_t< uint16_t >                      serving_plmn_rate_control;
    opt_t< atsss_container_t >             atsss_container;
    opt_t< bit4_t >                        control_plane_only_indi;
};

// clang-format off
/*
Table 8.3.3.1.1: PDU SESSION ESTABLISHMENT REJECT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION ESTABLISHMENT REJECT message identity	Message type	9.7	M	V	1
    5GSM cause	5GSM cause	9.11.4.2	M	V	1
37	Back-off timer value	GPRS timer 3	9.11.2.5	O	TLV	3
F-	Allowed SSC mode	Allowed SSC mode	9.11.4.5	O	TV	1
78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
7B	Extended protocol configuration options	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
TBD	Re-attempt indicator	Re-attempt indicator	9.11.4.17	O	TLV	3
61	5GSM congestion re-attempt indicator	5GSM congestion re-attempt indicator	9.11.4.21	O	TLV	3
*/
// clang-format on
struct pdu_session_establishment_reject_t {
    nsm_header_t            header;
    uint8_t                 cause;
    opt_t< uint8_t >        backoff_timer;
    opt_t< bit4_t >         allowed_ssc_mode;
    opt_t< eap_t >          eap;
    opt_t< extended_pco_t > extended_pco;
    opt_t< uint8_t >        reattempt_ind;
    opt_t< uint8_t >        nsm_congestion_reattempt_ind;
};

/*
Table 8.3.4.1.1: PDU SESSION AUTHENTICATION COMMAND message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION AUTHENTICATION COMMAND message identity	Message type	9.7	M	V	1
    EAP message	EAP message	9.11.2.2	M	LV-E	6-1502
7B	Extended protocol configuration options	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
*/
struct pdu_session_authentication_command_t {
    nsm_header_t header;
    eap_t        eap;
    opt_t< extended_pco_t > extended_pco;
};

// clang-format off
/*
Table 8.3.5.1.1: PDU SESSION AUTHENTICATION COMPLETE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION AUTHENTICATION COMPLETE message identity	Message type	9.7	M	V	1
    EAP message	EAP message	9.11.2.2	M	LV-E	6-1502
7B	Extended protocol configuration options	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
*/
// clang-format on
struct pdu_session_authentication_complete_t {
    nsm_header_t header;
    eap_t        eap;
    opt_t< extended_pco_t > extended_pco;
};

// clang-format off
/*
Table 8.3.6.1.1: PDU SESSION AUTHENTICATION RESULT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION AUTHENTICATION RESULT message identity	Message type	9.7	M	V	1
78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
7B	Extended protocol configuration options	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
*/
// clang-format on
struct pdu_session_authentication_result_t {
    nsm_header_t header;
    eap_t        eap;
    opt_t< extended_pco_t > extended_pco;
};

// clang-format off
/*
Table 8.3.7.1.1: PDU SESSION MODIFICATION REQUEST message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION MODIFICATION REQUEST message identity	Message type	9.7	M	V	1
28	5GSM capability	5GSM capability	9.11.4.1	O	TLV	3-15
59	5GSM cause	5GSM cause	9.11.4.2	O	TV	2
55	Maximum number of supported packet filters	Maximum number of supported packet filters	9.11.4.9	O	TV	3
B-	Always-on PDU session requested	Always-on PDU session requested	9.11.4.4	O	TV	1
13	Integrity protection maximum data rate	Integrity protection maximum data rate	9.11.4.7	O	TV	3
7A	Requested QoS rules	QoS rules	9.11.4.13	O	TLV-E	7-65538
79	Requested QoS flow descriptions	QoS flow descriptions	9.11.4.12	O	TLV-E	6-65538
75	Mapped EPS bearer contexts	Mapped EPS bearer contexts	9.11.4.8	O	TLV-E	7-65538
7B	Extended protocol configuration options	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
*/
// clang-format on
struct pdu_session_modification_request_t {
    nsm_header_t header;
    opt_t< nsm_capability_t > capabilities;
    opt_t< uint8_t >          cause;
    opt_t< uint16_t >         supported_packet_filters_max_n;
    opt_t< bit4_t >           always_on_pdu_session_requested;
    opt_t< uint16_t >         integrity_max_data_rate;
    opt_t< qos_rules_t >      requested_qos_rules;
    opt_t< qos_flow_descriptions_t > requested_qos_flow_descs;
    opt_t< mapped_eps_bearer_contexts_t > mapped_eps_bearer_contexts;
    opt_t< extended_pco_t >               extended_pco;
};

// clang-format off
/*
Table 8.3.8.1.1: PDU SESSION MODIFICATION REJECT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION MODIFICATION REJECT message identity	Message type	9.7	M	V	1
    5GSM cause	5GSM cause	9.11.4.2	M	V	1
37	Back-off timer value	GPRS timer 3	9.11.2.5	O	TLV	3
7B	Extended protocol configuration options	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
TBD	Re-attempt indicator	Re-attempt indicator	9.11.4.17	O	TLV	3
61	5GSM congestion re-attempt indicator	5GSM congestion re-attempt indicator	9.11.4.21	O	TLV	3
*/
// clang-format on
struct pdu_session_modification_reject_t {
    nsm_header_t            header;
    uint8_t                 cause;
    opt_t< uint8_t >        backoff_timer;
    opt_t< extended_pco_t > extended_pco;
    opt_t< uint8_t >        reattempt_ind;
    opt_t< uint8_t >        nsm_congestion_reattempt_ind;
};

/*
Table 8.3.9.1.1: PDU SESSION MODIFICATION COMMAND message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION MODIFICATION COMMAND message identity	Message type	9.7	M	V	1
59	5GSM cause	5GSM cause	9.11.4.2	O	TV	2
2A	Session AMBR	Session-AMBR	9.11.4.14	O	TLV	8
56	RQ timer value	GPRS timer	9.11.2.3	O	TV	2
8-	Always-on PDU session indication	Always-on PDU session indication	9.11.4.3 O TV 1
7A	Authorized QoS rules	QoS rules	9.11.4.13	O	TLV-E	7-65538
75	Mapped EPS bearer contexts	Mapped EPS bearer contexts	9.11.4.8	O	TLV-E	7-65538
79 Authorized QoS flow descriptions	QoS flow descriptions	9.11.4.12	O	TLV-E	6-65538
7B Extended protocol configuration options	Extended protocol configuration options	9.11.4.6 O	TLV-E	4-65538
xx	Session-TMBR	Session-TMBR	9.11.4.19	O	TLV	8
*/
struct pdu_session_modification_command_t {
    nsm_header_t header;
    opt_t< uint8_t > cause;
    opt_t< octet_6 > session_ambr;
    opt_t< uint8_t > rq_timer;
    opt_t< bit4_t >  always_on_pdu_session_ind;
    opt_t< qos_rules_t > authorized_qos_rules;
    opt_t< mapped_eps_bearer_contexts_t > mapped_eps_bearer_contexts;
    opt_t< qos_flow_descriptions_t >      authorized_qos_flow_descs;
    opt_t< extended_pco_t >               extended_pco;
};

/*
Table 8.3.10.1.1: PDU SESSION MODIFICATION COMPLETE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION MODIFICATION COMPLETE message identity	Message type	9.7	M	V	1
7B	Extended protocol configuration options	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
*/
struct pdu_session_modification_complete_t {
    nsm_header_t header;
    opt_t< extended_pco_t > extended_pco;
};

/*
Table 8.3.11.1.1: PDU SESSION MODIFICATION COMMAND REJECT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION MODIFICATION COMMAND REJECT message identity	Message type	9.7	M V	1
    5GSM cause	5GSM cause	9.11.4.2	M	V	1
7B	Extended protocol configuration options	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
*/
struct pdu_session_modification_command_t {
    nsm_header_t header;
    uint8_t      cause;
    opt_t< extended_pco_t > extended_pco;
};

/*
Table 8.3.12.1.1: PDU SESSION RELEASE REQUEST message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION RELEASE REQUEST message identity	Message type	9.7	M	V	1
59	5GSM cause	5GSM cause	9.11.4.2	O	TV	2
7B	Extended protocol configuration options	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
*/
struct pdu_session_release_request_t {
    opt_t< uint8_t > cause;
    opt_t< extended_pco_t > extended_pco;
};

/*
Table 8.3.13.1.1: PDU SESSION RELEASE REJECT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION RELEASE REJECT message identity	Message type	9.7	M	V	1
    5GSM cause	5GSM cause	9.11.4.2	M	V	1
7B	Extended protocol configuration options	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
*/
struct pdu_session_release_reject_t {
    uint8_t cause;
    opt_t< extended_pco_t > extended_pco;
};

/*
Table 8.3.14.1.1: PDU SESSION RELEASE COMMAND message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION RELEASE COMMAND message identity	Message type	9.7	M	V	1
    5GSM cause	5GSM cause	9.11.4.2	M	V	1
37	Back-off timer value	GPRS timer 3	9.11.2.5	O	TLV	3
78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
61	5GSM congestion re-attempt indicator	5GSM congestion re-attempt indicator	9.11.4.21	O	TLV	3
7B	Extended protocol configuration options	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
*/
struct pdu_session_release_command_t {
    uint8_t                 cause;
    opt_t< uint8_t >        backoff_timer;
    opt_t< eap_t >          eap;
    opt_t< uint8_t >        nsm_congestion_reattempt_ind;
    opt_t< extended_pco_t > extended_pco;
};

/*
Table 8.3.15.1.1: PDU SESSION RELEASE COMPLETE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION RELEASE COMPLETE message identity	Message type	9.7	M	V	1
59	5GSM cause	5GSM cause	9.11.4.2	O	TV	2
7B	Extended protocol configuration options	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
*/
struct pdu_session_release_complete_t {
    nsm_header_t header;
    opt_t< uint8_t > cause;
    opt_t< extended_pco_t > extended_pco;
};

/*
Table 8.3.16.1.1: 5GSM STATUS message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    5GSM STATUS message identity	Message type	9.7	M	V	1
    5GSM cause	5GSM cause	9.11.4.2	M	V	1
*/
struct nsm_status_t {
    nsm_header_t header;
    uint8_t      cause;
};
