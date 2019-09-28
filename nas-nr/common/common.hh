#pragma once
#include "core.hh"
// ## 9.11.2    Common information elements

namespace cmn{
/* 9.11.2.2    EAP message RFC2284 RFC3748 */
extern const field_meta hf_eap;
extern const element_meta eap_message;
/* 9.11.2.2    EAP message RFC2284 RFC3748 */
int dissect_eap_message(dissector d, context* ctx);

/*  9.11.2.1A    DNN */
extern const field_meta hf_dnn;

/*  9.11.2.1A    DNN */
int dissect_dnn(dissector d, context* ctx);
extern const element_meta dnn;

/* 9.10.2.1    Additional information*/
int dissect_additional_information(dissector d, context* ctx);

/* 9.10.2.1    Additional information*/
extern const element_meta additional_information;

/* TS 24.008 g10[9] 10.5.7.3 GPRS Timer */
int dissect_gprs_timer_set(dissector d, context* ctx);

int dissect_gprs_timer2_set(dissector d, context* ctx); /* 3GPP TS 24.008 g10 10.5.7.4 */
int dissect_gprs_timer3_set(dissector d, context* ctx); /* TS 24.008 g10 [10] 10.5.7.4a */

int dissect_e212_mcc_mnc(dissector d, context*); // implemented in e212_mcc_mnc.cc

extern const field_meta hf_5gmm_registration_status;
extern const field_meta hf_emm_registration_status;

int dissect_n1_to_s1_mode_container(dissector d, context* ctx); // 9.11.2.7

int dissect_s1_to_n1_mode_container(dissector d, context*ctx);// 9.11.2.9

int dissect_intra_n1_mode_container(dissector d, context* ctx);// 9.11.2.6

// S-NSSAI   9.11.2.8
int dissect_s_nssai(dissector d, context* ctx);
extern const element_meta s_nssai;
extern const v_string     enc_algo_type_values[];
}

namespace cmn {
extern const field_meta hf_authentication_code;
extern const field_meta hf_sequence_no;
extern const field_meta hf_integrity_algo_type;
extern const field_meta hf_ciphering_algo_type;
extern const field_meta hf_ksi_5g;
extern const field_meta hf_security_context_type;
extern const field_meta hf_kacf;
extern const field_meta hf_next_hop_chaining_counter;

extern const true_false_string tfs_ue_status_n1_mode;
extern const true_false_string tfs_emm_registration_status;
} // namespace cmn
