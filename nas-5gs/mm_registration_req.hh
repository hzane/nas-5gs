#pragma once
#include "core.hh"
#include "dissect_mm_msg.hh"

/* * 8.2.6 Registration request */

static const val_string nas_5gs_mm_reg_req_vals[] = {
    {0x08, "Follow-On Request bit (FOR)"},
    {0x07, "5GS registration type"},
    {0x70, "NAS key set identifier"},
    {0x80, "Type of security context flag (TSC)"},
    {0, nullptr},
};
static field_meta hfm_registration_req_flags = {
    "Message type",
    "nas_5gs.sm.message_type",
    ft::ft_uint8,
    fd::base_hex | fd::base_ext_string,
    nas_5gs_mm_reg_req_vals,
    nullptr,
    nullptr,
    0x0,
};
extern const field_meta* hf_registration_req_flags = &hfm_registration_req_flags;

static const val_string nas_5gs_mm_registration_req_elem[] = {
    {0xc0, "Non-current native NAS KSI"},
    {0x10, "5GMM capability"},
    {0x2e, "UE security capability"},
    {0x2f, "Requested NSSAI"},
    {0x52, "Last visited registered TAI"},
    {0x17, "S1 UE network capability"},
    {0x40, "Uplink data status"},
    {0x50, "PDU session status"},
    {0xb0, "MICO indication"},
    {0x2b, "UE status"},
    {0x77, "Additional GUTI"},
    {0x25, "Allowed PDU session status"},
    {0x18, "UE's usage setting"},
    {0x51, "Requested DRX parameters"},
    {0x70, "EPS NAS message container"},
    {0x74, "LADN indication"},
    {0x80, "Payload container type"},
    {0x7B, "Payload container"},
    {0x90, "Network slicing indication"},
    {0x53, "5GS update type"},
    {0x71, "NAS message container"},
    {0, nullptr},
};

static field_meta hfm_mm_registration_req_elem = {
    "Type",
    "elem.type",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_registration_req_elem,
    nullptr,
    nullptr,
    0x00,
};
extern const field_meta* hf_mm_registration_req_elem =
    &hfm_mm_registration_req_elem;

namespace em_de_mm {
extern const element_meta mobile_id;
extern const element_meta nksi_key_set_id;
extern const element_meta mm_cap;
extern const element_meta ue_sec_cap;
extern const element_meta mm_requested_nssai;
extern const element_meta last_v_tai;
extern const element_meta s1_ue_net_cap;
extern const element_meta ul_data_status;
extern const element_meta pdu_ses_status;
extern const element_meta mico_ind;
extern const element_meta ue_status;
extern const element_meta aguti_mobile_id;
extern const element_meta allow_pdu_ses_sts;
extern const element_meta ue_usage_set;
extern const element_meta requested_drx_param;
extern const element_meta eps_nas_msg_cont;
extern const element_meta ladn_inf;
extern const element_meta pld_cont_type;
extern const element_meta pld_cont;
extern const element_meta nw_slicing_ind;
extern const element_meta update_type;
extern const element_meta nas_msg_cont;
} // namespace em_de_nas_5gs_mm

namespace em_de_mm_reg_accept {
extern const element_meta reg_res;
extern const element_meta guti_5gs_mobile_id;
extern const element_meta plmn_list;
extern const element_meta ta_id_list;
extern const element_meta allowed_nssai;
extern const element_meta rejected_nssai;
extern const element_meta configured_nssai;
extern const element_meta nw_feat_sup;
extern const element_meta pdu_ses_status;
extern const element_meta pdu_ses_react_res;
extern const element_meta pdu_ses_react_res_err_c;
extern const element_meta ladn_inf;
extern const element_meta mico_ind;
extern const element_meta nw_slicing_ind;
extern const element_meta sal;
extern const element_meta t3512_gprs_timer_3;
extern const element_meta de_reg_timer_gprs_timer2;
extern const element_meta gprs_timer_2;
extern const element_meta emerg_num_list;
extern const element_meta emerg_num_list_7a;
extern const element_meta sor_trans_cont;
extern const element_meta eap_message;
extern const element_meta nssai_inclusion_mode;
extern const element_meta operator_defined_acd;
extern const element_meta nego_drx_param;
} // namespace em_de_mm_reg_accept

