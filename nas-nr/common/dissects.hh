#include "dissector.hh"
struct context;
struct dissector;

struct nmm_header_t;
struct nsm_header_t;

struct authentication_request_t;

int dissect_nmm_header(dissector d, context* ctx, nmm_header_t* ret);
int dissect_nsm_header(dissector d, context* ctx, nsm_header_t* ret);

// using dissect_f_t = int (*)(dissector, context*, void*);

int dissect_registration_request(dissector d, context* ctx, void* ret);
int dissect_registration_accept(dissector d, context*ctx, void*ret);
int dissect_registration_complete(dissector d, context*ctx, void*ret);
int dissect_registration_reject(dissector d, context*ctx, void*ret);
int dissect_deregistration_request_ue_origin(dissector d, context*ctx, void*ret);
int dissect_deregistration_accept_ue_origin(dissector d, context*ctx, void*ret);
int dissect_deregistration_request_ue_terminate(dissector d, context*ctx, void*ret);
int dissect_deregistration_accept_ue_terminate(dissector d, context*ctx, void*ret);
int dissect_service_request(dissector d, context*ctx, void*ret);
int dissect_service_reject(dissector d, context*ctx, void*ret);
int dissect_service_accept(dissector d, context*ctx, void*ret);
int dissect_configuration_update_command(dissector d, context*ctx, void*ret);
int dissect_configuration_update_complete(dissector d, context*ctx, void*ret);
int dissect_authentication_request(dissector                 d,
                                   context*                  ctx,
                                   authentication_request_t* ret);
int dissect_authentication_response(dissector d, context*ctx, void*ret);
int dissect_authentication_reject(dissector d, context*ctx, void*ret);
int dissect_authentication_failure(dissector d, context*ctx, void*ret);
int dissect_authentication_result(dissector d, context*ctx, void*ret);
int dissect_identity_request(dissector d, context*ctx, void*ret);
int dissect_identity_response(dissector d, context*ctx, void*ret);
int dissect_security_mode_command(dissector d, context*ctx, void*ret);
int dissect_security_mode_complete(dissector d, context*ctx, void*ret);
int dissect_security_mode_reject(dissector d, context*ctx, void*ret);
int dissect_nmm_status(dissector d, context*ctx, void*ret);
int dissect_notification(dissector d, context*ctx, void*ret);
int dissect_notification_response(dissector d, context*ctx, void*ret);
int dissect_ul_nas_transport(dissector d, context*ctx, void*ret);
int dissect_dl_nas_transparent(dissector d, context*ctx, void*ret);
int dissect_pdu_session_establishment_request(dissector d, context*ctx, void*ret);
int dissect_pdu_session_establishment_accept(dissector d, context*ctx, void*ret);
int dissect_pdu_session_establishment_reject(dissector d, context*ctx, void*ret);
int dissect_pdu_session_authentication_command(dissector d, context*ctx, void*ret);
int dissect_pdu_session_authentication_complete(dissector d, context*ctx, void*ret);
int dissect_pdu_session_modification_request(dissector d, context*ctx, void*ret);
int dissect_pdu_session_modification_reject(dissector d, context*ctx, void*ret);
int dissect_pdu_session_modification_command(dissector d, context*ctx, void*ret);
int dissect_pdu_session_modification_complete(dissector d, context*ctx, void*ret);
int dissect_pdu_session_modification_command_reject(dissector d, context*ctx, void*ret);
int dissect_pdu_session_release_request(dissector d, context*ctx, void*ret);
int dissect_pdu_session_release_reject(dissector d, context*ctx, void*ret);
int dissect_pdu_session_release_command(dissector d, context*ctx, void*ret);
int dissect_pdu_session_release_complete(dissector d, context*ctx, void*ret);
int dissect_nsm_status(dissector d, context*ctx, void*ret);

int dissect_registration_request(dissector d, context* ctx, void* ret);
int dissect_registration_accept(dissector d, context* ctx, void* ret);
int dissect_registration_complete(dissector d, context* ctx, void* ret);
int dissect_registration_reject(dissector d, context* ctx, void* ret);
int dissect_authentication_failure(dissector d, context* ctx, void* ret);
int dissect_deregistration_request_ue_orig(dissector d, context* ctx, void* ret);
int dissect_deregistration_accept_ue_orig(dissector d, context* ctx, void* ret);
int dissect_deregistration_request_ue_term(dissector d, context* ctx, void* ret);
int dissect_deregistration_accept_ue_term(dissector d, context* ctx, void* ret);
int dissect_service_request(dissector d, context* ctx, void* ret);
int dissect_service_reject(dissector d, context* ctx, void* ret);
int dissect_service_accept(dissector d, context* ctx, void* ret);
int dissect_configuration_update_command(dissector d, context* ctx, void* ret);
int dissect_configuration_update_complete(dissector d, context* ctx, void* ret);
int dissect_authentication_request(dissector d, context* ctx, void* ret);
int dissect_authentication_response(dissector d, context* ctx, void* ret);
int dissect_authentication_reject(dissector d, context* ctx, void* ret);
int dissect_authentication_failure(dissector d, context* ctx, void* ret);
int dissect_authentication_result(dissector d, context* ctx, void* ret);
int dissect_identity_request(dissector d, context* ctx, void* ret);
int dissect_identity_response(dissector d, context* ctx, void* ret);
int dissect_security_mode_command(dissector d, context* ctx, void* ret);
int dissect_security_mode_complete(dissector d, context* ctx, void* ret);
int dissect_security_mode_reject(dissector d, context* ctx, void* ret);
int dissect_nmm_status(dissector d, context* ctx, void* ret);
int dissect_notification(dissector d, context* ctx, void* ret);
int dissect_notification_response(dissector d, context* ctx, void* ret);
int dissect_ul_nas_transport(dissector d, context* ctx, void* ret);
int dissect_dl_nas_transport(dissector d, context* ctx, void* ret);
