#pragma once
#include "config.hh"
#include "tvbuff.hh"

namespace pi_dir {
__declspec(selectany) extern const int unknown = 0;
__declspec(selectany) extern const int ul = 1;
__declspec(selectany) extern const int dl = 2;
} // namespace pi_dir

struct packet_info {
    const char* current_proto;
    uint32_t    presence_flags; // some flags
    uint32_t    num;            // frame number
    int64_t     abs_ts;
    int64_t     rel_ts;
    int         dir; // pi_dir
};
