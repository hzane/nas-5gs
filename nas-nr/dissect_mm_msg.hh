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

extern const true_false_string tfs_eps_tsc;

extern const true_false_string tfs_nas_5gs_mm_n1_mod;
extern const true_false_string tfs_nas_5gs_mm_s1_mod;

extern const true_false_string tfs_follow_on_req;
extern const true_false_string tfs_mm_tsc;
extern const true_false_string tfs_sms_requested;


extern const val_string mm_pld_cont_type_values[];
extern const val_string values_cause[];
extern const val_string mm_sal_t_li_values[];
extern const val_string nas_eps_emm_nas_ksi_values[];
/* 9.11.3.7    5GS registration type */
extern const val_string values_registration_type[];
extern const val_string mm_type_of_enc_algo_vals[];
extern const val_string mm_type_of_ip_algo_vals[];
extern const val_string mm_req_type_vals[];
extern const val_string mm_serv_type_vals[];
extern const val_string identity_type_values[];

inline __declspec(selectany) extern const true_false_string tfs_supported_not_supported = {
    "Supported",
    "Not supported",
};

inline __declspec(selectany) extern const true_false_string tfs_requested_or_not = {
    "Requested",
    "Not Requested",
};
} // namespace mm
