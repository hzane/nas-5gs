#pragma once
#include "buff_view.hh"
#include "config.hh"
#include "field_meta.hh"
#include "packet.hh"
#include "proto.hh"

struct protocol_meta {
    const char*   name;
    const char*   full_name;
    dissect_fnc_t dissector;
};

// protocol dissect entry
extern int dissect_nas5g(dissector, context*);

inline const protocol_meta nas_5gs_module = {
    "NAS-5GS",
    "Non-Access-Stratum 5GS (NAS)PDU, References: 3GPP TS 24.501 15.1.0",
    dissect_nas5g,
};

// Extended protocol discriminator
namespace epd {
inline const uint8_t MM5G = 0x7e; // TGPP_PD_5GMM
inline const uint8_t SM5G = 0x2e; // TGPP_PD_5GSM
} // namespace EPD

typedef dissect_fnc_t dissect_msg_fnc_t;

struct message_meta {
    uint8_t           type; // iei
    const char*       name;
    dissect_msg_fnc_t fnc;
};

typedef message_meta element_meta;

inline const char* safe_str(const char* v) { return (v && v[0] != '\n') ? v : ""; }