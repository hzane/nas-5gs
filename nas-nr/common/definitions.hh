#pragma once
#include <cstdint>
#include <optional>
#include <variant>
#include <vector>

#include "nas.hh"
struct packet;
struct context;

using string  = std::string;
using octet_t = std::vector< uint8_t >;

using octet_2 = uint8_t[2];
using octet_3 = uint8_t[3];
using octet_4 = uint8_t[4];
using octet_6 = uint8_t[6];
using octet_8 = uint8_t[8];
using octet_7 = uint8_t[7];
using octet_b = uint8_t[11];
using octet_c = uint8_t[12];
using octet_d = uint8_t[13];
using octet_e = uint8_t[14];
using octet_g = uint8_t[16];
using octet_h = uint8_t[17];
using octet_c                                   = uint8_t[12];

using uint24_t = uint32_t;
using uint48_t = uint64_t;

using bit_1 = uint8_t;
using bit_2 = uint8_t;
using bit_3 = uint8_t;
using bit_4 = uint8_t;
using bit_7 = uint8_t;
using bit_6 = uint8_t;
using bit_5 = uint8_t;
using bit_a = uint16_t;
using bit_b = uint16_t;

template < typename element_t >
struct opt_t {
    bool      present = false;
    element_t v       = {};
};

struct nmm_header_t {
    uint8_t epd;                      // 9.2	Extended protocol discriminator
    uint8_t security_header_type : 4; /*9.3*/
    uint8_t spare : 4;                /*9.5*/
    uint8_t message_type;             /*9.7*/
};

struct nsm_header_t {
    uint8_t epd;            // 9.2	Extended protocol discriminator
    uint8_t pdu_session_id; /*9.4*/
    uint8_t pti;            /*procedure transaction identity 9.6*/
    uint8_t message_type;   /* 9.7*/
};

// Extended protocol discriminator
namespace epd {
inline const uint8_t nmm = 0x7eu;
inline const uint8_t nsm = 0x2eu;
} // namespace epd

struct nas_message_t;
struct nas_message_plain_t;
struct nas_message_protected_t;
struct nsm_message_t;
struct nmm_message_t;

struct authentication_request_t;
struct authentication_response_t;
struct authentication_result_t;
struct authentication_failure_t;
struct authentication_reject_t;

struct registration_request_t;
struct registration_accept_t;
struct registration_complete_t;
struct registration_reject_t;

struct ul_nas_transport_t;
struct dl_nas_transport_t;

struct deregistration_request_t;
struct deregistration_accept_t;
struct deregistration_request_t;
struct deregistration_accept_t;
struct deregistration_request_ue_orig_t;
struct deregistration_request_ue_term_t;
struct deregistration_accept_ue_orig_t;
struct deregistration_accept_ue_term_t;

struct service_request_t;
struct service_accept_t;
struct service_reject_t;

struct configuration_update_command_t;
struct configuration_update_complete_t;

struct identity_request_t;
struct identity_response_t;

struct notification_t;
struct notification_response_t;

struct s1_ue_network_capability_t;

struct security_mode_command_t;
struct security_mode_complete_t;
struct security_mode_reject_t;

struct nmm_status_t;

struct nmm_message_t {
    nmm_header_t                                       header;

