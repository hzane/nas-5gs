#pragma once
#include "config.hh"

struct buff_view;
struct packet;
struct proto_node;
struct context;

struct packet {
    uint32_t presence_flags = 0; // some flags
    uint32_t num            = 0; // frame number
    int64_t  abs_ts         = 0; // nano seconds
    int64_t  rel_ts         = 0; // nano seconds
    int      dir            = 0; // direction
};

inline void up_link(packet*pinfo){
    if (pinfo) pinfo->dir = direction::ul;
}

inline void down_link(packet*pinfo){
    if (pinfo) pinfo->dir = direction::dl;
}

inline void both_link(packet*pinfo) {
    if (pinfo) pinfo->dir = direction::both;
}
