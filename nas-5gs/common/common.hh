#pragma once
#include "../core.hh"

namespace cmn{
/* 9.11.2.2    EAP message RFC2284 RFC3748 */
extern const field_meta hf_eap;

/* 9.11.2.2    EAP message RFC2284 RFC3748 */
int dissect_eap_msg(dissector d, context* ctx);

/*  9.11.2.1A    DNN */
extern const field_meta hf_dnn;

/*  9.11.2.1A    DNN */
int dissect_dnn(dissector d, context* ctx);

/* 9.10.2.1    Additional information*/
int dissect_additional_inf(dissector d, context* ctx);

/* 9.10.2.1    Additional information*/
extern const element_meta additional_inf;

/* TS 24.008 g10[9] 10.5.7.3 GPRS Timer */
int dissect_gprs_timer(dissector d, context* ctx);

int dissect_gprs_timer2(dissector d, context* ctx); /* 3GPP TS 24.008 g10 10.5.7.4 */
int dissect_gprs_timer3(dissector d, context* ctx); /* TS 24.008 g10 [10] 10.5.7.4a */

int dissect_e212_mcc_mnc(dissector d, context*); // implemented in e212_mcc_mnc.cc
}
