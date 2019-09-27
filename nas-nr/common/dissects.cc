#include <cstring>
#include "core.hh"
#include "message.hh"
#include "nas.hh"
#include "ber.hh"

int dissect_nsm_message(dissector d, context* ctx, nsm_message_t* v);
int dissect_nmm_message(dissector d, context* ctx, nmm_message_t* v);

int dissect_authentication_request(dissector                 d,
                                   context*                  ctx,
                                   authentication_request_t* ret) {
    auto consumed = dissect_nmm_header(d, ctx, &ret->header);
    d.step(consumed);

    ret->ng_ksi = d.uint8() & 0x0fu;

    d.step(dissect_lv(d, ctx, &ret->abba, dissect_octet));

    d.step(dissect_tv(d.slice(17),
                      ctx,
                      &ret->rand,
                      dissect_octet));
    return d.length;
}
int dissect_nas_plain(dissector d, context* ctx, nas_message_plain_t* v);
int dissect_nas_protected(dissector d, context* ctx, nas_message_protected_t* v);

int dissect_nas_message(dissector d, context* ctx, nas_message_t* v) {
    /* 9.2 Extended protocol discriminator  octet 1 */
    auto epd = d.uint8(false);

    // Security header type (octet 1)
    const auto security_type = d.uint8(false, 1) & 0x0fu;

    if (epd == epd::nsm || security_type == 0) {
        v->plain=std::make_shared<nas_message_plain_t>();
        auto consumed = dissect_nas_plain(d, ctx, v->plain.get());
        return consumed;
    }
    v->sec = std::make_shared<nas_message_protected_t>();
    return dissect_nas_protected(d, ctx, v->sec.get());
}

int dissect_nas_protected(dissector d, context* ctx, nas_message_protected_t* v) {
    const use_context uc(&d, ctx, "security protected nas message", 0);

    /* 9.2 Extended protocol discriminator  octet 1 */
    v->epd = d.uint8();

    /* 9.3 Security header type associated    1/2 */
    // 9.5 Spare half octet 1/2
    v->security_header_type = d.uint8() & 0x0fu;

    /* 9.8 Message authentication code octet 3 - 6 */
    (void) d.octet(v->auth_code, std::size(v->auth_code));

    /* 9.10 Sequence number    octet 7 */
    v->sequence_no = d.uint8();

    // TODO: decrypt the body
    // This should work when the NAS ciphering algorithm is NULL (128-EEA0)
    const auto consumed = dissect_nas_plain(d, ctx, &v->plain);
    d.step(consumed);

    return uc.length;
}

/* Plain NAS 5GS Message */
int dissect_nas_plain(dissector d, context* ctx, nas_message_plain_t* v) {
    const use_context uc(&d, ctx, "plain-nas-message", 0);

    /* Extended protocol discriminator  octet 1 */
    const auto epd = d.uint8(false);
    auto       consumed = 0;

    if (epd == epd::nmm) {
        v->nmm = std::make_shared<nmm_message_t>();
        consumed = dissect_nmm(d, ctx, v->nmm.get());
    } else if (epd == epd::nsm) {
        v->nsm = std::make_shared<nsm_message_t>();
        consumed = dissect_nsm_message(d, ctx, v->nsm.get());
    } else {
        diag("unknown epd %d\n", epd);
    }
    d.step(consumed);

    return uc.length;
}

struct message_desc_t {
    using dissect_t = int (*)(dissector, context*, void* ret);
    uint8_t     type;
    const char* name;
    dissect_t   dissect;
};

int dissect_nsm_message(dissector d, context* ctx, nsm_message_t* v) {
    const use_context uc(&d, ctx, "session-management-message", 0);

    dissect_nsm_header(d, ctx, &v->header);

    switch (v->header.message_type) {
    case 0xc1u:

        break;
    default:
        break;
    }

    return uc.length;
}

extern const message_desc_t nmm_messages[];
int dissect_nmm_message(dissector d, context* ctx, nmm_message_t* v) {
    const use_context uc(&d, ctx, "mobile-management-message", 0);

    for (auto i = nmm_messages; i->name != nullptr;) {
        if(i->type == v->header.message_type){

        }
        ++i;
    }
    return 0;
}

int dissect_nmm_header(dissector d, context* ctx, nmm_header_t* ret) {
    ret->epd                  = d.uint8();
    ret->security_header_type = d.uint8() & 0x0fu;
    ret->message_type         = d.uint8();
    return 3;
}

int dissect_nsm_header(dissector d, context* ctx, nsm_header_t* ret) {
    ret->epd            = d.uint8();
    ret->pdu_session_id = d.uint8();
    ret->pti            = d.uint8();
    ret->message_type   = d.uint8();
    return 4;
}

