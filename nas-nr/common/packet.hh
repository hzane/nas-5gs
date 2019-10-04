#pragma once
#include <cstdint>

namespace direction {
inline extern const int unknown = 0;
inline extern const int ul      = 1;
inline extern const int dl      = 2;
} // namespace direction

struct packet {
    uint32_t num           = 0; // frame number
    int64_t  abs_timestamp = 0; // nano seconds
    int64_t  rel_timestamp = 0; // nano seconds
    int      dir           = 0; // direction
};

inline void up_link(packet* pkt) {
    if (pkt) pkt->dir = direction::ul;
}

inline void down_link(packet* pkt) {
    if (pkt) pkt->dir = direction::dl;
}
