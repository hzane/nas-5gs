#pragma once
#include "config.hh"

struct tvbuff;
struct packet_info;
struct proto_node;
struct context;


namespace direction {
NASNR_INLINE const int unknown = 0;
NASNR_INLINE const int ul      = 1;
NASNR_INLINE const int dl      = 2;
NASNR_INLINE const int both    = 3;
} // namespace direction

struct packet_info {
    uint32_t presence_flags NASNR_EQUAL_INIT( 0); // some flags
    uint32_t num            NASNR_EQUAL_INIT( 0); // frame number
    int64_t  abs_ts         NASNR_EQUAL_INIT( 0); // nano seconds
    int64_t  rel_ts         NASNR_EQUAL_INIT( 0); // nano seconds
    int      dir            NASNR_EQUAL_INIT( 0); // direction
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
