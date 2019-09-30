#pragma once
#include "core.hh"
// ## 9.11.2    Common information elements

/* 9.11.2.2    EAP message RFC2284 RFC3748 */

/* 9.11.2.2    EAP message RFC2284 RFC3748 */
int dissect_eap_message(dissector d, context* ctx);

/*  9.11.2.1A    DNN */
int dissect_dnn(dissector d, context* ctx);
extern const element_meta dnn;

/* 9.10.2.1    Additional information*/
int dissect_additional_information(dissector d, context* ctx);

/* 9.10.2.1    Additional information*/
extern const element_meta additional_information;
extern const element_meta s_nssai;

/* TS 24.008 g10[9] 10.5.7.3 GPRS Timer */
int dissect_gprs_timer_set(dissector d, context* ctx);

int dissect_gprs_timer2_set(dissector d, context* ctx); /* 3GPP TS 24.008 g10 10.5.7.4 */
int dissect_gprs_timer3_set(dissector d, context* ctx); /* TS 24.008 g10 [10] 10.5.7.4a */

int dissect_e212_mcc_mnc(dissector d, context*); // implemented in e212_mcc_mnc.cc

int dissect_n1_to_s1_mode_container(dissector d, context* ctx); // 9.11.2.7

int dissect_s1_to_n1_mode_container(dissector d, context*ctx);// 9.11.2.9

int dissect_intra_n1_mode_container(dissector d, context* ctx);// 9.11.2.6

int dissect_s_nssai(dissector d, context* ctx);// S-NSSAI   9.11.2.8

inline const octet_field hf_authentication_code = {
    "Message authentication code",
};

inline const uint8_field hf_sequence_no={
    "Sequence number",
    0x00u,
};