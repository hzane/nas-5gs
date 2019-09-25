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

namespace cmn {
struct gprs_timer_t {};
struct gprs_timer_2_t {};
struct gprs_timer_3_t {};

struct none_t {};
struct decimal_t {};

template < size_t N >
using octet_t = std::array< uint8_t, N >;

template < size_t N = 4 >
struct nibble_t {
    uint8_t _ : N;
};

using additional_information_t = payload_t;
using dnn_t                    = payload_t;
using mcc_mnc_t                = octet_t< 3 >;
using eap_message_t            = payload_t;
using gprs_timer_t             = uint8_t;
using gprs_timer_2_t           = uint8_t;
using gprs_timer_3_t           = uint8_t;
using ciphering_algorithm_t    = uint8_t;
using integrity_algorithm_t    = uint8_t;
using k_amf_change_flag_t      = bool;
using security_context_type_flag_t = bool;

struct intra_n1_mode_container_t {
    oectet_t< 4 >             auth_code;
    nibble_t< 4 >               integrity_algorithm_type;
    nibble_t< 4 >               ciphering_algorithm_type;
    nibble_t< 3 >               nas_ksi;
    bool                        security_context_flag_type;
    bool                        kamf_change_flag;
    uint8_t                     sequence_no;
};

struct n1_to_s1_mode_container_t {
    uint8_t sequence_no;
};

using registration_status_t = bool;

struct s1_to_n1_mode_container_t {
    oectet_t< 4 > auth_code;
    nibble_t< 4 > integrity_algo_type;
    nibble_t< 4 > ciphering_algo_type;
    nibble_t< 3 > nas_ksi;
    bool          security_context_type_flag;
    bool          next_hop_chaining_counter;
};
} // namespace cmn

namespace sm {
struct backoff_timer_t : cmn::gprs_timer_3_t {};
struct rq_timer_t : cmn::gprs_timer_t {};

using packet_filter_type_t = uint8;
using packet_filter_length_t = uint8_t;
using packet_filter_direction_t = nibble_t< 2 >;
using packet_filter_id_t        = nibble_t< 4 >;

using max_data_rate_t = uint16_t;
// struct max_data_rate_t {};
// struct uplink_integrity_protection_max_data_rate_t : max_data_rate_t {};
// struct downlink_integrity_protection_max_data_rate_t : max_data_rate_t {};

struct nrsm_cause_t {};

struct ssc_mode_t {
    inline static const auto meta = &ssc_mode;
    inline static const auto values = ssc_mode_values;
    nibble< 3 >              value;
};
struct eps_bearer_content_t {
    uint8_t operation_code;
    uint8_t ebit;
    uint8_t deb;
};

struct allowed_ssc_mode_t {
    bool mode_1;
    bool mode_2;
    bool mode_3;
};

struct extended_pco_t {};
struct congestion_reattempt_t {};
struct nrsm_cause_t {};
struct eap_message_t {};
struct allowed_ssc_mode_t {};

struct reattempt_indicator_t {
    bool ratc;
    bool eplmnc;
};
// using reattempt_indicator_t = octet_t< 3 >;

struct pdu_session_establishment_reject_t {
    nrms_cause_t                       cause;
    optional< gprs_timer3_t >          backoff_timer;
    optional< allowed_ssc_mode_t >     allowed_ssc_mode;
    optional< eap_message_t >          eap_message;
    optional< extended_pco_t >         extended_pco;
    optional< reattempt_indicator_t >  reattempt_indicator;
    optional< congestion_reattempt_t > congestion_reattempt;
};

struct nrsm_cause_t {};
struct extended_pco_t {};

struct parameter_content_t {};
struct eps_bearer_identity_t {};
struct averaging_window_t {};

struct qos_parameter_t {
    uint8_t id;
    std::variant< qi5_t,
                  ambr_t,
                  averaging_window_t,
                  eps_bearer_identity_t,
                  parameter_content_t >
        content;
};

struct qos_rule_t {};

// 9.11.4.13 QoS rules
struct qos_rules_t {
    inline static const element_meta* meta = &qos_rules;
    std::vector< qos_rule_t >         rules;
};

struct mapped_eps_bearer_context_t {};
struct bearer_context_t {};
struct nrsm_capability_t {};

struct max_supported_packet_filters_t {
    uint8_t number;
    uint8_t c;
};

struct ambr_t {
    uint8_t  unit;
    uint16_t value;
};

// Session-AMBR 9.11.4.14
struct session_ambr_t  {
    inline static const element_meta* meta = session_ambr;
    ambr_t                            downlink;
    ambr_t                            uplink;
};

struct serving_plmn_rate_control_t {
    inline static const element_meta* meta = serving_plmn_rate_control;
    uint16_t                          value;
};

struct alwayson_pdu_session_indication_t {};
struct pdu_session_indication_t {};
struct congestion_reattempt_t {};

// struct pdu_session_type_t {};
using pdu_session_type_t = nibble_t< 4 >;

struct selected_pdu_session_type_t {};
struct pdu_address_t {};
struct max_data_rate_t {};
struct integrity_protection_max_data_rate_t {};
struct ssc_mode_t {};

struct pdu_dn_request_container_t {
    inline static const element_meta* meta = &sm_pdu_dn_request_container;
    inline static const field_meta*   dn_specific_identity = &hf_dn_specific_identity;
    string                      id; // utf-8 string
};
struct requested_qos_rules_t {};

struct qos_flow_description_t {
    uint8_t                        qos_flow_indentity;
    qos_flow_operation_code_t      qos_flow_operation_code;
    nibble_t< 1 >                  ebit;
    nibble_t< 7 >                  number;
    std::vector< qos_parameter_t > parameters;
};

struct authorized_qos_flow_descriptions_t {
    vector< qos_flow_description_t > values;
};

struct request_qos_flow_description_t {};
struct control_plane_only_indication_t {};

} // namespace sm