    std::shared_ptr< authentication_request_t >        authentication_request;
    std::shared_ptr< authentication_response_t >       authentication_response;
    std::shared_ptr< authentication_result_t >         authentication_result;
    std::shared_ptr< authentication_failure_t >        authentication_failure;
    std::shared_ptr< authentication_reject_t >         authentication_reject;
    std::shared_ptr< registration_request_t >          registration_request;
    std::shared_ptr< registration_accept_t >           registration_accept;
    std::shared_ptr< registration_complete_t >         registration_complete;
    std::shared_ptr< registration_reject_t >           registration_reject;
    std::shared_ptr< ul_nas_transport_t >              ul_nas_transport;
    std::shared_ptr< dl_nas_transport_t >              dl_nas_transport;
    std::shared_ptr< deregistration_request_t >        deregistration_request;
    std::shared_ptr< deregistration_accept_t >         deregistration_accept;
    std::shared_ptr< deregistration_request_ue_orig_t >        deregistration_request_ue_orig;
    std::shared_ptr< deregistration_accept_ue_orig_t >         deregistration_accept_ue_orig;
    std::shared_ptr< deregistration_request_ue_term_t >        deregistration_request_ue_term;
    std::shared_ptr< deregistration_accept_ue_term_t >         deregistration_accept_ue_term;
    std::shared_ptr< service_request_t >               service_request;
    std::shared_ptr< service_accept_t >                service_accept;
    std::shared_ptr< service_reject_t >                service_reject;
    std::shared_ptr< configuration_update_command_t >  configuration_update_command;
    std::shared_ptr< configuration_update_complete_t > configuration_update_complete;
    std::shared_ptr< identity_request_t >              identity_request;
    std::shared_ptr< identity_response_t >             identity_response;
    std::shared_ptr< notification_t >                  notification;
    std::shared_ptr< notification_response_t >         notification_response;
    std::shared_ptr< s1_ue_network_capability_t >      s1_ue_network_capability;
    std::shared_ptr< security_mode_command_t >         security_mode_command;
    std::shared_ptr< security_mode_complete_t >        security_mode_complete;
    std::shared_ptr< security_mode_reject_t >          security_mode_reject;
    std::shared_ptr< nmm_status_t >                    nmm_status;
};
// sm message

struct pdu_session_establishment_request_t;
struct pdu_session_establishment_accept_t;
struct pdu_session_establishment_reject_t;

struct pdu_session_authentication_command_t;
struct pdu_session_authentication_complete_t;
struct pdu_session_authentication_result_t;

struct pdu_session_modification_request_t;
struct pdu_session_modification_reject_t;
struct pdu_session_modification_command_t;
struct pdu_session_modification_complete_t;
struct pdu_session_modification_command_reject_t;

struct pdu_session_release_request_t;
struct pdu_session_release_reject_t;
struct pdu_session_release_command_t;
struct pdu_session_release_complete_t;

struct nsm_status_t;

struct nsm_message_t {
    nsm_header_t header;

    std::shared_ptr< pdu_session_establishment_request_t > pdu_session_establishment_request;
    std::shared_ptr< pdu_session_establishment_accept_t >  pdu_session_establishment_accept;
    std::shared_ptr< pdu_session_establishment_reject_t >  pdu_session_establishment_reject;

    std::shared_ptr< pdu_session_authentication_command_t > pdu_session_authentication_command;
    std::shared_ptr< pdu_session_authentication_complete_t >
                                                      pdu_session_authentication_complete;
    std::shared_ptr< pdu_session_authentication_result_t > pdu_session_authentication_result;

    std::shared_ptr< pdu_session_modification_request_t >  pdu_session_modification_request;
    std::shared_ptr< pdu_session_modification_reject_t >   pdu_session_modification_reject;
    std::shared_ptr< pdu_session_modification_command_t >  pdu_session_modification_command;
    std::shared_ptr< pdu_session_modification_complete_t > pdu_session_modification_complete;
    std::shared_ptr< pdu_session_modification_command_reject_t >
        pdu_session_modification_command_reject;

    std::shared_ptr< pdu_session_release_request_t >  pdu_session_release_request;
    std::shared_ptr< pdu_session_release_reject_t >   pdu_session_release_reject;
    std::shared_ptr< pdu_session_release_command_t >  pdu_session_release_command;
    std::shared_ptr< pdu_session_release_complete_t > pdu_session_release_complete;
    std::shared_ptr< nsm_status_t >                   nsm_status;
};

