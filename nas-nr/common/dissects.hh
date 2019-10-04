#pragma once
#include "definitions.hh"

result_t de_nmm_header(dissector d, context* ctx, nmm_header_t* ret);
result_t de_nsm_header(dissector d, context* ctx, nsm_header_t* ret);


result_t de_nas_message(dissector d, context* ctx, nas_message_t* v);

result_t de_nsm_message(dissector d, context* ctx, nsm_message_t* v);

result_t de_nmm_message(dissector d, context* ctx, nmm_message_t* v);

result_t de_nas_plain(dissector d, context* ctx, nas_message_plain_t* v);

result_t de_nas_protected(dissector d, context* ctx, nas_message_protected_t* v);

result_t de_registration_request(dissector d, context* ctx, registration_request_t* ret);

result_t de_registration_accept(dissector d, context* ctx, registration_accept_t* ret);

result_t de_registration_complete(dissector                d,
                                  context*                 ctx,
                                  registration_complete_t* ret);

result_t de_registration_reject(dissector d, context* ctx, registration_reject_t* ret);

result_t de_deregistration_request_ue_orig(dissector                         d,
                                           context*                          ctx,
                                           deregistration_request_ue_orig_t* ret);

result_t de_deregistration_accept_ue_orig(dissector                        d,
                                          context*                         ctx,
                                          deregistration_accept_ue_orig_t* ret);

result_t de_deregistration_request_ue_term(dissector                         d,
                                           context*                          ctx,
                                           deregistration_request_ue_term_t* ret);

result_t de_deregistration_accept_ue_term(dissector                        d,
                                          context*                         ctx,
                                          deregistration_accept_ue_term_t* ret);

result_t de_service_request(dissector d, context* ctx, service_request_t* ret);

result_t de_service_reject(dissector d, context* ctx, service_reject_t* ret);

result_t de_service_accept(dissector d, context* ctx, service_accept_t* ret);

result_t de_configuration_update_command(dissector                       d,
                                         context*                        ctx,
                                         configuration_update_command_t* ret);

result_t de_configuration_update_complete(dissector                        d,
                                          context*                         ctx,
                                          configuration_update_complete_t* ret);

result_t de_authentication_request(dissector                 d,
                                   context*                  ctx,
                                   authentication_request_t* ret);

result_t de_authentication_response(dissector                  d,
                                    context*                   ctx,
                                    authentication_response_t* ret);

result_t de_authentication_reject(dissector                d,
                                  context*                 ctx,
                                  authentication_reject_t* ret);

result_t de_authentication_failure(dissector                 d,
                                   context*                  ctx,
                                   authentication_failure_t* ret);

result_t de_authentication_result(dissector                d,
                                  context*                 ctx,
                                  authentication_result_t* ret);

result_t de_identity_request(dissector d, context* ctx, identity_request_t* ret);

result_t de_identity_response(dissector d, context* ctx, identity_response_t* ret);

result_t de_security_mode_command(dissector                d,
                                  context*                 ctx,
                                  security_mode_command_t* ret);

result_t de_security_mode_complete(dissector                 d,
                                   context*                  ctx,
                                   security_mode_complete_t* ret);

result_t de_security_mode_reject(dissector d, context* ctx, security_mode_reject_t* ret);

result_t de_nmm_status(dissector d, context* ctx, nmm_status_t* ret);

result_t de_notification(dissector d, context* ctx, notification_t* ret);

result_t de_notification_response(dissector                d,
                                  context*                 ctx,
                                  notification_response_t* ret);

result_t de_ul_nas_transport(dissector d, context* ctx, ul_nas_transport_t* ret);

result_t de_dl_nas_transport(dissector d, context* ctx, dl_nas_transport_t* ret);

result_t de_pdu_session_establishment_request(dissector                            d,
                                              context*                             ctx,
                                              pdu_session_establishment_request_t* ret);

result_t de_pdu_session_establishment_accept(dissector                           d,
                                             context*                            ctx,
                                             pdu_session_establishment_accept_t* ret);