namespace nas_5gs_mm {
/* 9.11.3.4     5GS mobile identity*/
int mobile_id(packet_info* info,
              proto_node*  tree,
              tvbuff*      buf,
              int          offset,
              int          len,
              context*     ctx = nullptr);

/* 9.11.3.1     5GMM capability*/
int mm_cap(packet_info* info,
           proto_node*  tree,
           tvbuff*      buf,
           int          offset,
           int          len,
           context*     ctx = nullptr);

/* 9.11.3.2     5GMM cause*/
int mm_cause(packet_info* info,
             proto_node*  tree,
             tvbuff*      buf,
             int          offset,
             int          len,
             context*     ctx = nullptr);

/* 9.11.3.2A    5GS DRX parameters*/
int drx_param(packet_info* info,
              proto_node*  tree,
              tvbuff*      buf,
              int          offset,
              int          len,
              context*     ctx = nullptr);

/* 9.11.3.3     5GS identity type*/
int identity_type(packet_info* info,
                  proto_node*  tree,
                  tvbuff*      buf,
                  int          offset,
                  int          len,
                  context*     ctx = nullptr);

/* 9.11.3.5     5GS network feature support*/
int nw_feat_sup(packet_info* info,
                proto_node*  tree,
                tvbuff*      buf,
                int          offset,
                int          len,
                context*     ctx = nullptr);
/* 9.11.3.6     5GS registration result*/
int reg_res(packet_info* info,
            proto_node*  tree,
            tvbuff*      buf,
            int          offset,
            int          len,
            context*     ctx = nullptr);
/* 9.11.3.7     5GS registration type*/
int reg_type(packet_info* info,
             proto_node*  tree,
             tvbuff*      buf,
             int          offset,
             int          len,
             context*     ctx = nullptr);
/* 9.11.3.8     5GS tracking area identity */
int ta_id(packet_info* info,
          proto_node*  tree,
          tvbuff*      buf,
          int          offset,
          int          len,
          context*     ctx = nullptr);

/* 9.11.3.9     5GS tracking area identity list */
int ta_id_list(packet_info* info,
               proto_node*  tree,
               tvbuff*      buf,
               int          offset,
               int          len,
               context*     ctx = nullptr);

/* 9.11.3.9A    5GS update type */
int update_type(packet_info* info,
                proto_node*  tree,
                tvbuff*      buf,
                int          offset,
                int          len,
                context*     ctx = nullptr);

/* 9.11.3.10    ABBA */
int abba(packet_info* info,
         proto_node*  tree,
         tvbuff*      buf,
         int          offset,
         int          len,
         context*     ctx = nullptr);

/* 9.11.3.11    Access type */
int access_type(packet_info* info,
                proto_node*  tree,
                tvbuff*      buf,
                int          offset,
                int          len,
                context*     ctx = nullptr);

/* 9.11.3.12    Additional 5G security            information */
int add_5g_sec_inf(packet_info* info,
                   proto_node*  tree,
                   tvbuff*      buf,
                   int          offset,
                   int          len,
                   context*     ctx = nullptr);

/* 9.11.3.13    Allowed PDU session status*/
int allow_pdu_ses_sts(packet_info* info,
                      proto_node*  tree,
                      tvbuff*      buf,
                      int          offset,
                      int          len,
                      context*     ctx = nullptr);

/* 9.11.3.14    Authentication failure parameter */
/* 9.11.3.15    Authentication parameter AUTN*/
/* 9.11.3.16    Authentication parameter RAND*/
/* 9.11.3.17    Authentication response parameter */

/* 9.11.3.18    Configuration update indication*/
int conf_upd_ind(packet_info* info,
                 proto_node*  tree,
                 tvbuff*      buf,
                 int          offset,
                 int          len,
                 context*     ctx = nullptr);

/* 9.11.3.19    Daylight saving time*/

/* 9.11.3.20    De-registration type*/
int de_reg_type(packet_info* info,
                proto_node*  tree,
                tvbuff*      buf,
                int          offset,
                int          len,
                context*     ctx = nullptr);

/* 9.11.3.21    Void */
/* 9.11.3.22    Void*/
/* 9.11.3.23    Emergency number list*/

/* 9.11.3.24    EPS NAS message container*/
int eps_nas_msg_cont(packet_info* info,
                     proto_node*  tree,
                     tvbuff*      buf,
                     int          offset,
                     int          len,
                     context*     ctx = nullptr);

/* 9.11.3.25    EPS NAS security algorithms*/
/* 9.11.3.26    Extended emergency number list*/
/* 9.11.3.27    Void*/
/* 9.11.3.28    IMEISV request*/

/* 9.11.3.29    LADN indication*/
int ladn_indic(packet_info* info,
               proto_node*  tree,
               tvbuff*      buf,
               int          offset,
               int          len,
               context*     ctx = nullptr);

/* 9.11.3.30    LADN information*/
int ladn_inf(packet_info* info,
             proto_node*  tree,
             tvbuff*      buf,
             int          offset,
             int          len,
             context*     ctx = nullptr);

/* 9.11.3.31    MICO indication*/
int mico_ind(packet_info* info,
             proto_node*  tree,
             tvbuff*      buf,
             int          offset,
             int          len,
             context*     ctx = nullptr);

/* 9.11.3.32    NAS key set identifier*/
int nas_key_set_id(packet_info* info,
                   proto_node*  tree,
                   tvbuff*      buf,
                   int          offset,
                   int          len,
                   context*     ctx = nullptr);

/* 9.11.3.33    NAS message container*/
int nas_msg_cont(packet_info* info,
                 proto_node*  tree,
                 tvbuff*      buf,
                 int          offset,
                 int          len,
                 context*     ctx = nullptr);

/* 9.11.3.34    NAS security algorithms*/
int nas_sec_algo(packet_info* info,
                 proto_node*  tree,
                 tvbuff*      buf,
                 int          offset,
                 int          len,
                 context*     ctx = nullptr);

/* 9.11.3.35    Network name*/

/* 9.11.3.36    Network slicing indication */
int nw_slicing_ind(packet_info* info,
                   proto_node*  tree,
                   tvbuff*      buf,
                   int          offset,
                   int          len,
                   context*     ctx = nullptr);

/* 9.11.3.37    NSSAI*/
int nssai(packet_info* info,
          proto_node*  tree,
          tvbuff*      buf,
          int          offset,
          int          len,
          context*     ctx = nullptr);

/* 9.11.3.37A   NSSAI inclusion mode */
int nssai_inc_mode(packet_info* info,
                   proto_node*  tree,
                   tvbuff*      buf,
                   int          offset,
                   int          len,
                   context*     ctx = nullptr);

/* 9.11.3.38    Operator-defined access  category  definitions */
int op_def_acc_cat_def(packet_info* info,
                       proto_node*  tree,
                       tvbuff*      buf,
                       int          offset,
                       int          len,
                       context*     ctx = nullptr);

/* 9.11.3.39    Payload container*/
int pld_cont(packet_info* info,
             proto_node*  tree,
             tvbuff*      buf,
             int          offset,
             int          len,
             context*     ctx = nullptr);

/* 9.11.3.40    Payload container type*/
int pld_cont_type(packet_info* info,
                  proto_node*  tree,
                  tvbuff*      buf,
                  int          offset,
                  int          len,
                  context*     ctx = nullptr);

/* 9.11.3.41    PDU session identity 2*/
int pdu_ses_id_2(packet_info* info,
                 proto_node*  tree,
                 tvbuff*      buf,
                 int          offset,
                 int          len,
                 context*     ctx = nullptr);

/* 9.11.3.42    PDU session reactivation  result*/
int pdu_ses_react_res(packet_info* info,
                      proto_node*  tree,
                      tvbuff*      buf,
                      int          offset,
                      int          len,
                      context*     ctx = nullptr);

/* 9.11.3.43    PDU session reactivation result error cause */
int pdu_ses_react_res_err_c(packet_info* info,
                            proto_node*  tree,
                            tvbuff*      buf,
                            int          offset,
                            int          len,
                            context*     ctx = nullptr);

/* 9.11.3.44    PDU session status*/
int pdu_ses_status(packet_info* info,
                   proto_node*  tree,
                   tvbuff*      buf,
                   int          offset,
                   int          len,
                   context*     ctx = nullptr);

/* 9.11.3.45    PLMN list*/

/* 9.11.3.46    Rejected NSSAI*/
int rej_nssai(packet_info* info,
              proto_node*  tree,
              tvbuff*      buf,
              int          offset,
              int          len,
              context*     ctx = nullptr);

/* 9.11.3.47    Request type*/
int req_type(packet_info* info,
             proto_node*  tree,
             tvbuff*      buf,
             int          offset,
             int          len,
             context*     ctx = nullptr);

/* 9.11.3.48    S1 UE network capability*/
/* 9.11.3.48A   S1 UE security capability*/

/* 9.11.3.49    Service area list*/
int sal(packet_info* info,
        proto_node*  tree,
        tvbuff*      buf,
        int          offset,
        int          len,
        context*     ctx = nullptr);

/* 9.11.3.50    Service type*/ /* Used Inline Half octet IE */

/* 9.11.3.50A   SMS indication */
int sms_ind(packet_info* info,
            proto_node*  tree,
            tvbuff*      buf,
            int          offset,
            int          len,
            context*     ctx = nullptr);

/* 9.11.3.51    SOR transparent container */
int sor_trasp_cont(packet_info* info,
                   proto_node*  tree,
                   tvbuff*      buf,
                   int          offset,
                   int          len,
                   context*     ctx = nullptr);

/* 9.11.3.52    Time zone*/
/* 9.11.3.53    Time zone and time*/

/* 9.11.3.53A   UE parameters update  transparent container */
int ue_par_upd_trasnsp_cont(packet_info* info,
                            proto_node*  tree,
                            tvbuff*      buf,
                            int          offset,
                            int          len,
                            context*     ctx = nullptr);

/* 9.11.3.54    UE security capability*/
int ue_sec_cap(packet_info* info,
               proto_node*  tree,
               tvbuff*      buf,
               int          offset,
               int          len,
               context*     ctx = nullptr);

/* 9.11.3.55    UE's usage setting*/
int ue_usage_set(packet_info* info,
                 proto_node*  tree,
                 tvbuff*      buf,
                 int          offset,
                 int          len,
                 context*     ctx = nullptr);

/* 9.11.3.56    UE status*/
int ue_status(packet_info* info,
              proto_node*  tree,
              tvbuff*      buf,
              int          offset,
              int          len,
              context*     ctx = nullptr);

/* 9.11.3.57    Uplink data status*/
int ul_data_status(packet_info* info,
                   proto_node*  tree,
                   tvbuff*      buf,
                   int          offset,
                   int          len,
                   context*     ctx = nullptr);
} // namespace de_nas_5gs_mm_5gs
