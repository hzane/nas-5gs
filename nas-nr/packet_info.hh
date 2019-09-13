#pragma once
#include "config.hh"

struct tvbuff;
struct packet_info;
struct proto_node;
struct context;


namespace direction {
inline extern const int unknown = 0;
inline extern const int ul      = 1;
inline extern const int dl      = 2;
inline extern const int both    = 3;
} // namespace direction

struct packet_info {
    uint32_t presence_flags = 0; // some flags
    uint32_t num            = 0; // frame number
    int64_t  abs_ts         = 0; // nano seconds
    int64_t  rel_ts         = 0; // nano seconds
    int      dir            = 0; // direction
};
inline void up_link(packet_info*pinfo){
    if (pinfo) pinfo->dir = direction::ul;
}
inline void down_link(packet_info*pinfo){
    if (pinfo) pinfo->dir = direction::dl;
}

inline void both_link(packet_info*pinfo) {
    if (pinfo) pinfo->dir = direction::both;
}
