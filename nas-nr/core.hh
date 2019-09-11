#pragma once
#include "config.hh"
#include "tvbuff.hh"
#include "field_meta.hh"
#include "proto.hh"
#include "tree_meta.hh"
#include "packet_info.hh"

namespace em_severity {
inline const int comment = 0;
inline const int chat    = 1;
inline const int note    = 2;
inline const int warn    = 3;
inline const int error   = 4;
} // namespace em_severity

struct expert_meta : field_meta {
    const char* name;
    int         severity; // em_severity
    const char* summary;
};

namespace tree_metas { // tree_metas
inline const tree_meta ett_none     = {"-", nullptr};
inline const tree_meta ett_protocol = {};
inline const tree_meta ett_message  = {};
inline const tree_meta ett_element  = {"Element", nullptr};
inline const tree_meta ett_expert   = {"Expert", nullptr};
inline const tree_meta ett_any      = {};
} // namespace tree_metas

struct protocol_meta {
    const char*   name;
    const char*   full_name;
    dissect_fnc_t dissector;
};

// protocol dissect entry
extern int dissect_nas5g(dissector, context*);

inline const protocol_meta nas_5gs_module = {
    "NAS-5GS",
    "Non-Access-Stratum 5GS (NAS)PDU",
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
    const char*       alias;
};

typedef message_meta element_meta;

inline const char* safe_str(const char* v) { return (v && v[0] != '\n') ? v : ""; }

string w2utf8(std::wstring const& w);
