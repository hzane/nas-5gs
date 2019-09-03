#pragma once
#include <cstdarg>
#include <string>
#include <vector>
#include "config.hh"
#include "field_meta.hh"
#include "packet_info.hh"
#include "proto.hh"
#include "range_string.hh"
#include "tree_meta.hh"
#include "tvbuff.hh"

namespace em_severity {
__declspec(selectany) extern const int comment = 0;
__declspec(selectany) extern const int chat    = 1;
__declspec(selectany) extern const int note    = 2;
__declspec(selectany) extern const int warn    = 3;
__declspec(selectany) extern const int error   = 4;
} // namespace em_severity

struct expert_meta : field_meta {
    const char* name;
    int         severity; // em_severity
    const char* summary;
};

namespace tree_metas { // tree_metas
__declspec(selectany) extern const tree_meta ett_none     = {"-", nullptr};
__declspec(selectany) extern const tree_meta ett_protocol = {};
__declspec(selectany) extern const tree_meta ett_message  = {};
__declspec(selectany) extern const tree_meta ett_element  = {"Element", nullptr};
__declspec(selectany) extern const tree_meta ett_expert   = {"Expert", nullptr};
__declspec(selectany) extern const tree_meta ett_any      = {};
} // namespace tree_metas

struct protocol_meta {
    const char*   name;
    const char*   full_name;
    dissect_fnc_t dissector;
};

// protocol dissect entry
extern int dissect_nas5g(dissector, context*);

__declspec(selectany) extern const protocol_meta nas_5gs_module = {
    "NAS-5GS",
    "Non-Access-Stratum 5GS (NAS)PDU",
    dissect_nas5g,
};

// Extended protocol discriminator
namespace EPD {
__declspec(selectany) extern const uint8_t MM5G = 0x7e; // TGPP_PD_5GMM
__declspec(selectany) extern const uint8_t SM5G = 0x2e; // TGPP_PD_5GSM
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
