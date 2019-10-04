#include "dissects.hh"

#include <cstring>

#include "ber.hh"
#include "core.hh"
#include "definitions.hh"
#include "dissects.hh"
#include "ies.hh"
#include "message.hh"
#include "messages.hh"
#include "nas.hh"

int result_t::step(dissector&d)const{
    d.step(consumed);
    return consumed;
}

result_t de_nas_message(dissector d, context* ctx, nas_message_t* v) {
    /* 9.2 Extended protocol discriminator  octet 1 */
    auto epd = d.uint8(false);

    // Security header type (octet 1)
    const auto security_type = d.uint8(false, 1) & 0x0fu;

    if (epd == epd::nsm || security_type == 0) {
        v->plain=std::make_shared<nas_message_plain_t>();
        return de_nas_plain(d, ctx, v->plain.get());
    }
    v->protect = std::make_shared<nas_message_protected_t>();
    return de_nas_protected(d, ctx, v->protect.get());
}

result_t dissect_nas_protected(dissector d, context* ctx, nas_message_protected_t* v) {
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
    de_nas_plain(d, ctx, &v->plain).step(d);

    return {uc.length};
}

/* Plain NAS 5GS Message */
result_t dissect_nas_plain(dissector d, context* ctx, nas_message_plain_t* v) {
    const use_context uc(&d, ctx, "plain-nas-message", 0);

    /* Extended protocol discriminator  octet 1 */
    const auto epd = d.uint8(false);

    if (epd == epd::nmm) {
        v->nmm = std::make_shared<nmm_message_t>();
        de_nmm_message(d, ctx, v->nmm.get()).step(d);
    } else if (epd == epd::nsm) {
        v->nsm = std::make_shared<nsm_message_t>();
        de_nsm_message(d, ctx, v->nsm.get()).step(d);
    } else {
        diag("unknown epd %d\n", epd);
    }

    return {uc.length};
}

struct message_desc_t {
    using dissect_t = int (*)(dissector, context*, void* ret);
    uint8_t     type;
    const char* name;
    dissect_t   dissect;
};

#define DISSECT(mt, X)                              \
    case mt:                                        \
        v-> X = std::make_shared< X##_t >();     \
        (void) de_##X(d, ctx, (v-> X).get()); \
        break;

result_t dissect_nsm_message(dissector d, context* ctx, nsm_message_t* v) {
    const use_context uc(&d, ctx, "session-management-message", 0);

    de_nsm_header(d, ctx, &v->header);

    switch (v->header.message_type) {
    case 0xc4:
        v->pdu_session_establishment_request = std::make_shared<pdu_session_establishment_request_t>();
        break;
        DISSECT(0xc1u, pdu_session_establishment_request);
        DISSECT(0xc2u, pdu_session_establishment_accept);
        DISSECT(0xc3u, pdu_session_establishment_reject);
        DISSECT(0xc5u, pdu_session_authentication_command);
        DISSECT(0xc6u, pdu_session_authentication_complete);
        DISSECT(0xc9u, pdu_session_modification_request);
        DISSECT(0xcau, pdu_session_modification_reject);
        DISSECT(0xccu, pdu_session_modification_complete);
        DISSECT(0xcdu, pdu_session_modification_command_reject);
        DISSECT(0xd1u, pdu_session_release_request);
        DISSECT(0xd2u, pdu_session_release_reject);
        DISSECT(0xd3u, pdu_session_release_command);
        DISSECT(0xd4u, pdu_session_release_complete);
        DISSECT(0xd6u, nsm_status);
    default:
        break;
    }

    return {uc.length};
}

extern const message_desc_t nmm_messages[];
result_t dissect_nmm_message(dissector d, context* ctx, nmm_message_t* v) {
    const use_context uc(&d, ctx, "mobile-management-message", 0);

    de_nmm_header(d, ctx, &v->header);
    switch(v->header.message_type){
        DISSECT(0x41, registration_request);
        DISSECT(0x42, registration_accept);
        DISSECT(0x43, registration_complete);
        DISSECT(0x44, registration_reject);
        DISSECT(0x45, deregistration_request_ue_orig);
        DISSECT(0x46, deregistration_accept_ue_orig);
        DISSECT(0x47, deregistration_request_ue_term);
        DISSECT(0x48, deregistration_accept_ue_term);
        DISSECT(0x4c, service_request);
        DISSECT(0x4d, service_reject);
        DISSECT(0x4e, service_accept);
        DISSECT(0x54, configuration_update_command);
        DISSECT(0x55, configuration_update_complete);
        DISSECT(0x56, authentication_request);
        DISSECT(0x57, authentication_response);
        DISSECT(0x58, authentication_reject);
        DISSECT(0x59, authentication_failure);
        DISSECT(0x5a, authentication_result);
        DISSECT(0x5b, identity_request);
        DISSECT(0x5c, identity_response);
        DISSECT(0x5d, security_mode_command);
        DISSECT(0x5e, security_mode_complete);
        DISSECT(0x5f, security_mode_reject);
        DISSECT(0x64, nmm_status);
        DISSECT(0x65, notification);
        DISSECT(0x66, notification_response);
        DISSECT(0x67, ul_nas_transport);
        DISSECT(0x68, dl_nas_transport);
    default:
        break;
    }
    return {0};
}

result_t de_nsm_header(dissector d, context* ctx, nsm_header_t* ret) {
    ret->epd            = d.uint8();
    ret->pdu_session_id = d.uint8();
    ret->pti            = d.uint8();
    ret->message_type   = d.uint8();
    return {4};
}

result_t de_nmm_header(dissector d, context* ctx, nmm_header_t* ret) {
    ret->epd                  = d.uint8();
    ret->security_header_type = d.uint8() & 0x0fu;
    ret->message_type         = d.uint8();
    return {3};
}
