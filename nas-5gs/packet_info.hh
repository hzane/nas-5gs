#pragma once
#include "config.hh"
#include "tvbuff.hh"
#include <map>
#include <memory>

struct tvbuff;
struct packet_info;
struct proto_node;
struct context;


namespace pi_dir {
__declspec(selectany) extern const int unknown = 0;
__declspec(selectany) extern const int ul      = 1;
__declspec(selectany) extern const int dl      = 2;
__declspec(selectany) extern const int both    = 3;
} // namespace pi_dir

struct packet_info {
    uint32_t                          presence_flags; // some flags
    uint32_t                          num;            // frame number
    int64_t                           abs_ts;         //
    int64_t                           rel_ts; //
    int                               dir;    // pi_dir
    uint8_t                           payload_content_type = 0; // for payload content
    // std::map< std::string, uint64_t > i_privates;
};
inline void up_link(packet_info*pinfo){
    if (pinfo) pinfo->dir = pi_dir::ul;
}
inline void down_link(packet_info*pinfo){
    if (pinfo) pinfo->dir = pi_dir::dl;
}

inline void store_payload_content_type(packet_info* pinfo, uint8_t pct) {
    if (pinfo)pinfo->payload_content_type = pct;
}
inline uint8_t retrive_payload_content_type(packet_info* pinfo) {
    return pinfo ? pinfo->payload_content_type : 0;
}
