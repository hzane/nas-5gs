#pragma once
#include "config.hh"
#include "core.hh"
#include "sm/sm_dissects.hh"
#include "sm/sm_element_meta.hh"
#include "sm/sm_field_meta.hh"

struct context;

/* 5GS session management messages */
namespace sm {
__declspec(selectany) extern const dissect_fnc_t no_dissect = nullptr;

extern const true_false_string tfs_allowed_not_allowed;
extern const true_false_string tfs_sm_dqr ;
extern const message_meta msgs[];

extern const value_string sm_unit_for_session_ambr_values[];
extern const value_string sm_cause_values[];

// *     9.11.4.13    QoS rules
extern const value_string rule_operation_code_values[] ;
extern const value_string sm_pf_type_values[] ;
extern const value_string sm_pkt_flt_dir_values[] ;
extern const value_string rule_param_cont[] ;

/*   9.11.4.8 Mapped EPS bearer contexts  */
extern const value_string sm_mapd_eps_b_cont_opt_code_values[] ;
extern const value_string sm_mapd_eps_b_cont_deb_values[] ;
extern const value_string sm_mapd_eps_b_cont_e_values[] ;
extern const value_string sm_mapd_eps_b_cont_E_Modify_values[] ;
extern const value_string sm_mapd_eps_b_cont_param_id_values[] ;


// * 9.11.4.7 Integrity protection maximum data rate
extern const value_string sm_int_prot_max_data_rate_values[] ;


/* 9.11.4.16    SSC mode */
extern const value_string sc_mode_values[] ;
} // namespace sm
