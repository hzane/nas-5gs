#pragma once
#include "core.hh"

/* 9.7  Message type */

/* 5GS mobility management messages */
namespace mm {
__declspec(selectany) extern const dissect_fnc_t no_dissect = nullptr;

int registration_req(dissector d, context* ctx);
int registration_accept(dissector d, context* ctx);
int registration_complete(dissector d, context* ctx);
int registration_rej(dissector d, context* ctx);
int de_reg_req_ue_orig(dissector d, context* ctx);
int de_registration_req_ue_term(dissector d, context* ctx);
int service_req(dissector d, context* ctx);
int service_rej(dissector d, context* ctx);
int service_acc(dissector d, context* ctx);

int conf_upd_cmd(dissector d, context* ctx);
int conf_update_comp(dissector d, context* ctx);
int authentication_req(dissector d, context* ctx);
int authentication_resp(dissector d, context* ctx);
int authentication_rej(dissector d, context* ctx);
int authentication_failure(dissector d, context* ctx);
int authentication_result(dissector d, context* ctx);
int id_req(dissector d, context* ctx);
int id_resp(dissector d, context* ctx);
int sec_mode_cmd(dissector d, context* ctx);
int sec_mode_comp(dissector d, context* ctx);
int sec_mode_rej(dissector d, context* ctx);

int mm_status(dissector d, context* ctx);
int notification(dissector d, context* ctx);
int notification_resp(dissector d, context* ctx);
int ul_nas_transp(dissector d, context* ctx);
int dl_nas_transp(dissector d, context* ctx);

__declspec(selectany) extern const message_meta msgs[] = {
    {0x41, "Registration request", registration_req},
    {0x42, "Registration accept", registration_accept},
    {0x43, "Registration complete", registration_complete},
    {0x44, "Registration reject", registration_rej},
    {0x45, "Deregistration request (UE originating)", de_reg_req_ue_orig},
    {0x46, "Deregistration accept (UE originating)", nullptr},
    {0x47, "Deregistration request (UE terminated)", de_registration_req_ue_term},
    {0x48, "Deregistration accept (UE terminated)", nullptr},

    {0x49, "Not used in current version", no_dissect},
    {0x4a, "Not used in current version", no_dissect},
    {0x4b, "Not used in current version", no_dissect},

    {0x4c, "Service request", service_req},
    {0x4d, "Service reject", service_rej},
    {0x4e, "Service accept", service_acc},

    {0x4f, "Not used in current version", no_dissect},
    {0x50, "Not used in current version", no_dissect},
    {0x51, "Not used in current version", no_dissect},
    {0x52, "Not used in current version", no_dissect},
    {0x53, "Not used in current version", no_dissect},

    {0x54, "Configuration update command", conf_upd_cmd},
    {0x55, "Configuration update complete", conf_update_comp},
    {0x56, "Authentication request", authentication_req},
    {0x57, "Authentication response", authentication_resp},
    {0x58, "Authentication reject", authentication_rej},
    {0x59, "Authentication failure", authentication_failure},

    {0x5a, "Authentication result", authentication_result},
    {0x5b, "Identity request", id_req},
    {0x5c, "Identity response", id_resp},
    {0x5d, "Security mode command", sec_mode_cmd},
    {0x5e, "Security mode complete", sec_mode_comp},
    {0x5f, "Security mode reject", sec_mode_rej},

    {0x60, "Not used in current version", no_dissect},
    {0x61, "Not used in current version", no_dissect},
    {0x62, "Not used in current version", no_dissect},
    {0x63, "Not used in current version", no_dissect},
    {0x64, "5GMM status", mm_status},
    {0x65, "Notification", notification},
    {0x66, "Notification response", notification_resp},
    {0x67, "UL NAS transport", ul_nas_transp},
    {0x68, "DL NAS transport", dl_nas_transp},
    {0, nullptr, nullptr},
};
}

int                       dissect_mm_cause(dissector d, context* ctx);
__declspec(selectany) extern const element_meta mm_cause = {
    -1,
    "5GMM cause",
    dissect_mm_cause,
};

int dissect_eap_msg(dissector d, context* ctx);

__declspec(selectany) extern const element_meta eap_msg = {
    0x78,
    "EAP message",
    dissect_eap_msg,
};

int                       dissect_nksi(dissector d, context* ctx);
__declspec(selectany) extern const element_meta nksi = {
    -1,
    "NAS key set identifier",
    dissect_nksi,
};

int                       dissect_mobile_id(dissector d, context* ctx);
__declspec(selectany) extern const element_meta mobile_id = {
    -1,
    "Mobile identity",
    dissect_mobile_id,
};

int                dissect_pdu_ses_status(dissector d, context* ctx = nullptr);
__declspec(selectany) extern const element_meta pdu_ses_status = {
    0x50,
    "PDU session status",
    dissect_pdu_ses_status,
};

int                dissect_nas_msg_cont(dissector d, context* ctx = nullptr);
__declspec(selectany) extern const element_meta nas_msg_cont = {
    0x71,
    "NAS message container",
    dissect_nas_msg_cont,
};