namespace mm{
struct nssai_t {
    uint8_t                            cause;
    uint8_t                            slice_service_type;
    optional< slice_differentiator_t > sd;
};

using allowed_nssai_t = std::vector< nssai_t >;

using rejected_nssai_t = std::vector< nssai_t >;

using tracking_area_code_t = octet_t< 3 >;

struct tracking_area_id_00_t {
    mcc_mnc_t                           mccmnc;
    std::vector< tracking_area_code_t > code;
};

struct tracking_area_id_01_t {
    mcc_mnc_t mccmnc;
    tracking_area_code_t code;
};

using tracking_area_id_02_t = std::vector< tracking_area_id_01_t >;

struct tracking_area_id_03_t {
    mcc_mnc_t mccmnc;
};

struct tracking_area_identity_t {
    nibble_t< 2 > type;
    nibble_t< 5 > number;
    std::variant< tracking_area_id_00_t,
                  tracking_area_id_01_t,
                  tracking_area_id_02_t,
                  tracking_area_id_03_t >
        value;
};

using tracking_area_identity_list_t = std::vector< tracking_area_identity_t >;

using alwayson_pdu_session_requested = nibble< 1 >;

struct pdu_session_indications_t {};
struct pdu_session_reactivation_result_t : pdu_session_indications_t {};
struct pdu_session_status_t : pdu_session_indications_t {};

using nas_ksi_t = nibble_t< 3 >;

struct eps_bearer_indications_t {};
struct eps_bearer_context_status_t : eps_bearer_indications_t {};

using slice_differentiator_t = octect_t< 3 >;
using slice_service_type_t   = uint8_t;
using follow_on_request_t    = bool;

struct nrmm_capability_t {
    bool                  service_gap_control;
    bool                  header_compression_for_control_plane;
    bool                  n3_data;
    bool                  control_plane;
    bool                  restrict_ec_support;
    bool                  lpp_capability;
    bool                  handover_attach;
    bool                  s1_mode;
    std::optional< bool > nrsr_vcc;
    std::optional< bool > user_plane_nr_optimization;
};

using nrmm_status_t = uint8_t;
using identity_type = nibble_t< 3 >;

struct mobile_id_imseisv_t {
    bool                   odd_even;
    nibble_t< 3 >          type;
    payload_t              imseisv;
};
using supi_nai_t = string;

using scheme_msin_t   = payload_t;
using scheme_output_t = payload_t;

struct supi_imsi_t {
    mcc_mnc_t                                      mccmnc;
    uint16_t                                       routing_indicator;
    uint8_t                                        protection_scheme_id;
    uint8_t                                        public_key_id;
    std::variant< scheme_msin_t, scheme_output_t > scheme;
};
struct mobile_id_suci_t {
    bool                                    odd_even;
    nibble_t< 3 >                           type;
    uint8_t                                 supi_format;
    std::variant< supi_imsi_t, supi_nai_t > supi;
};
struct mobile_id_tmsi_t {
    nibble_t< 3 > type;
    octet_t< 2 >  amf_set_id;
    uint8_t       amf_pointer;
    octet_t< 4 >  tmsi;
};
struct mobile_id_guti_t {
    nibble_t< 3 > type;
    mcc_mnc_t     mccmnc;
    uint8_t       amf_region_id;
    oectet_t< 2 > amf_set_id;
    uint8_t       amf_pointer;
    octet_t< 4 > tmsi;
};
struct mobile_id_imei_t {
    bool                   odd_even;
    nibble_t< 3 >          type;
    payload_t              imei;
};

struct mobile_id_noid_t {
    uint8_t type;
};

struct mobile_id_mac_t {
    nibble_t< 3 > type;
    octet_t< 6 > mac;
};
struct mobile_id_t {
    uint8_t type;
    std::variant< mobile_id_noid_t,
                  mobile_id_suci_t,
                  mobile_id_guti_t,
                  mobile_id_imei_t,
                  mobile_id_tmsi_t,
                  mobile_id_imseisv_t,
                  mobile_id_mac_t >
        id;
};

struct mm_network_feature_support_t {
    bool                  mps_indicator;
    bool                  interworking_without_n26;
    bool                  emergency_fallback_indicator;
    bool                  emergency_support_indicator;
    bool                  ims_voice_over_ps_indicator;
    std::optional< bool > emergency_support_for_n3gpp;
    std::optional< bool > mcs_indicator;
    std::optional< bool > restrict_ec;
    std::optional< bool > nr_control_plane_ciot;
    std::optional< bool > n3data;
    std::optional< bool > hc_cp_ciot;
    std::optional< bool > up_ciot;
};

struct session_tmbr_t {};
struct atsss_container_t {};

struct pdu_session_establishment_accept_t {
    pdu_session_type_t           type;
    ssc_mode_t                   selected;
    qos_rules_t                  authorized_qos_rules;
    session_ambr_t               session_ambr;
    std::optional<nrsm_cause_t>                 cause;
    std::optional<pdu_address_t>                address;
    std::optional<gprs_timer_t>                 rq_timer;
    std::optional<s_nssai_t>                    s_nssai;
    std::optional<pdu_session_indication_t>     alwayson_pdu_session_indication;
    std::optional<mapped_eps_bearer_contexts_t> mapped_eps_bearer_contexts;
    std::optional<eap_message_t>                    eap_message;
    std::optional< qos_flow_description_t >         authorized_qos_flow_description;
    std::optional< extended_pco_t >                 extened_pco;
    std::optional< dnn_t >                          dnn;
    std::optional< network_feature_support_t >      network_feature_support;
    std::optional< session_tmbr_t >                 session_tmbr_t;
    std::optional< serving_plmn_rate_control_t >    serving_plmn_rate_control;
    std::optional< atsss_container_t >              atsss_container;
    std::optional< control_plane_only_indication_t > control_plane_only_indication;
};

using pdu_session_type_t = nibble_t< 3 >;
using alwayson_pdu_session_requested_t = nibble_t< 1 >;

struct pud_session_establishment_request_t {
    max_data_rate_t                               integrity_protection_max_data_rate;
    optional< pdu_session_type_t >                pdu_session_type;
    optional< ssc_mode_t >                        ssc_mode;
    optional< nrsm_capability_t >                 nrsm_capability;
    optional< max_supported_packet_filters_t >    max_supported_packet_filters;
    optional< alwayson_pdu_session_requested_t >  alwayson_pdu_session_requested;
    optional< pdu_dn_request_container_t >        pdu_dn_request_container;
    optional< extended_pco_t >                    extended_pco;
};

struct pdu_session_authentication_result_t {
    eap_message_t              eap_message;
    optional< extended_pco_t > extended_pco;
};

struct pdu_session_authentication_command_t {
    eap_message_t              eap_message;
    optional< extended_pco_t > extended_pco;
};

struct pdu_session_authentication_complete_t {
    eap_message_t            eap_message;
    optional<extended_pco_t> extended_pco;
};

struct ma_pdu_session_information_t {};

using request_type_t = nibble_t< 4 >;

struct uplink_nas_transport_t {
    nibble_t< 4 >                            payload_container_type;
    payload_container_t                      payload_container;
    optional< pdu_session_id_t >             pdu_session_id;
    optional< pdu_session_id_t >             old_pdu_session_id;
    optional< request_type_t >               request_type;
    optional< s_nssai_t >                    s_nssai;
    optional< dnn_t >                        dnn;
    optional< additional_information_t >     additional_information;
    optional< ma_pdu_session_information_t > ma_pdu_session_information;
};

struct imeisv_mobile_id_t {};
struct rejected_nssai_t {};
struct nas_message_container_t {};
struct request_type_t {};
struct old_pud_session_id_t {};
struct pdu_session_id_t {};

// struct uplink_data_status_t {};
using uplink_data_status_t = octet_t< 2 >;

struct ue_parameters_update_transparent_container_t {
    bool data_type;
};

struct data_status_t {};
struct downlink_data_status_t {};
struct s_tmsi_t {};
struct pdu_session_reactive_result_error_t {};
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

// struct timezone_t {};
using timezone_t = uint8_t;

struct timezone_time_t {
    uint8_t yeaer;
    uint8_t month;
    uint8_t mday;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t timezone;
};

struct codec_bitmap_t {
    bool tdma_efr;
    bool umts_amr2;
    bool umts_amr;
    bool hr_amr;
    bool fr_amr;
    bool gsm_efr;
    bool gsm_hr;
    bool gsm_fr;
    optional< bool > umts_evs;
    optional< bool > ohr_amr_wb;
    optional< bool > ofr_amr_wb;
    optional< bool > ohr_arm;
    optional< bool > umts_amr_wb;
    optional< bool > fr_amr_wb;
    optional< bool > pdc_efr;
};

struct supported_codec_t {
    uint8_t system_indentification;
    codec_bitmap_t bitmap;
};
using supported_codec_list_t = std::vector< supported_codec_t >;

using sms_indication_t = bool;
using service_type_t   = uint8_t;

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

struct registration_request_t {
    nibble_t< 4 >                          type;
    nas_ksi_t                              nas_ksi;
    mobile_id_t                            mobile_id;
    optional< nas_ksi >                    native_nas_ksi;
    optional< nrmm_capability_t >          mm_capability;
    optional< ue_security_capability_t >   ue_security_capability;
    optional< nssai_t >                    requested_nssai;
    optional< tracking_area_id_t >         last_visited_tai;
    optional< s1_ue_network_capability_t > s1_ue_network_capability;
};

struct registration_reject_t {
    uint8_t                    mm_cause;
    optional< gprs_timer_3_t > t3346_timer;
    optional< gprs_timer_2_t > t3502_timer;
    optional< eap_message_t >  eap_message;
};

struct registration_complete_t {
    optional< sor_transparent_container_t > container;
};

struct registration_accept_t {
    registration_result_t               result;
    optional< mobile_id >               guti_mobile_id;
    optional< plmn_list_t >             plmn_list;
    optional< tracking_area_id_list_t > tai_list;
    optional< nssai_t >                 allowed_nssai;
    optional< rejected_nssai_t >        rejected_nssai;
    optional< nssai_t >                 configured_nssai;
    optional< network_feature_support_t > network_feature_support;
    optional< pdu_session_status_t >      pdu_session_status;
    optional< pdu_session_reactivation_result_t > pdu_session_reactivation_result;
    optional< pdu_session_reactivation_result_error_cause_t > error_cause;
    optional< ladn_information_t >                            ladn_information;
    optional< nibble_t< 4 > >                                 mico_indication;
    optional< nibble_t< 4 > >                                 network_slicing_indication;
    optional< service_area_list_t >                           service_area_list;
    optional< gprs_timer_3_t >                                t3512_timer;
    optional< gprs_timer_2_t >                                n3_deregistration_timer;
    optional< gprs_timer_2_t >                                t3502_timer;
    optional< emergency_number_list_t >                       emergency_number_list;
    optional< extended_emergency_number_list_t > extended_emergency_number_list;
    optional< sor_transparent_container_t >      sor_container;
    optional< eap_message_t >                    eap_message;
};

struct registration_result_t {};

struct n3gpp_network_provided_policies_t {};
struct negotiated_drx_parametereter_t {};
struct operator_defined_acd_t {};
struct nssai_inclusion_mode_t {};
struct eap_message_t {};

struct sor_plmnid_list_t {
    mcc_mnc_t mccmnc;
    uint8_t   access_technology_identifier_1;
    uint8_t   access_technology_identifier_2;
};
struct sor_mac_iausf_t {
    uint8_t sor_header;
    sor_mac_iausf_t sor_mac_iausf;
    uint16_t        counter;
    std::variant< sor_secured_packet_t, sor_plmnid_list_t > item;
};
struct sor_mac_iue_t {
    uint8_t       header;
    octet_t< 16 > iue;
};
using sor_transparent_container_t = std::variant< sor_mac_iausf_t, sor_mac_iue_t >;

struct extended_emergency_number_list_t {};
struct emergency_number_list_t {};
struct t3502_t {};
struct gprs_timer2_t {};
struct n3g_deregistration_timer_t {};
struct t3512_t {};

struct service_area_00_t {
    mcc_mnc_t mccmnc;
    std::vector< octet_t< 3 > > tracking_area_code;
};
struct service_area_01_t {
    mcc_mnc_t mccmnc;
    octet_t< 3 > tracking_area_code;
};
using service_area_10_t = std::vector< service_area_01_t >;

struct service_area_11_t {
    mcc_mnc_t mccmnc;
};

struct service_area_t {
    bool          allowed_type;
    nibble_t< 2 > list_type;
    nibble_t< 5 > number;
    std::variant< service_area_00_t,
                  service_area_01_t,
                  service_area_10_t,
                  service_area_11_t >
        value;
};
struct service_area_list_t {
    std::vector< service_area_t > value;
};

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

// struct ue_usage_setting_t{    bool value;};
using ue_usage_setting_t = bool;

struct s1_ue_network_capability_t {};
struct ue_security_capability_t {};
struct ladn_indication_t {};
struct payload_container_t {};
struct nc_native_nas_ksi_t {};
struct nas_ksi_t {};
struct last_visited_tai_t {};

struct tracking_area_id_t {};


struct ue_status_t {
    bool nmm_registration_status;
    bool emm_registration_status;
};

struct eps_nas_message_container_t {};

using nrmm_cause_t = uint8_t;

struct network_feature_support_t {};
struct network_slicing_indication_t {};
struct abba_t {};
} // namespace mm

