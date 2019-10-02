set(SM_SRCS  allowed_scc_mode.cc
        alwayson_pdu_session_indication.cc
        alwayson_pdu_session_requested.cc
        atsss_container.cc
        control_plane_only_indication.cc
        extended_protocol_configuration_options.cc
        integrity_protection_maximum_data_rate.cc
        mapped_eps_bearer_contexts.cc
        maximum_number_of_supported_packet_filters.cc
        nsm_capability.cc
        nsm_cause.cc
        nsm_congestion_reattempt_indicator.cc
        nsm_network_feature_support.cc
        nsm_status.cc
        pdu_address.cc
        pdu_session_authentication_command.cc
        pdu_session_authentication_complete.cc
        pdu_session_authentication_result.cc
        pdu_session_establishment_accept.cc
        pdu_session_establishment_reject.cc
        pdu_session_establishment_request.cc
        pdu_session_modification_command.cc
        pdu_session_modification_command_reject.cc
        pdu_session_modification_complete.cc
        pdu_session_modification_reject.cc
        pdu_session_modification_request.cc
        pdu_session_release_command.cc
        pdu_session_release_complete.cc
        pdu_session_release_reject.cc
        pdu_session_release_request.cc
        qos_flow_descriptions.cc
        qos_rules.cc
        reattempt_indicator.cc
        scc_mode.cc
        serving_plmn_rate_control.cc
        session_ambr.cc
        sm_dissects.hh
        sm_element_meta.hh
        sm_field_meta.hh
        sm_pdu_dn_request_container.cc)

add_library(nas-nr-sm ${SM_SRCS})
# set_property(TARGET nas-nr-sm PROPERTY POSITION_INDEPENDENT_CODE TRUE)
