#pragma once
#include "core.hh"

/* 5GS session management messages */
namespace sm {
__declspec(selectany) extern const dissect_fnc_t no_dissect = nullptr;

int pdu_ses_est_req(dissector d, context* ctx);
int pdu_ses_est_acc(dissector d, context* ctx);
int pdu_ses_est_rej(dissector d, context* ctx);
int pdu_ses_auth_cmd(dissector d, context* ctx);
int pdu_ses_auth_comp(dissector d, context* ctx);
int pdu_ses_mod_req(dissector d, context* ctx);
int pdu_ses_mod_rej(dissector d, context* ctx);
int pdu_ses_mod_cmd(dissector d, context* ctx);
int pdu_ses_mod_comp(dissector d, context* ctx);

int pdu_ses_mod_com_rej(dissector d, context* ctx);
int pdu_ses_rel_req(dissector d, context* ctx);
int pdu_ses_rel_rej(dissector d, context* ctx);
int pdu_ses_rel_cmd(dissector d, context* ctx);
int pdu_ses_rel_comp(dissector d, context* ctx);
int sm_status(dissector d, context* ctx);

__declspec(selectany) extern const message_meta msgs[] = {
    {0xc1, "PDU session establishment request", pdu_ses_est_req},
    {0xc2, "PDU session establishment accept", pdu_ses_est_acc},
    {0xc3, "PDU session establishment reject", pdu_ses_est_rej},

    {0xc4, "Not used in current version", no_dissect},
    {0xc5, "PDU session authentication command", pdu_ses_auth_cmd},

    {0xc6, "PDU session authentication complete", pdu_ses_auth_comp},
    {0xc7, "PDU session authentication result", no_dissect},
    {0xc8, "Not used in current version", no_dissect},

    {0xc9, "PDU session modification request", pdu_ses_mod_req},
    {0xca, "PDU session modification reject", pdu_ses_mod_rej},
    {0xcb, "PDU session modification command", pdu_ses_mod_cmd},
    {0xcc, "PDU session modification complete", pdu_ses_mod_comp},
    {0xcd, "PDU session modification command reject", pdu_ses_mod_com_rej},

    {0xce, "Not used in current version", no_dissect},
    {0xcf, "Not used in current version", no_dissect},
    {0xd0, "Not used in current version", no_dissect},

    {0xd1, "PDU session release request", pdu_ses_rel_req},
    {0xd2, "PDU session release reject", pdu_ses_rel_rej},
    {0xd3, "PDU session release command", pdu_ses_rel_cmd},
    {0xd4, "PDU session release complete", pdu_ses_rel_comp},

    {0xd5, "Not used in current version", no_dissect},

    {0xd6, "5GSM status", nas_5gs_sm_5gsm_status},
    {0, nullptr, nullptr},
};
} // namespace sm