struct nrmm_unknown_t {};
struct nrms_unknown_t {};

struct service_reject_t {
    nrmm_cause_t                     cause;
    optional< pdu_session_status_t > pdu_session_status;
    optional< gprs_timer_2_t >       t3346_timer;
    optional< eap_message_t >        eap_message;
    optional< grps_timer_3_t >       t3348_timer;
};

struct service_request_t {
    nibble_t< 4 >                            nas_ksi;
    nibble_t< 4 >                            service_type;
    s_tmsi_t                                 s_tmsi;
    optional< uplink_data_status_t >         uplink_data_status;
    optional< pdu_session_status_t >         pdu_session_status;
    optional< allowed_pdu_session_status_t > allowed_pdu_session_status;
    optional< payload_t >                    container;
};

struct pdu_session_reactivation_result_error_cause_t {};
struct pdu_session_reactivation_result_t {};
struct service_accept_t {
    optional< pdu_session_status_t >              pdu_session_status;
    optional< pdu_session_reactivation_result_t > pdu_session_reactivation_result;
    optional< pdu_session_reactivation_result_error_cause_t > error_cause;
    optional< eap_message_t >                                 eap_message;
    optional< gprs_timer3 >                                   t3348;
};

struct security_mode_reject_t {
    nrmm_cause_t cause;
};