extern const message_desc_t nmm_messages[] = {
    {0x41, "Registration request", dissect_registration_request},
    {0x42, "Registration accept", dissect_registration_accept},
    {0x43, "Registration complete", dissect_registration_complete},
    {0x44, "Registration reject", dissect_registration_reject},

    {
        0x45,
        "Deregistration request (UE originating)",
        dissect_deregistration_request_ue_origin,
    },
    {
        0x46,
        "Deregistration accept (UE originating)",
        dissect_deregistration_accept_ue_origin,
    },
    {
        0x47,
        "Deregistration request (UE terminated)",
        dissect_deregistration_request_ue_terminate,

    },
    {
        0x48,
        "Deregistration accept (UE terminated)",
        dissect_deregistration_accept_ue_terminate,

    },

    {0x49, "Not used in current version", no_dissect},
    {0x4a, "Not used in current version", no_dissect},
    {0x4b, "Not used in current version", no_dissect},

    {0x4c, "Service request", dissect_service_request},
    {0x4d, "Service reject", dissect_service_reject},
    {0x4e, "Service accept", dissect_service_accept},

    {0x4f, "Not used in current version", no_dissect},
    {0x50, "Not used in current version", no_dissect},
    {0x51, "Not used in current version", no_dissect},
    {0x52, "Not used in current version", no_dissect},
    {0x53, "Not used in current version", no_dissect},

    {0x54, "Configuration update command", dissect_configuration_update_command},
    {0x55, "Configuration update complete", dissect_configuration_update_complete},

    {0x56, "Authentication request", dissect_authentication_request},
    {0x57, "Authentication response", dissect_authentication_response},
    {0x58, "Authentication reject", dissect_authentication_reject},
    {0x59, "Authentication failure", dissect_authentication_failure},
    {0x5a, "Authentication result", dissect_authentication_result},

    {0x5b, "Identity request", dissect_identity_request},
    {0x5c, "Identity response", dissect_identity_response},
    {0x5d, "Security mode command", dissect_security_mode_command},
    {0x5e, "Security mode complete", dissect_security_mode_complete},
    {0x5f, "Security mode reject", dissect_security_mode_reject},

    {0x60, "Not used in current version", no_dissect},
    {0x61, "Not used in current version", no_dissect},
    {0x62, "Not used in current version", no_dissect},
    {0x63, "Not used in current version", no_dissect},

    {0x64, "5GMM status", dissect_mm_status},
    {0x65, "Notification", dissect_notification},
    {0x66, "Notification response", dissect_notification_response},
    {0x67, "UL NAS transport", dissect_ul_nas_transport},
    {0x68, "DL NAS transport", dissect_dl_nas_transparent},
    {0, nullptr, nullptr},
};

extern const message_metamessage_desc_t nsm_messages[] = {
    {
        0xc1,
        "PDU session establishment request",
        dissect_pdu_session_establishment_request,
    },
    {
        0xc2,
        "PDU session establishment accept",
        dissect_pdu_session_establishment_accept,
    },
    {
        0xc3,
        "PDU session establishment reject",
        dissect_pdu_session_establishment_reject,

    },

    {
        0xc4,
        "Not used in current version",
        no_dissect,
    },
    {
        0xc5,
        "PDU session authentication command",
        dissect_pdu_session_authentication_command,
    },

    {
        0xc6,
        "PDU session authentication complete",
        dissect_pdu_session_authentication_complete,
    },
    {
        0xc7,
        "PDU session authentication result",
        no_dissect,
    },
    {
        0xc8,
        "Not used in current version",
        no_dissect,
    },

    {
        0xc9,
        "PDU session modification request",
        dissect_pdu_session_modification_request,
    },
    {
        0xca,
        "PDU session modification reject",
        dissect_pdu_session_modification_reject,
    },
    {
        0xcb,
        "PDU session modification command",
        dissect_pdu_session_modification_command,
    },
    {
        0xcc,
        "PDU session modification complete",
        dissect_pdu_session_modification_complete,
    },
    {
        0xcd,
        "PDU session modification command reject",
        dissect_pdu_session_modification_command_reject,
    },

    {
        0xce,
        "Not used in current version",
        no_dissect,
    },
    {
        0xcf,
        "Not used in current version",
        no_dissect,

    },
    {
        0xd0,
        "Not used in current version",
        no_dissect,
    },

    {
        0xd1,
        "PDU session release request",
        dissect_pdu_session_release_request,
    },
    {
        0xd2,
        "PDU session release reject",
        dissect_pdu_session_release_reject,
    },
    {
        0xd3,
        "PDU session release command",
        dissect_pdu_session_release_command,
    },
    {
        0xd4,
        "PDU session release complete",
        dissect_pdu_session_release_complete,
    },

    {
        0xd5,
        "Not used in current version",
        no_dissect,
    },

    {
        0xd6,
        "5GSM status",
        dissect_sm_status,
    },
    {0, nullptr, nullptr},
};
