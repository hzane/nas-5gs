#pragma once
#include "core.hh"

/* 9.7  Message type */

/* 5GS mobility management messages */
namespace mm {
__declspec(selectany) extern const dissect_fnc_t no_dissect = nullptr;

int nas_5gs_mm_registration_req(packet_info* pinfo,
                                proto_node*  tree,
                                tvbuff*      buf,
                                int          offset,
                                int          len,
                                context*     ctx);
int nas_5gs_mm_registration_accept(packet_info* pinfo,
                                   proto_node*  tree,
                                   tvbuff*      buf,
                                   int          offset,
                                   int          len,
                                   context*     ctx);
int nas_5gs_mm_registration_complete(packet_info* pinfo,
                                     proto_node*  tree,
                                     tvbuff*      buf,
                                     int          offset,
                                     int          len,
                                     context*     ctx);
int nas_5gs_mm_registration_rej(packet_info* pinfo,
                                proto_node*  tree,
                                tvbuff*      buf,
                                int          offset,
                                int          len,
                                context*     ctx);
int nas_5gs_mm_de_reg_req_ue_orig(packet_info* pinfo,
                                  proto_node*  tree,
                                  tvbuff*      buf,
                                  int          offset,
                                  int          len,
                                  context*     ctx);
int nas_5gs_mm_de_registration_req_ue_term(packet_info* pinfo,
                                           proto_node*  tree,
                                           tvbuff*      buf,
                                           int          offset,
                                           int          len,
                                           context*     ctx);
int nas_5gs_mm_service_req(packet_info* pinfo,
                           proto_node*  tree,
                           tvbuff*      buf,
                           int          offset,
                           int          len,
                           context*     ctx);
int nas_5gs_mm_service_rej(packet_info* pinfo,
                           proto_node*  tree,
                           tvbuff*      buf,
                           int          offset,
                           int          len,
                           context*     ctx);
int nas_5gs_mm_service_acc(packet_info* pinfo,
                           proto_node*  tree,
                           tvbuff*      buf,
                           int          offset,
                           int          len,
                           context*     ctx);

int nas_5gs_mm_conf_upd_cmd(packet_info* pinfo,
                            proto_node*  tree,
                            tvbuff*      buf,
                            int          offset,
                            int          len,
                            context*     ctx);
int nas_5gs_mm_conf_update_comp(packet_info* pinfo,
                                proto_node*  tree,
                                tvbuff*      buf,
                                int          offset,
                                int          len,
                                context*     ctx);
int nas_5gs_mm_authentication_req(packet_info* pinfo,
                                  proto_node*  tree,
                                  tvbuff*      buf,
                                  int          offset,
                                  int          len,
                                  context*     ctx);
int nas_5gs_mm_authentication_resp(packet_info* pinfo,
                                   proto_node*  tree,
                                   tvbuff*      buf,
                                   int          offset,
                                   int          len,
                                   context*     ctx);
int nas_5gs_mm_authentication_rej(packet_info* pinfo,
                                  proto_node*  tree,
                                  tvbuff*      buf,
                                  int          offset,
                                  int          len,
                                  context*     ctx);
int nas_5gs_mm_authentication_failure(packet_info* pinfo,
                                      proto_node*  tree,
                                      tvbuff*      buf,
                                      int          offset,
                                      int          len,
                                      context*     ctx);
int nas_5gs_mm_authentication_result(packet_info* pinfo,
                                     proto_node*  tree,
                                     tvbuff*      buf,
                                     int          offset,
                                     int          len,
                                     context*     ctx);
int nas_5gs_mm_id_req(packet_info* pinfo,
                      proto_node*  tree,
                      tvbuff*      buf,
                      int          offset,
                      int          len,
                      context*     ctx);
int nas_5gs_mm_id_resp(packet_info* pinfo,
                       proto_node*  tree,
                       tvbuff*      buf,
                       int          offset,
                       int          len,
                       context*     ctx);
int nas_5gs_mm_sec_mode_cmd(packet_info* pinfo,
                            proto_node*  tree,
                            tvbuff*      buf,
                            int          offset,
                            int          len,
                            context*     ctx);
int nas_5gs_mm_sec_mode_comp(packet_info* pinfo,
                             proto_node*  tree,
                             tvbuff*      buf,
                             int          offset,
                             int          len,
                             context*     ctx);
int nas_5gs_mm_sec_mode_rej(packet_info* pinfo,
                            proto_node*  tree,
                            tvbuff*      buf,
                            int          offset,
                            int          len,
                            context*     ctx);

int nas_5gs_mm_5gmm_status(packet_info* pinfo,
                           proto_node*  tree,
                           tvbuff*      buf,
                           int          offset,
                           int          len,
                           context*     ctx);
int nas_5gs_mm_notification(packet_info* pinfo,
                            proto_node*  tree,
                            tvbuff*      buf,
                            int          offset,
                            int          len,
                            context*     ctx);
int nas_5gs_mm_notification_resp(packet_info* pinfo,
                                 proto_node*  tree,
                                 tvbuff*      buf,
                                 int          offset,
                                 int          len,
                                 context*     ctx);
int nas_5gs_mm_ul_nas_transp(packet_info* pinfo,
                             proto_node*  tree,
                             tvbuff*      buf,
                             int          offset,
                             int          len,
                             context*     ctx);
int nas_5gs_mm_dl_nas_transp(packet_info* pinfo,
                             proto_node*  tree,
                             tvbuff*      buf,
                             int          offset,
                             int          len,
                             context*     ctx);

__declspec(selectany) extern const message_meta msgs[] = {
    {
        0x41,
        "Registration request",
        nas_5gs_mm_registration_req,
    },
    {
        0x42,
        "Registration accept",
        nas_5gs_mm_registration_accept,
    },
    {
        0x43,
        "Registration complete",
        nas_5gs_mm_registration_complete,
    },
    {
        0x44,
        "Registration reject",
        nas_5gs_mm_registration_rej,
    },
    {
        0x45,
        "Deregistration request (UE originating)",
        nas_5gs_mm_de_reg_req_ue_orig,
    },
    {
        0x46,
        "Deregistration accept (UE originating)",
        nullptr,
    },
    {
        0x47,
        "Deregistration request (UE terminated)",
        nas_5gs_mm_de_registration_req_ue_term,
    },
    {
        0x48,
        "Deregistration accept (UE terminated)",
        nullptr,
    },

    {
        0x49,
        "Not used in current version",
        no_dissect,
    },
    {
        0x4a,
        "Not used in current version",
        no_dissect,
    },
    {
        0x4b,
        "Not used in current version",
        no_dissect,
    },

    {
        0x4c,
        "Service request",
        nas_5gs_mm_service_req,
    },
    {
        0x4d,
        "Service reject",
        nas_5gs_mm_service_rej,
    },
    {
        0x4e,
        "Service accept",
        nas_5gs_mm_service_acc,
    },

    {
        0x4f,
        "Not used in current version",
        no_dissect,
    },
    {
        0x50,
        "Not used in current version",
        no_dissect,
    },
    {
        0x51,
        "Not used in current version",
        no_dissect,
    },
    {
        0x52,
        "Not used in current version",
        no_dissect,
    },
    {
        0x53,
        "Not used in current version",
        no_dissect,
    },

    {
        0x54,
        "Configuration update command",
        nas_5gs_mm_conf_upd_cmd,
    },
    {
        0x55,
        "Configuration update complete",
        nas_5gs_mm_conf_update_comp,
    },
    {
        0x56,
        "Authentication request",
        nas_5gs_mm_authentication_req,
    },
    {
        0x57,
        "Authentication response",
        nas_5gs_mm_authentication_resp,
    },
    {
        0x58,
        "Authentication reject",
        nas_5gs_mm_authentication_rej,
    },
    {
        0x59,
        "Authentication failure",
        nas_5gs_mm_authentication_failure,
    },

    {
        0x5a,
        "Authentication result",
        nas_5gs_mm_authentication_result,
    },
    {
        0x5b,
        "Identity request",
        nas_5gs_mm_id_req,
    },
    {
        0x5c,
        "Identity response",
        nas_5gs_mm_id_resp,
    },
    {
        0x5d,
        "Security mode command",
        nas_5gs_mm_sec_mode_cmd,
    },
    {
        0x5e,
        "Security mode complete",
        nas_5gs_mm_sec_mode_comp,
    },
    {
        0x5f,
        "Security mode reject",
        nas_5gs_mm_sec_mode_rej,
    },

    {
        0x60,
        "Not used in current version",
        no_dissect,
    },
    {
        0x61,
        "Not used in current version",
        no_dissect,
    },
    {
        0x62,
        "Not used in current version",
        no_dissect,
    },
    {
        0x63,
        "Not used in current version",
        no_dissect,
    },
    {
        0x64,
        "5GMM status",
        nas_5gs_mm_5gmm_status,
    },
    {
        0x65,
        "Notification",
        nas_5gs_mm_notification,
    },
    {
        0x66,
        "Notification response",
        nas_5gs_mm_notification_resp,
    },
    {
        0x67,
        "UL NAS transport",
        nas_5gs_mm_ul_nas_transp,
    },
    {
        0x68,
        "DL NAS transport",
        nas_5gs_mm_dl_nas_transp,
    },
    {0, nullptr, nullptr},
};
}