struct security_mode_complete_t {
    optional< mobile_id_t > imeisv;
    optional< eap_message_t > eap_message;
};

struct security_mode_command_t {
    security_algorithm_t    algo;
    nas_ksi_t               nas_ksi;
    security_capabilities_t replayed_ue_security_capabilities;
    optional< nibble_t< 4 > >                     imeisv_request;
    optional< security_algorithm_t >              selected_eps_security_algo;
    optional< additional_security_information_t > additional;
    optional< eap_message_t >                     eap_message;
    optional< abba_t >                            abba;
    optional< security_capabilities_t >           replayed_s1_ue_security_capability;
};

struct ue_security_capability_t {
    uint8_t nea;
    uint8_t nia;
    uint8_t eea;
    uint8_t eia;
};
using replayed_ue_security_capability_t = ue_security_capability_t;

struct s1_ue_network_capability_t {
    uint8_t eea;
    uint8_t eia;
    uint8_t uea;
    uint8_t uia;
};
using reported_ue_network_capability_t = s1_ue_network_capability_t;

struct nrmm_message_t {
    uint8_t extended_protocol_discriminator;
    nibble_t< 4 > security_header_type;
    uint8_t       message_type;
    std::variant< nrmm_unknown_t,
                  registration_request_t,
                  registration_accept_t,
                  registration_complete_t,
                  registration_reject_t,
                  deregistration_request_ue_origin_t,
                  deregistration_request_ue_terminate_t,
                  deregistration_accept_ue_origin_t,
                  deregistration_accept_ue_terminate_t,
                  service_request_t,
                  service_reject_t,
                  service_accept_t,
                  configuration_update_command_t,
                  configuration_update_complete_t,
                  authentication_request_t,
                  authentication_response_t,
                  authentication_reject_t,
                  authentication_failure_t,
                  authentication_result_t,
                  identity_request_t,
                  identity_response_t,
                  security_mode_command_t,
                  security_mode_complete_t,
                  security_mode_reject_t,
                  mm_status_t,
                  notification_t,
                  notification_response_t,
                  ul_nas_transparent_container_t,
                  dl_nas_transparent_container_t >
        ie;
};