result_t de_pdu_session_establishment_reject(dissector                           d,
                                             context*                            ctx,
                                             pdu_session_establishment_reject_t* ret);

result_t de_pdu_session_authentication_command(dissector                             d,
                                               context*                              ctx,
                                               pdu_session_authentication_command_t* ret);

result_t de_pdu_session_authentication_complete(
    dissector                              d,
    context*                               ctx,
    pdu_session_authentication_complete_t* ret);

result_t de_pdu_session_modification_request(dissector                           d,
                                             context*                            ctx,
                                             pdu_session_modification_request_t* ret);

result_t de_pdu_session_modification_reject(dissector                          d,
                                            context*                           ctx,
                                            pdu_session_modification_reject_t* ret);

result_t de_pdu_session_modification_command(dissector                           d,
                                             context*                            ctx,
                                             pdu_session_modification_command_t* ret);

result_t de_pdu_session_modification_complete(dissector                            d,
                                              context*                             ctx,
                                              pdu_session_modification_complete_t* ret);

result_t de_pdu_session_modification_command_reject(
    dissector                                  d,
    context*                                   ctx,
    pdu_session_modification_command_reject_t* ret);

result_t de_pdu_session_release_request(dissector                      d,
                                        context*                       ctx,
                                        pdu_session_release_request_t* ret);

result_t de_pdu_session_release_reject(dissector                     d,
                                       context*                      ctx,
                                       pdu_session_release_reject_t* ret);

result_t de_pdu_session_release_command(dissector                      d,
                                        context*                       ctx,
                                        pdu_session_release_command_t* ret);

result_t de_pdu_session_release_complete(dissector                       d,
                                         context*                        ctx,
                                         pdu_session_release_complete_t* ret);

result_t de_nsm_status(dissector d, context* ctx, nsm_status_t* ret);

