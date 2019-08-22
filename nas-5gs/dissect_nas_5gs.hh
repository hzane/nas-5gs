#pragma once
#include "core.hh"
extern const field_meta* hf_nas_5gs_msg_elems ;

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