struct pdu_session_modification_command_reject_t {
    optional< nrsm_cause_t >   cause;
    optional< extended_pco_t > extended_pco;
};

struct pdu_session_modification_command_t {
    optional< nrsm_cause_t >                 cause;
    optional< session_ambr_t >               session_ambr;
    optional< gprs_timer_t >                 rq_timer;
    optional< pdu_session_indication_t >     pdu_session_indication;
    optional< qos_rules_t >                  authorized_qos_rules;
    optional< mapped_eps_bearer_contexts_t > mapped_eps_bearer_contexts;
    optional< qos_flow_description_t >       authorized_qos_flow_description;
    optional< extended_pco_t >               extended_pco;
    optional< session_tmbr_t >               session_tmbr;
};

struct pdu_session_modification_complete_t {
    optional< extended_pco_t > extended_pco;
    optional< nrsm_cause_t >   cause;
};

struct pdu_session_modification_reject_t {
    nrsm_cause                 cause;
    optional< gprs_timer_3 >   backoff_timer;
    optional< extended_pco_t > extended_pco;
    optional< reattempt_indicator_t > reattempt_indicator;
    optional< congestion_reattempt_t> congestion_reattempt
};

struct pdu_session_modification_request_t {
    optional< nrsm_capability_t >                capability;
    optional< nrsm_cause_t >                     cause;
    optional< max_supported_packet_filters_t >   max_supported_packet_filters;
    optional< alwayson_pdu_session_requested_t > alwayson_pdu_session_requested;
    optional< max_data_rate_t >                  integrity_protection_max_data_rate;
    optional< qos_rules_t >                      requested_qos_rules;
    optional< qos_flow_description_t >           requested_qos_flow_description;
    optional< mapped_eps_bearer_contexts_t >     mapped_eps_bearer_contexts;
    optional< extended_pco_t >                   extended_pco;
};

