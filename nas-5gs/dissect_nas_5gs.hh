#pragma once
#include "core.hh"

// protocol dissect entry
int dissect_nas_5gs(dissector d, context* ctx = nullptr);

// dissect_msg_fnc_t
int dissect_sm_msg(dissector d, context* ctx = nullptr);
int dissect_mm_msg(dissector d, context* ctx = nullptr);

int dissect_nas_5gs_plain(dissector d, context* ctx = nullptr);

inline const message_meta* find_dissector(uint8_t iei, const message_meta* meta){
    while(meta->type){
        if (meta->type == iei) return meta;
        meta++;
    }
    return nullptr;
}


namespace nas_meta{
extern const field_meta* hf_msg_elem;
extern const field_meta* hf_spare_half_octet;
extern const field_meta* hf_epd;
extern const field_meta* hf_pdu_session_id;
extern const field_meta* hf_mm_msg_type;
extern const field_meta* hf_sm_msg_type;
extern const field_meta* hf_sec_header_type;
} // namespace nas_meta
