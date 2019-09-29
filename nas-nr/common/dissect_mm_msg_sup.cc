#include "dissect_mm_msg.hh"

using namespace mm;
using namespace nas;


/* *    9.11.3.48    S1 UE network capability */
/* See subclause 9.9.3.34 in 3GPP TS 24.301 */

/* *   9.11.3.48A    S1 UE security capability */
/*See subclause 9.9.3.36 in 3GPP TS 24.301 */

/* *     9.11.3.49    Service area list */

extern const v_string mm::tac_list_values[] = {
    {0x00, "list of TACs belonging to one PLMN, with non-consecutive TAC values"},
    {0x01, "list of TACs belonging to one PLMN, with consecutive TAC values"},
    {0x02, "list of TAIs belonging to different PLMNs"},
    {0x03, "All TAIs belonging to the PLMN are in the allowed area"},
    {0, nullptr},
};


extern const message_meta mm::msgs[] = {
    {0x41, "Registration request", dissect_registration_request, },
    {0x42, "Registration accept", dissect_registration_accept, },
    {0x43, "Registration complete", dissect_registration_complete, },
    {0x44, "Registration reject", dissect_registration_reject, },

    {
        0x45,
        "Deregistration request (UE originating)",
        dissect_deregistration_request_ue_origin,
    },
    {
        0x46,
        "Deregistration accept (UE originating)",
        dissect_deregistration_accept_ue_origin,
    },
    {
        0x47,
        "Deregistration request (UE terminated)",
        dissect_deregistration_request_ue_terminate,
    },
    {
        0x48,
        "Deregistration accept (UE terminated)",
        dissect_deregistration_accept_ue_terminate,
    },

    {0x49, "Not used in current version", no_dissect, },
    {0x4a, "Not used in current version", no_dissect, },
    {0x4b, "Not used in current version", no_dissect, },

    {0x4c, "Service request", dissect_service_request, },
    {0x4d, "Service reject", dissect_service_reject, },
    {0x4e, "Service accept", dissect_service_accept, },

    {0x4f, "Not used in current version", no_dissect, },
    {0x50, "Not used in current version", no_dissect, },
    {0x51, "Not used in current version", no_dissect, },
    {0x52, "Not used in current version", no_dissect, },
    {0x53, "Not used in current version", no_dissect, },

    {0x54, "Configuration update command", dissect_configuration_update_command, },
    {
        0x55,
        "Configuration update complete",
        dissect_configuration_update_complete,
    },

    {0x56, "Authentication request", dissect_authentication_request, },
    {0x57, "Authentication response", dissect_authentication_response, },
    {0x58, "Authentication reject", dissect_authentication_reject, },
    {0x59, "Authentication failure", dissect_authentication_failure, },
    {0x5a, "Authentication result", dissect_authentication_result, },

    {0x5b, "Identity request", dissect_identity_request, },
    {0x5c, "Identity response", dissect_identity_response, },
    {0x5d, "Security mode command", dissect_security_mode_command, },
    {0x5e, "Security mode complete", dissect_security_mode_complete, },
    {0x5f, "Security mode reject", dissect_security_mode_reject, },

    {0x60, "Not used in current version", no_dissect, },
    {0x61, "Not used in current version", no_dissect, },
    {0x62, "Not used in current version", no_dissect, },
    {0x63, "Not used in current version", no_dissect, },

    {0x64, "5GMM status", dissect_mm_status, },
    {0x65, "Notification", dissect_notification, },
    {0x66, "Notification response", dissect_notification_response, },
    {0x67, "UL NAS transport", dissect_ul_nas_transport, },
    {0x68, "DL NAS transport", dissect_dl_nas_transparent, },
    {0, nullptr, nullptr, },
};

extern const uint24_field hf_slice_differentiator = {
    "Slice differentiator (SD)",
    0x0,
};

// defined in 3GPP TS 23.003
extern const uint8_field hf_slice_service_type = {
    "Slice/service type (SST)",
    0x0,
};