struct pdu_session_release_command_t {
    nrsm_cause_t                      cause;
    optional< gprs_timer_3_t >        backoff_timer;
    optional< eap_message_t >         eap_message;
    optional< congestion_reattempt_t> congestion_reattempt;
    optional< extended_pco_t >        extended_pco;
};

struct pdu_session_release_complete_t {
    optional< nrsm_cause_t > cause;
    optional<extended_pco_t> extended_pco;
};

struct pdu_session_release_reject_t {
    nrsm_cause_t               cause;
    optional< extended_pco_t > extended_pco;
};

struct pdu_session_release_request_t {
    optional< nrsm_cause_t >   cause;
    optional< extended_pco_t > extended_pco;
};

struct nrsm_message_t {
    uint8_t extended_protocol_discriminator;
    uint8_t pdu_session_id;
    uint8_t procedure_transaction_id;
    uint8_t message_type;
    std::variant< nrsm_unknown_t,
                  pdu_session_establishment_request_t,
                  pdu_session_establishment_accept_t,
                  pdu_session_establishment_reject_t,
                  pdu_session_authentication_complete_t,
                  pdu_session_authentication_command_t,
                  pdu_session_modification_request_t,
                  pdu_session_modification_reject_t,
                  pdu_session_modification_command_t,
                  pdu_session_modification_complete_t,
                  pdu_session_modification_command_reject_t,
                  pdu_session_release_request_t,
                  pdu_session_release_reject_t,
                  pdu_session_release_command_t,
                  pdu_session_release_complete_t nrsm_status_t >
        ie;
};
using nas_plain_message_t = std::variant< nrmm_message_t, nrsm_message_t >;

