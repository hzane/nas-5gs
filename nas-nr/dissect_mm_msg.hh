#pragma once
#include "common.hh" // NOLINT
#include "dissect_nas5g.hh"
#include "mm/mm_dissects.hh"     // NOLINT
#include "mm/mm_element_meta.hh" // NOLINT
#include "mm/mm_field_meta.hh"   // NOLINT

/* 5GS mobility management messages */
namespace mm {
inline __declspec(selectany) extern const dissect_fnc_t no_dissect = nullptr;

extern const message_meta      msgs[];

extern const true_false_string tfs_sal_al_t;

inline const true_false_string tfs_requested_not_requested = {
    "Requested",
    "Not Requested",
};

inline __declspec(selectany) extern const true_false_string tfs_odd_even = {
    "Odd number of identity digits",
    "Even number of identity digits",
};

extern const true_false_string tfs_eps_security_context_types;
extern const true_false_string tfs_follow_on_request;
extern const true_false_string tfs_security_context_types;
extern const true_false_string tfs_sms_requested;
extern const val_string        payload_container_type_values[];
extern const val_string        tac_list_values[];
extern const val_string        nas_ksi_values[];
extern const val_string values_registration_type[];
extern const val_string        enc_algo_type_values[];
extern const val_string        integrity_protection_algo_type_values[];
extern const val_string        request_type_values[];
extern const val_string        service_type_values[];
extern const val_string identity_type_values[];

inline __declspec(selectany) extern const true_false_string tfs_requested_or_not = {
    "Requested",
    "Not Requested",
};
} // namespace mm
