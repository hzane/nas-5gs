#include <cstring>
#include "core.hh"
#include "message.hh"
#include "nas.hh"
#include "ber.hh"

int dissect_nsm_message(dissectord, context* ctx, nsm_message_t* v);
int dissect_nmm(dissector, context*, nmm_message_t*);

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


int dissect_nsm_message(dissector d, context* ctx, nsm_message_t* v) {
    const use_context uc(&d, ctx, "session-management-message", 0);

    d.step(dissect_nsm_header(d, ctx, &v->header));

    switch (v->header.message_type) {
    case 0xc1u:

        break;
    default:
        break;
    }

    return uc.length;
}

int dissect_nmm_message(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "mobile-management-message", 0);

    return 0;
}