struct nas_protected_message_t {
    uint8_t             extended_protocol_discriminator;
    nibble_t< 4 >       security_header_type;
    octet_t< 4 >        authentication_code;
    uint8_t             sequence_no;
    nas_plain_message_t body;
};

using nas_message_t = std::variant< nas_plain_message_t, nas_protected_message_t >;

using nas_message_container_t = nas_message_t;
using security_protected_nas_message = nas_message_t;

using dissect_t = int (*)(dissector, context*, const string&name);

int dissect_ie(dissector     d,
               context*      ctx,
               uint8_t       ieid,
               dissect_t     func,
               const string& name,
               bool          required = false) {
    if (d.length <= 0) return d.not_present(0, required, name);
    auto iei = d.uint8();
    iei      = d.left();
    if (iei_not_match(iei, ieid)) return d.not_present(0, required, name);

    auto     consumed = func(d, ctx, name);

    return consumed;
}

int dissect_ie_something(dissector d, context*ctx, const string&name){
    const use_context uc(d, ctx, name, 0);
    auto              tree = d.add_item(-1, name);
    use_tree          ut(d, tree);
    // auto ie = static_cast< ie_something* >(d.data);
    // ie->iei = d.uint8();
    (void) dissect_iei(d, ctx, none);
    d.step(1);

    (void) dissect_mcc_mnc(d, ctx);
    d.step(3);

    d.add_item(3, &mf_tac);
    d.step(3);

    tree->set_length(d.offset - uc.offset);
    return d.offset - uc.offset;
}

