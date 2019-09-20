#pragma once
#include <cstdint>
#include <optional>
#include <variant>
#include <vector>
#include "config.hh"
#include "field_meta.hh"

template<typename field>
struct field_v{
    const field_meta* meta     = nullptr;
    bool              presence = false;
    int               length   = 0;
    field             field    = {};
};

using additional_info = std::vector< uint8_t >;

using dnn = string;

struct mcc_mnc {
    const v_string mcc;
    const v_string mnc;
};

using eap = string;

struct gprs_timer {
    uint8_t         val;
    v_string        unit;
};

using gprs_timer2 = gprs_timer;
using gprs_timer3 = gprs_timer;

using authentication_code = uint32_t;
using nibble = uint8_t;
using bit3 = uint8_t;
using bit1 = uint8_t;
using bit7 = uint8_t;
using bit2 = uint8_t;

struct intra_n1_mode_container {
    authentication_code auth_code;
    nibble             integrity_protected_algo_type;
    nibble              ciphering_algo_type;
    bit3                ksi;
    bool                tsc;
    bool                kacf;
    uint8_t             sequence_no;
};

// 9.11.2.7 N1 mode to S1 mode NAS transparent container
struct n1_to_s1_container {
    uint8_t sequence_no;
};

using uint24_t = uint32_t;

using std::optional;

// S-NSSAI   9.11.2.8
struct s_nssai{
    uint8_t   slice_service_type;
    optional< uint24_t > slice_differentiator;
    optional< uint8_t > mapped_configured_sst;
    optional< uint8_t > mapped_configured_sd;
};


struct s1_to_n1_container {
    authentication_code auth_code;
    nibble              integrity_protected_algo_type;
    nibble              ciphering_algo_type;
    bit3                ksi;
    bool                tsc;
    bool                ncc;
};

// 9.11.3.2	5GMM cause
using mm_cause = v_string;

struct mm_capability {
    bool             service_gap_control;
    bool             header_compression_for_control_plane;
    bool             n3data;
    bool             control_plane;
    bool             restrict_ec;
    bool             lte_positioning_protocol;
    bool             handover_attach;
    bool             s1_mode;
    optional< bool > sr_vcc;
    optional< bool > user_plane;
};

struct mm_status {
    mm_cause mm_cause;
};

/* * 9.11.3.3 5GS identity type */
using identity_type = v_string;

struct mobile_id_none {
    bool odd_even;
    bit3 type_id; // = 0
};

using imei = std::vector<uint8_t>;

struct mobile_id_imei {
    bool odd_even;
    bit3 type_id;
    imei imei;
};
using mobile_id_imeisv = mobile_id_imei;

using uint48_t = uint64_t;

struct mobile_id_mac {
    bit3 type_id;  // = 6
    uint48_t mac;
};

struct mobile_id_guti{
    bit3     type_id;
    mcc_mnc  mcc_mnc;
    bit10    amf_region_id;
    bit6     amf_pointer;
    uint32_t tmsi;
};

using suci_nai = std::vector<uint8_t>;

using scheme_null = std::vector< uint8_t >;

using scheme_output = std::vector< uint8_t >;

struct supi_format_0 {
    mcc_mnc                                    mcc_mnc;
    uint16_t                                   routing_indication;
    v_string                                   protection_scheme_id;
    uint8_t                                    public_key_identifier;
    std::variant< scheme_null, scheme_output > scheme_output;
};

struct mobile_id_suci {
    bit3     type_id; // = 1
    v_string                supi_format_type;
    optional< supi_format_0 > supi_format_0;
    optional< suci_nai >  suci_nai;
};

using bit6 = uint8_t;
using bit10 = uint16_t;

struct mobile_id_s_tmsi {
    bit3     type_id;    // = 4
    bit10    amf_set_id; //
    bit6     amf_pointer;
    uint32_t tmsi;
};

// 5GS mobile identity - 5G-GUTI

using mobile_id = std::variant< mobile_id_none,
                                mobile_id_suci,
                                mobile_id_guti,
                                mobile_id_imei,
                                mobile_id_s_tmsi,
                                mobile_id_imeisv,
                                mobile_id_mac >;


struct network_feature_support{
    bool mpsi;
    bool ims_iwk;
    bool ims_emf;
    bool ims_emc;
    bool ims_vops;
};

