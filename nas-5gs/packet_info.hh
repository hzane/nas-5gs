#pragma once
#include "config.hh"

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
    uint32_t presence_flags = 0; // some flags
    uint32_t num            = 0; // frame number
    int64_t  abs_ts         = 0; //
    int64_t  rel_ts         = 0; //
    int      dir            = 0; // pi_dir
    // uint8_t                           payload_content_type = 0; // for payload content
    // std::map< std::string, uint64_t > i_privates;
};
inline void up_link(packet_info*pinfo){
    if (pinfo) pinfo->dir = pi_dir::ul;
}
inline void down_link(packet_info*pinfo){
    if (pinfo) pinfo->dir = pi_dir::dl;
}