int dissect_tlv(dissector d, context* ctx, const ie_meta* meta, bool required = false){
    if (d.length <= 0) return d.not_present(0, required, meta);
    auto iei = d.uint8();
    iei      = d.left();
    if (iei_not_match(iei, meta)) return d.not_present(0, required, meta);

    auto     tree = d.add_item(-1, meta->name);
    use_tree ut(d, tree);

    auto consumed = meta->dissect(d, ctx, meta);
    tree->set_length(consumed);
    return consumed;
}

int dissect_v(dissector d, context*ctx, const ie_meta* meta){
    auto consumed = meta->dissect(d, ctx, meta);
    return consumed;
}

int dissect_tracking_area_identity(dissector d, context*ctx, const string&name = string()){
    auto           iename = "5GS tracking area identity";
    const use_context    uc(ctx, iename, d, 0);

    auto           tree = d.add_item(-1, use_name(name, iename));
    const use_tree ud(d, tree);

    auto           t = d.uint8() & 0x60u;
    auto           n = d.uint8() & 0x1fu;
    d.step(1);

    (void) dissect_mcc_mnc(d, ctx);
    d.step(3);

    for (uint8_t i = 1; i <= n; ++i){
        (void) dissect_tac(d, ctx, formats("TAC %d", i));
        d.step(3);
    }

    tree->set_length(d.offset - uc.offset);
    return d.offset - uc.offset;
}

int dissect_tracking_area_identiy_list(tracking_area_identity_list*self, dissector d, context*ctx, uint8_t ieid){
    if (d.length <= 0) return 0;
    if (iei_not_match(iei, d.uint8())) return 0;
    const use_context uc(ctx, "tracking-area-identity", 0);

    self->iei = d.uint8();
    d.step(1);

    self->length = d.uint8();
    d.step(1);

    for (auto len = self->length; len > 0;) {
        tracking_area_identity tai;
        auto                   consumed = dissect_tracking_area_identity(&tai, d, ctx);
        self->contents.push_back(tai);
        d.step(consumed);
        len -= consumed;
    }
    return d.offset - uc.offset;
}

int dissect_pdu_session_modification_reject(void*v, dissector d, context*ctx){
    auto self = static_cast< pdu_session_modification_reject* >(v);
    self->epd = d.uint8(true);

    self->pdu_session_id = d.uint(true);
    self->pti = d.uint(true);
    self->message_id     = d.uint8(true);
    self->cause          = d.uint8();

    auto consumed = dissect_gprs_timer_3(
        d, ctx, &self->backoff_timer.v, &self->backoff_timer.p, 0x37);
    d.step(consumed);

    if (gprs_timer_3 t = {}; auto consumed = dissect_gprs_timer_3(&t, d, ctx, 0x37)) {
        self->backoff_timer = t;
        d.step(consumed);
    }


    auto consumed = dissect_opt_ie(self->extended_pco, dissect_extended_pco, d, ctx, 0x7b);
    d.step(consumed);

}

int dissect_gprs_timer_3(dissector d, context*ctx, void*v, bool*present, int ieid){
    auto iei = d.uint8();
    *present = d.length > 0 && iei_match(iei, ieid);
    if (!*present) return 0;

    auto t = static_cast< gprs_timer_3* >(v);
    t->iei = iei;

    t->length = d.uint8();

    t->value  = d.uint8();

    return 3;
}
