#pragma once
#include "core.hh"
extern const field_meta* hf_nas_5gs_msg_elems ;

// dissect_msg_fnc_t
int dissect_sm_msg(packet_info* pinfo,
                   proto_node*  tree,
                   tvbuff*      buf,
                   int          offset,
                   int          len,
                   context*     ctx = nullptr);
int dissect_mm_msg(packet_info* info,
                   proto_node*  tree,
                   tvbuff*      buf,
                   int          offset,
                   int          len,
                   context* ctx= nullptr);

// protocol dissect entry
int dissect_nas_5gs(packet_info* info,
                    proto_node*  tree,
                    tvbuff*      buf,
                    int          offset,
                    int          len,
                    context*     ctx = nullptr);

int dissect_nas_5gs_plain(packet_info* info,
                          proto_node*  tree,
                          tvbuff*      buf,
                          int          offset,
                          int          len,
                          context*     ctx = nullptr);

inline const message_meta* find_dissector(uint8_t iei, const message_meta* meta){
    while(meta->type){
        if (meta->type == iei) return meta;
        meta++;
    }
    return nullptr;
}

