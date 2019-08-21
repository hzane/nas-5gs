#pragma once
#include <cstdarg>
#include <string>
#include "config.hh"
#include "packet_info.hh"
#include "proto.hh"
#include "tvbuff.hh"
#include "field_meta.hh"

extern void nas_5gs_module_init();
extern void nas_5gs_module_cleanup();
extern void bug(const char* format, ...);

struct context {
    const char*  msg_name;
    const char*  elem_name;
    const char*  field_name;
};

namespace em_severity {
__declspec(selectany) extern const int comment = 0;
__declspec(selectany) extern const int chat    = 1;
__declspec(selectany) extern const int note    = 2;
__declspec(selectany) extern const int warn    = 3;
__declspec(selectany) extern const int error   = 4;
} // namespace em_severity

struct expert_meta : field_meta {
    const char* name;
    int         severity;  // em_severity
    const char* summary;
};


struct tree_meta {
    const char* name;
};

namespace tree_metas { // tree_metas
__declspec(selectany) extern const tree_meta ett_none     = {};
__declspec(selectany) extern const tree_meta ett_protocol = {};
__declspec(selectany) extern const tree_meta ett_message  = {};
__declspec(selectany) extern const tree_meta ett_element  = {};
__declspec(selectany) extern const tree_meta ett_expert   = {};
__declspec(selectany) extern const tree_meta ett_any      = {};
} // namespace tm

struct protocol_meta {
    const char*      name;
    const char*      full_name;
    dissect_fnc_t    dissector;
};

extern int dissect_nas_5gs(packet_info*, proto_node*, tvbuff*, int, int, context*);

__declspec(selectany) extern const protocol_meta nas_5gs_module = {
    "NAS-5GS",
    "Non-Access-Stratum 5GS (NAS)PDU",
    dissect_nas_5gs,
};
namespace TGPP_PD{
__declspec(selectany) extern const uint8_t MM5G = 0x7e; //TGPP_PD_5GMM
__declspec(selectany) extern const uint8_t SM5G = 0x2e; //TGPP_PD_5GSM
}

struct message_meta {
    uint8_t           type; // iei
    const char*       name;
    dissect_msg_fnc_t fnc;
};

typedef message_meta element_meta;

inline const char* safe_str(const char* v) { return (v && v[0] != '\n') ? v : ""; }

inline void extraneous_data_check(packet_info* pinfo,
                           proto_node*  tree,
                           tvbuff*      tvb,
                           int          offset,
                           int          len,
                           int          maxlen) {
    if (len >maxlen){
        tree->add_expert(pinfo,
                         tvb,
                         offset,
                         len - maxlen,
                         "extraneous data (%d) bytes",
                         (len - maxlen));
    }
}
