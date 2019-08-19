#pragma once
#include "core.hh"

/* 5GS session management messages */
namespace sm {
__declspec(selectany) extern const dissect_fnc_t no_dissect = nullptr;

int nas_5gs_sm_pdu_ses_est_req(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx);
int nas_5gs_sm_pdu_ses_est_acc(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx);
int nas_5gs_sm_pdu_ses_est_rej(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx);
int nas_5gs_sm_pdu_ses_auth_cmd(packet_info* pinfo,
                                proto_node*  tree,
                                tvbuff*      buf,
                                int          offset,
                                int          len,
                                context*     ctx);
int nas_5gs_sm_pdu_ses_auth_comp(packet_info* pinfo,
                                 proto_node*  tree,
                                 tvbuff*      buf,
                                 int          offset,
                                 int          len,
                                 context*     ctx);
int nas_5gs_sm_pdu_ses_mod_req(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx);
int nas_5gs_sm_pdu_ses_mod_rej(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx);
int nas_5gs_sm_pdu_ses_mod_cmd(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx);
int nas_5gs_sm_pdu_ses_mod_comp(packet_info* pinfo,
                                proto_node*  tree,
                                tvbuff*      buf,
                                int          offset,
                                int          len,
                                context*     ctx);

int nas_5gs_sm_pdu_ses_mod_com_rej(packet_info* pinfo,
                                   proto_node*  tree,
                                   tvbuff*      buf,
                                   int          offset,
                                   int          len,
                                   context*     ctx);
int nas_5gs_sm_pdu_ses_rel_req(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx);
int nas_5gs_sm_pdu_ses_rel_rej(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx);
int nas_5gs_sm_pdu_ses_rel_cmd(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx);
int nas_5gs_sm_pdu_ses_rel_comp(packet_info* pinfo,
                                proto_node*  tree,
                                tvbuff*      buf,
                                int          offset,
                                int          len,
                                context*     ctx);
int nas_5gs_sm_5gsm_status(packet_info* pinfo,
                           proto_node*  tree,
                           tvbuff*      buf,
                           int          offset,
                           int          len,
                           context*     ctx);
__declspec(selectany) extern const message_meta msgs[] = {
    {0xc1, "PDU session establishment request", nas_5gs_sm_pdu_ses_est_req},
    {0xc2, "PDU session establishment accept", nas_5gs_sm_pdu_ses_est_acc},
    {0xc3, "PDU session establishment reject", nas_5gs_sm_pdu_ses_est_rej},

    {0xc4, "Not used in current version", no_dissect},
    {0xc5, "PDU session authentication command", nas_5gs_sm_pdu_ses_auth_cmd},

    {0xc6, "PDU session authentication complete", nas_5gs_sm_pdu_ses_auth_comp},
    {0xc7, "PDU session authentication result", no_dissect},
    {0xc8, "Not used in current version", no_dissect},

    {0xc9, "PDU session modification request", nas_5gs_sm_pdu_ses_mod_req},
    {0xca, "PDU session modification reject", nas_5gs_sm_pdu_ses_mod_rej},
    {0xcb, "PDU session modification command", nas_5gs_sm_pdu_ses_mod_cmd},
    {0xcc, "PDU session modification complete", nas_5gs_sm_pdu_ses_mod_comp},
    {0xcd, "PDU session modification command reject", nas_5gs_sm_pdu_ses_mod_com_rej},

    {0xce, "Not used in current version", no_dissect},
    {0xcf, "Not used in current version", no_dissect},
    {0xd0, "Not used in current version", no_dissect},

    {0xd1, "PDU session release request", nas_5gs_sm_pdu_ses_rel_req},
    {0xd2, "PDU session release reject", nas_5gs_sm_pdu_ses_rel_rej},
    {0xd3, "PDU session release command", nas_5gs_sm_pdu_ses_rel_cmd},
    {0xd4, "PDU session release complete", nas_5gs_sm_pdu_ses_rel_comp},

    {0xd5, "Not used in current version", no_dissect},

    {0xd6, "5GSM status", nas_5gs_sm_5gsm_status},
    {0, nullptr, nullptr},
};
}