namespace sm {
struct max_data_rate_t {};
struct uplink_integrity_protection_max_data_rate_t : max_data_rate_t {};
struct downlink_integrity_protection_max_data_rate_t : max_data_rate_t {};

struct nrsm_cause_t {};

struct ssc_mode_t {};
struct eps_bearer_content_t {
    uint8_t operation_code;
    uint8_t ebit;
    uint8_t deb;
};
struct gprs_timer3_t {};
struct ssc_mode_t {};
struct ssc_mode_1_t : ssc_mode_t  {};
struct ssc_mode_2_t : ssc_mode_t {};
struct ssc_mode_3_t : ssc_mode_t {};

struct extended_pco_t {};
struct congestion_reattempt_t {};
struct nrsm_cause_t {};
struct eap_message_t {};

struct pdu_session_establishment_reject_t {
    uint8_t                cause;
    gprs_timer3_t          backoff_timer;
    ssc_mode_t             allowed;
    eap_message_t          eap_message;
    extended_pco_t         extended_pco;
    congestion_reattempt_t congestion_reattempt;
};

struct nrsm_cause_t {};
struct extended_pco_t {};
struct authorized_qos_rules_t {};
struct qos_rules_t {};
struct mapped_eps_bearer_context_t {};
struct bearer_context_t {};
struct backoff_timer_t {};
struct gprs_timer3_t {};
struct nrsm_capability_t {};
struct max_supported_packet_filters_t {};
struct session_ambr_t {};
struct ambr_t {};
struct rq_gprs_timer_t {};
struct alwayson_pdu_session_indication_t {};
struct pdu_session_indication_t {};
struct congestion_reattempt_t {};
struct pdu_session_type_t {};
struct selected_pdu_session_type_t {};
struct pdu_address_t {};
struct max_data_rate_t {};
struct integrity_protection_max_data_rate_t {};
struct ssc_mode_t {};
struct pdu_dn_request_container_t {};
struct requested_qos_rules_t {};
struct qos_rules_t {};
struct authorized_qos_flow_description_t {};
struct qos_flow_description_t {};
struct request_qos_flow_description_t {};
struct control_plane_only_indication_t {};

} // namespace sm

namespace mm{
struct imeisv_mobile_id_t {};
struct pdu_session_status_t {};
struct rejected_nssai_t {};
struct tracking_area_id_list_t {};
struct allowed_nssai_t {};
struct nssai_t {};
struct eps_bearer_context_status_t {};
struct nas_message_container_t {};
struct nas_ksi_t {};
struct request_type_t {};
struct old_pud_session_id_t {};
struct pdu_session_id_t {};
struct uplink_data_status_t {};
struct data_status_t {};
struct downlink_data_status_t {};
struct s_tmsi_t {};
struct pdu_session_reactive_result_error_t {};
struct pdu_session_reactivation_result_t {};
struct replayed_s1_ue_security_capability_t {};
struct additional_security_information_t {};
struct selected_eps_security_algo_t {};
struct eps_security_algorithm_t {};
struct imeisv_request_t {};
struct imeisv_t {};
struct replayed_ue_security_capability_t {};
struct plmn_list_t {};
struct plmn_t {};
struct gprs_timer3 {};
struct backoff_gprs_timer3 {};
struct pdu_session_id_t {};
struct mobile_id_t {};
struct configured_nssai_t {};
struct timezone_time_t {};
struct sms_indication_t {};
struct operator_defined_access_category_t {};
struct local_timezone_t {};
struct network_name {};
struct short_network_name {};
struct full_network_name {};
struct daylight_saving_time_t {};
struct configure_update_indication_t {};
struct authentication_response_parameter_t {};
struct authentication_parameter_autn {};
struct authentication_parameter_rand_t {};
struct authentication_failure_parameter_t {};
struct registration_result_t {};
struct n3gpp_network_provided_policies_t {};
struct negotiated_drx_parametereter_t {};
struct operator_defined_acd_t {};
struct nssai_inclusion_mode_t {};
struct eap_message_t {};
struct sor_transparent_container_t {};
struct extended_emergency_number_list_t {};
struct emergency_number_list_t {};
struct t3502_t {};
struct gprs_timer2_t {};
struct n3g_deregistration_timer_t {};
struct t3512_t {};
struct service_area_list_t {};
struct ladn_information_t {};
struct guti_mobile_id_t {};
struct requested_nssai_t {};
struct mico_indication_t {};
struct requested_drx_parametereter_t {};
struct update_type_t {};
struct payload_container_type_t {};
struct aguti_mobile_id_t {};
struct allowed_pdu_session_status_t {};
struct pdu_session_status_t {};
struct ue_usage_setting_t{};
struct s1_ue_network_capability_t {};
struct ue_security_capability_t {};
struct ladn_indication_t {};
struct payload_container_t {};
struct nc_native_nas_ksi_t {};
struct nas_ksi_t {};
struct last_visited_tai_t {};
struct tracking_area_id_t {};
struct ue_status_t {};
struct eps_nas_message_container_t {};
struct nrmm_cause_t {};
struct nrmm_capability_t {};
struct network_feature_support_t {};
struct network_slicing_indication_t {};
struct abba_t {};
} // namespace mm

namespace cmn{
struct none_t {};
struct decimal_t {};

template<size_t N>
struct octet_t {
    std::array< uint8_t, N > _;
};


} // namespace cmn
