#pragma once
#include "../mm/mm_dissects.hh"     // NOLINT
#include "../mm/mm_element_meta.hh" // NOLINT
#include "../mm/mm_field_meta.hh"   // NOLINT
#include "common.hh"                // NOLINT
#include "dissect_nas5g.hh"

/* 5GS mobility management messages */
namespace mm {
inline const dissect_fnc_t no_dissect = nullptr;

extern const message_meta      msgs[];

inline const tf_string tfs_requested_not_requested = {
    "Requested",
    "Not Requested",
};

inline const tf_string tfs_odd_even = {
    "Odd number of identity digits",
    "Even number of identity digits",
};

// extern const tf_string tfs_eps_security_context_types;
extern const v_string          tac_list_values[];
extern const v_string          request_type_values[];
extern const tf_string         tfs_follow_on_request;
extern const tf_string         tfs_security_context_types;
extern const tf_string         tfs_sms_requested;
extern const v_string          payload_container_type_values[];
extern const v_string          integrity_protection_algo_type_values[];
extern const v_string          nas_ksi_values[];
extern const v_string          values_registration_type[];
extern const v_string          service_type_values[];
extern const v_string          identity_type_values[];

inline const tf_string tfs_requested_or_not = {
    "Requested",
    "Not Requested",
};
} // namespace mm