/*
Table 8.2.1.1.1: AUTHENTICATION REQUEST message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Authentication request message identity	Message type	9.7	M	V	1
    ngKSI 	NAS key set identifier	9.11.3.32	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    ABBA	ABBA	9.11.3.10	M	LV	3-n
21	Authentication parameter RAND (5G authentication challenge)	Authentication parameter
RAND	9.11.3.16	O	TV	17 20	Authentication parameter AUTN (5G authentication
challenge)	Authentication parameter AUTN	9.11.3.15	O	TLV	18 78	EAP message	EAP
message	9.11.2.2	O	TLV-E	7-1503

Table 8.2.2.1.1: AUTHENTICATION RESPONSE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Authentication response message identity	Message type	9.7	M	V	1
2D	Authentication response parameter	Authentication response parameter	9.11.3.17 O
TLV	18 78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503

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

Table 8.2.4.1.1: AUTHENTICATION FAILURE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Authentication failure message identity	Message type	9.7	M	V	1
    5GMM cause	5GMM cause	9.11.3.2	M	V	1
30	Authentication failure parameter	Authentication failure parameter	9.11.3.14 O
TLV	16

Table 8.2.5.1.1: AUTHENTICATION REJECT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Authentication reject message identity	Message type	9.7	M	V	1
78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503

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
26	PDU session reactivation result	PDU session reactivation result	9.11.3.42	O TLV
4-34 72	PDU session reactivation result error cause	PDU session reactivation result error
cause	9.11.3.43	O	TLV-E	5-515
79	LADN information	LADN information	9.11.3.30	O	TLV-E	12-1715
B-	MICO indication	MICO indication	9.11.3.31	O	TV	1
9-	Network slicing indication	Network slicing indication	9.11.3.36	O	TV	1
27	Service area list	Service area list	9.11.3.49	O	TLV	6-114
5E	T3512 value	GPRS timer 3	9.11.2.5	O	TLV	3
5D	Non-3GPP de-registration timer value	GPRS timer 2	9.11.2.4	O	TLV	3
16	T3502 value	GPRS timer 2	9.11.2.4	O	TLV	3
34	Emergency number list	Emergency number list	9.11.3.23	O	TLV	5-50
7A	Extended emergency number list	Extended emergency number list	9.11.3.26	O TLV-E
7-65538 73	SOR transparent container	SOR transparent container	9.11.3.51	O TLV-E
20-n 78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503 A-	NSSAI inclusion mode
NSSAI inclusion mode	9.11.3.37A	O	TV	1 76	Operator-defined access category
definitions	Operator-defined access category definitions	9.11.3.38	O	TLV-E	3-n 51
Negotiated DRX parameters	5GS DRX parameters	9.11.3.2A	O	TLV	3 D-	Non-3GPP NW
policies	Non-3GPP NW provided policies	9.11.3.58	O	TV	1 60	EPS bearer context
status	EPS bearer context status	9.11.3.59	O	TLV	4 xx	Negotiated extended DRX
parameters	Extended DRX parameters	9.11.3.60	O	TLV	3 tbd	T3447 value	GPRS timer
3	9.11.2.5	O	TLV	3 XX	T3448 value	GPRS timer 3	9.11.2.4	O	TLV	3 TBD
T3324 value	GPRS timer 3	9.11.2.5	O	TLV	3

Table 8.2.8.1.1: REGISTRATION COMPLETE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Registration complete message identity	Message type	9.7	M	V	1
73	SOR transparent container	SOR transparent container	9.11.3.51	O	TLV-E	20

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

Table 8.2.12.1.1: DEREGISTRATION REQUEST message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    De-registration request message identity	Message type	9.7	M	V	1
    De-registration type	De-registration type	9.11.3.20	M	V	1/2
    ngKSI	NAS key set identifier	9.11.3.32	M	V	1/2
    5GS mobile identity		5GS mobile identity	9.11.3.4	M	LV-E	6-n

Table 8.2.13.1.1: DEREGISTRATION ACCEPT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    De-registration accept message identity	Message type	9.7	M	V	1

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

Table 8.2.15.1.1.1: DEREGISTRATION ACCEPT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    De-registration accept message identity	Message type	9.7	M	V	1

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

Table 8.2.17.1.1: SERVICE ACCEPT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Service accept message identity	Message type	9.7	M	V	1
50	PDU session status	PDU session status	9.11.3.44	O	TLV	4-34
26	PDU session reactivation result	PDU session reactivation result	9.11.3.42	O TLV
4-34 72	PDU session reactivation result error cause	PDU session reactivation result error
cause	9.11.3.43	O	TLV-E	5-515 78	EAP message	EAP message	9.11.2.2	O	TLV-E
7-1503 XX	T3448 value	GPRS timer 3	9.11.2.4	O	TLV	3

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
definitions	9.11.3.38	O	TLV-E	3-n F-	SMS indication	SMS indication	9.11.3.50A O
TV	1 Tbd	T3447 value	GPRS timer 3	9.11.2.5	O	TLV	3

Table 8.2.20.1.1: CONFIGURATION UPDATE COMPLETE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Configuration update complete message identity	Message type	9.7	M	V	1

Table 8.2.21.1.1: IDENTITY REQUEST message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Identity request message identity	Message type	9.7	M	V	1
    Identity type	5GS identity type	9.11.3.3	M	V	1/2
    Spare half octet	Spare half octet 	9.5	M	V	1/2

Table 8.2.22.1.1: IDENTITY RESPONSE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Identity response message identity	Message type	9.7	M	V	1
    Mobile identity	5GS mobile identity	9.11.3.4	M	LV-E	3-n

Table 8.2.23.1.1: NOTIFICATION message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Notification message identity	Message type	9.7	M	V	1
    Access type	Access type	9.11.3.11	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2

Table 8.2.2341.1: NOTIFICATION RESPONSE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Notification response message identity	Message type	9.7	M	V	1
50	PDU session status	PDU session status	9.11.3.44	O	TLV	4-34

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
36	Additional 5G security information	Additional 5G security
information	9.11.3.12	O	TLV	3 78	EAP message	EAP message	9.11.2.2	O	TLV-E
7-1503 38	ABBA	ABBA	9.11.3.10	O	TLV	4-n 19	Replayed S1 UE security
capabilities	S1 UE security capability	9.11.3.48A	O	TLV	4-7

Table 8.2.26.1.1: SECURITY MODE COMPLETE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Security mode complete message identity	Message type	9.6	M	V	1
77	IMEISV	5G mobile identity	9.11.3.4	O	TLV-E	12
71	NAS message container	NAS message container	9.11.3.33	O	TLV-E	4-n

Table 8.2.27.1.1: SECURITY MODE REJECT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Security mode reject message identity	Message type	9.6	M	V	1
    5GMM cause	5GMM cause	9.11.3.2	M	V	1

Table 8.2.28.1.1: SECURITY PROTECTED 5GS NAS MESSAGE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    Message authentication code	Message authentication code	9.8	M	V	4
    Sequence number	Sequence number	9.10	M	V	1
    Plain 5GS NAS message	Plain 5GS NAS message	9.9	M	V	3-n

Table 8.2.29.1.1: 5GMM STATUS message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    Security header type	Security header type	9.3	M	V	1/2
    Spare half octet	Spare half octet	9.5	M	V	1/2
    5GMM STATUS message identity	Message type	9.7	M	V	1
    5GMM cause	5GMM cause	9.11.3.2	M	V	1

Table 8.3.1.1.1: PDU SESSION ESTABLISHMENT REQUEST message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION ESTABLISHMENT REQUEST message identity	Message type	9.7	M	V	1
    Integrity protection maximum data rate	Integrity protection maximum data
rate	9.11.4.7	M	V	2
9-	PDU session type	PDU session type	9.11.4.11	O	TV	1
A-	SSC mode	SSC mode	9.11.4.16	O	TV	1
28	5GSM capability	5GSM capability	9.11.4.1	O	TLV	3-15
55	Maximum number of supported packet filters	Maximum number of supported packet
filters	9.11.4.9	O	TV	3 B-	Always-on PDU session requested	Always-on PDU session
requested	9.11.4.4	O	TV	1 39	SM PDU DN request container	SM PDU DN request
container	9.11.4.15	O	TLV	3-255 7B	Extended protocol configuration options
Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538

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
8-	Always-on PDU session indication	Always-on PDU session indication	9.11.4.3 O TV
1 75	Mapped EPS bearer contexts	Mapped EPS bearer contexts	9.11.4.8	O	TLV-E
7-65538 78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
79	Authorized QoS flow descriptions	QoS flow descriptions	9.11.4.12	O	TLV-E
6-65538 7B	Extended protocol configuration options	Extended protocol configuration
options	9.11.4.6	O	TLV-E	4-65538 25	DNN	DNN	9.11.2.1A	O	TLV	3-102 xx	5GSM
network feature support	5GSM network feature support	9.11.4.18	O	TLV	3-15 xx
Session-TMBR	Session-TMBR	9.11.4.19	O	TLV	8 TBD	Serving PLMN rate control
Serving PLMN rate control	9.11.4.20	O	TLV	4 XX	ATSSS container	ATSSS
container	9.11.4.22	O	TLV-E	3-65538 XX	Control plane only indication	Control
plane only indication	9.11.4.23	O	TV	1

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
7B	Extended protocol configuration options	Extended protocol configuration
options	9.11.4.6	O	TLV-E	4-65538 TBD	Re-attempt indicator	Re-attempt
indicator	9.11.4.17	O	TLV	3 61	5GSM congestion re-attempt indicator	5GSM
congestion re-attempt indicator	9.11.4.21	O	TLV	3

Table 8.3.4.1.1: PDU SESSION AUTHENTICATION COMMAND message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION AUTHENTICATION COMMAND message identity	Message type	9.7	M	V	1
    EAP message	EAP message	9.11.2.2	M	LV-E	6-1502
7B	Extended protocol configuration options	Extended protocol configuration
options	9.11.4.6	O	TLV-E	4-65538

Table 8.3.5.1.1: PDU SESSION AUTHENTICATION COMPLETE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION AUTHENTICATION COMPLETE message identity	Message type	9.7	M	V	1
    EAP message	EAP message	9.11.2.2	M	LV-E	6-1502
7B	Extended protocol configuration options	Extended protocol configuration
options	9.11.4.6	O	TLV-E	4-65538

Table 8.3.6.1.1: PDU SESSION AUTHENTICATION RESULT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION AUTHENTICATION RESULT message identity	Message type	9.7	M	V	1
78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
7B	Extended protocol configuration options	Extended protocol configuration
options	9.11.4.6	O	TLV-E	4-65538

Table 8.3.7.1.1: PDU SESSION MODIFICATION REQUEST message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION MODIFICATION REQUEST message identity	Message type	9.7	M	V	1
28	5GSM capability	5GSM capability	9.11.4.1	O	TLV	3-15
59	5GSM cause	5GSM cause	9.11.4.2	O	TV	2
55	Maximum number of supported packet filters	Maximum number of supported packet
filters	9.11.4.9	O	TV	3 B-	Always-on PDU session requested	Always-on PDU session
requested	9.11.4.4	O	TV	1 13	Integrity protection maximum data rate	Integrity
protection maximum data rate	9.11.4.7	O	TV	3 7A	Requested QoS rules	QoS
rules	9.11.4.13	O	TLV-E	7-65538 79	Requested QoS flow descriptions	QoS flow
descriptions	9.11.4.12	O	TLV-E	6-65538 75	Mapped EPS bearer contexts	Mapped EPS
bearer contexts	9.11.4.8	O	TLV-E	7-65538 7B	Extended protocol configuration
options	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538

Table 8.3.8.1.1: PDU SESSION MODIFICATION REJECT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION MODIFICATION REJECT message identity	Message type	9.7	M	V	1
    5GSM cause	5GSM cause	9.11.4.2	M	V	1
37	Back-off timer value	GPRS timer 3	9.11.2.5	O	TLV	3
7B	Extended protocol configuration options	Extended protocol configuration
options	9.11.4.6	O	TLV-E	4-65538 TBD	Re-attempt indicator	Re-attempt
indicator	9.11.4.17	O	TLV	3 61	5GSM congestion re-attempt indicator	5GSM
congestion re-attempt indicator	9.11.4.21	O	TLV	3

Table 8.3.9.1.1: PDU SESSION MODIFICATION COMMAND message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION MODIFICATION COMMAND message identity	Message type	9.7	M	V	1
59	5GSM cause	5GSM cause	9.11.4.2	O	TV	2
2A	Session AMBR	Session-AMBR	9.11.4.14	O	TLV	8
56	RQ timer value	GPRS timer	9.11.2.3	O	TV	2
8-	Always-on PDU session indication	Always-on PDU session indication	9.11.4.3 O TV
1 7A	Authorized QoS rules	QoS rules	9.11.4.13	O	TLV-E	7-65538 75	Mapped EPS
bearer contexts	Mapped EPS bearer contexts	9.11.4.8	O	TLV-E	7-65538 79 Authorized
QoS flow descriptions	QoS flow descriptions	9.11.4.12	O	TLV-E	6-65538 7B
Extended protocol configuration options	Extended protocol configuration options	9.11.4.6
O	TLV-E	4-65538 xx	Session-TMBR	Session-TMBR	9.11.4.19	O	TLV	8

Table 8.3.10.1.1: PDU SESSION MODIFICATION COMPLETE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION MODIFICATION COMPLETE message identity	Message type	9.7	M	V	1
7B	Extended protocol configuration options	Extended protocol configuration
options	9.11.4.6	O	TLV-E	4-65538

Table 8.3.11.1.1: PDU SESSION MODIFICATION COMMAND REJECT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION MODIFICATION COMMAND REJECT message identity	Message type	9.7	M V	1
    5GSM cause	5GSM cause	9.11.4.2	M	V	1
7B	Extended protocol configuration options	Extended protocol configuration
options	9.11.4.6	O	TLV-E	4-65538

Table 8.3.12.1.1: PDU SESSION RELEASE REQUEST message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION RELEASE REQUEST message identity	Message type	9.7	M	V	1
59	5GSM cause	5GSM cause	9.11.4.2	O	TV	2
7B	Extended protocol configuration options	Extended protocol configuration
options	9.11.4.6	O	TLV-E	4-65538

Table 8.3.13.1.1: PDU SESSION RELEASE REJECT message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION RELEASE REJECT message identity	Message type	9.7	M	V	1
    5GSM cause	5GSM cause	9.11.4.2	M	V	1
7B	Extended protocol configuration options	Extended protocol configuration
options	9.11.4.6	O	TLV-E	4-65538

Table 8.3.14.1.1: PDU SESSION RELEASE COMMAND message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION RELEASE COMMAND message identity	Message type	9.7	M	V	1
    5GSM cause	5GSM cause	9.11.4.2	M	V	1
37	Back-off timer value	GPRS timer 3	9.11.2.5	O	TLV	3
78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
61	5GSM congestion re-attempt indicator	5GSM congestion re-attempt
indicator	9.11.4.21	O	TLV	3 7B	Extended protocol configuration options	Extended
protocol configuration options	9.11.4.6	O	TLV-E	4-65538

Table 8.3.15.1.1: PDU SESSION RELEASE COMPLETE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    PDU SESSION RELEASE COMPLETE message identity	Message type	9.7	M	V	1
59	5GSM cause	5GSM cause	9.11.4.2	O	TV	2
7B	Extended protocol configuration options	Extended protocol configuration
options	9.11.4.6	O	TLV-E	4-65538

Table 8.3.16.1.1: 5GSM STATUS message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
    PDU session ID	PDU session identity	9.4	M	V	1
    PTI	Procedure transaction identity	9.6	M	V	1
    5GSM STATUS message identity	Message type	9.7	M	V	1
    5GSM cause	5GSM cause	9.11.4.2	M	V	1

Table D.5.1.1.1: MANAGE UE POLICY COMMAND message content
IEI	IEI	Information Element	Type/Reference	Presence	Format	Length
    PTI	Procedure transaction identity	9.6	M	V	1
MANAGE UE POLICY COMMAND message identity	UE policy delivery service message type D.6.1
M	V	1			UE policy section management list UE policy section management list
D.6.2	M	LV-E	11-65533


Table D.5.2.1.1: MANAGE UE POLICY COMPLETE message content
IEI	Information Element	Type/Reference	Presence	Format	Length
    PTI	Procedure transaction identity	9.6	M	V	1
    MANAGE UE POLICY COMPLETE message identity	UE policy delivery service message type
D.6.1	M	V	1

Table D.5.3.1.1: MANAGE UE POLICY COMMAND REJECT message content
IEI	IEI	Information Element	Type/Reference	Presence	Format	Length
    PTI	Procedure transaction identity	9.6	M	V	1
MANAGE UE POLICY COMMAND REJECT message identity	UE policy delivery service message
type	D.6.1.	M	V	1			UE policy section management result UE policy section
management result	D.6.3	M	LV-E	11-65533


Table D.5.4.1.1: UE STATE INDICATION message content
IEI	IEI	Information Element	Type/Reference	Presence	Format	Length
    PTI	Procedure transaction identity	9.6	M	V	1
UE STATE INDICATION message identity	UE policy delivery service message type	D.6.1
M	V	1			UPSI list
UPSI list	D.6.4	M	LV-E	9-65531			UE policy classmark	UE policy classmark
D.6.5 M	LV	2-4	41	41	UE OS Id	OS Id	D.6.6	O TLV	18-242



*/
