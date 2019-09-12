#pragma once
#include "config.hh"
#include "core.hh"
#include "dissect_nas5g.hh"
#include "common.hh"  
#include "sm/sm_dissects.hh"
#include "sm/sm_element_meta.hh"
#include "sm/sm_field_meta.hh"

struct context;

/* 5GS session management messages */
namespace sm {
__declspec(selectany) extern const dissect_fnc_t no_dissect = nullptr;

extern const true_false_string tfs_sm_default_qos_rules;
extern const message_meta      msgs[];
extern const value_string      ambr_values[];
extern const value_string      sm_cause_values[];
extern const value_string      rule_operation_code_values[];
extern const value_string      packet_filter_component_type_values[];
extern const value_string      packet_filter_direction_values[];
extern const value_string      operation_code_values[];
extern const value_string      deb_bit_values[];
extern const value_string      e_bit_values[];
extern const value_string      e_bit_modify_values[];
extern const value_string      eps_parameter_identity_values[];
extern const value_string      int_prot_max_data_rate_values[];
extern const value_string      ssc_mode_values[];

inline extern const true_false_string tfs_allowed_not_allowed = {
    "Allowed",
    "Not Allowed",
};

} // namespace sm