// ies
using nmm_cause_t                               = uint8_t;
using authentication_parameter_failure_t        = uint8_t[14];
using octet_g                                   = uint8_t[16];
using dnn_t                                     = octet_t;
using eap_t                                     = octet_t;
using drx_parameters                            = bit_4;
using nid_type_t                                = bit_3;
using nregistration_type_t                      = bit_3;
using access_type_t                             = bit_2;
using daylight_saving_time_t                    = bit_2;
using imeisv_request_t                          = bit_3;
using payload_container_type_t                  = bit_4;
using request_type_t                            = bit_3;
using service_type_t                            = bit_4;
using sms_indication_t                          = bit_1;
using ma_pdu_session_information_t              = bit_4;
using allowed_ssc_mode_t                        = bit_3;
using supported_packet_filters_maximum_number_t = bit_b;
using pdu_session_type_t                        = bit_3;
using ssc_mode_t                                = bit_3;
using nsm_network_feature_support_t             = bit_1;
using nsm_congestion_reattempt_indicator_t      = bit_1;
using control_plane_only_indication_t           = bit_1;
using nssai_includion_mode_t                    = bit_2;
using payload_container_t                       = octet_t;
using abba_t                                    = octet_t;
using allowed_pdu_session_status_t              = octet_2;
using authentication_parameter_rand_t           = octet_g;
using authentication_response_parameter_t       = octet_t;
using eps_nas_message_t                         = octet_t;
using sm_pdu_dn_request_container_t             = octet_t;
using atsss_container_t                         = octet_t;
using pdu_session_identity_2_t                  = uint8_t;
using time_zone_t                               = uint8_t;
using nsm_cause_t                               = uint8_t;
using bit_b                                     = uint16_t;
using serving_plmn_rate_control_t               = uint16_t;
using nas_message_container_t                   = nas_message_t;

struct intra_n1_mode_container_t;
struct n1_mode_to_s1_mode_container_t;
struct s_nssai_t;
struct s1_mode_to_n1_mode_container_t;
struct nmm_capability_t;

struct mcc_mnc_t;

struct guti_nmid_t;
struct imeisv_nmid_t;
struct suci_nmid_t;
struct stmsi_nmid_t;
struct noid_nmid_t;
struct mac_nmid_t;
struct nmid_t;
using nmobile_id_t = nmid_t;

struct nnetwork_feature_support_t;
struct nregistration_result_t;


struct ntracking_area_id_t;
struct ntai_list_00_t;
struct ntai_list_01_t;
struct ntai_list_10_t;
struct ntracking_area_id_list_t;

struct nupdate_type_t;
struct additional_5g_security_inforation_t;
struct configuration_update_indication_t;
struct deregistration_type_t;
struct emergency_number_list_t;
struct eps_nas_security_algorighms_t;
struct extened_emergency_number_list_t;
struct ladn_indication_t;
struct ladn_information_t;
struct mico_indication_t;
struct nas_key_set_identifier_t;
struct nas_security_algorithm_t;
struct network_name_t;
struct network_slicing_indication_t;
struct nssai_t;

struct operator_defined_access_category_definition_t;
struct payload_container_multiple_t;
struct pdu_session_reactivation_result_t;
struct pdu_session_reactivation_result_error_cause_t;
struct pdu_session_status_t;
struct plmn_list_t;
struct rejected_nssai_t;
struct s1_ue_network_capability_t;
struct service_area_00_t;
struct service_area_01_t;
struct service_area_10_t;
struct service_area_11_t;
struct service_area_t;
struct service_area_list_t;

struct sor_transparent_container_0_t;
struct sor_transparent_container_1_t;
struct time_zone_time_t;
struct ue_parameter_update_container_0_t;
struct ue_parameter_update_container_1_t;
struct ue_security_capability_t;
struct ue_usage_setting_t;
struct ue_status_t;
struct uplink_data_status_t;
struct n3gpp_nw_provided_policies_t;
struct eps_bearer_context_status_t;
struct extended_drx_parameters_t;
struct mobile_station_classmark2_t;
struct supported_codec_list_t;
struct nsm_capability_t;
struct always_on_pdu_session_indication_t;
struct always_on_pdu_session_requested_t;
struct extended_pco_t;
struct integrity_protection_maximum_data_rate_t;
struct mapped_eps_bearer_contexts_t;
struct pdu_address_t;
struct qos_flow_descriptions_t;
struct qos_rule_t;
struct qos_rules_t;
struct session_ambr_t;
struct reattempt_indicator_t;
struct session_tmbr_t;
