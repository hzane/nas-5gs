#pragma once
#include "config.hh"

struct tvbuff {
    // may be null, if zero-length, or lazily constructed
    const uint8_t *data = nullptr;

    /** Amount of data that's available from the capture
     * file.  This is the length of virtual buffer (and/or
     * real_data).  It may be less than the reported
     * length if this is from a packet that was cut short
     * by the capture process.
     *
     * This must never be > reported_length or contained_length. */
    int length = 0;

    /** Amount of data that was reported as being in
     * the packet or other data that this represents.
     * As indicated above, it may be greater than the
     * amount of data that's available. */
    int reported_length = 0;

    tvbuff(const uint8_t *data, int len)
        : data(data), length(len), reported_length(len) {}

    inline uint16_t get_ntohs(int offset) {
        return (offset + 2) <= length ? n2uint16(data + offset) : 0;
    };
    uint32_t get_ntoh24(int offset) {
        return (offset + 3) <= length ? n2uint24(data + offset) : 0;
    }
    uint32_t get_ntoh32(int offset) {
        return (offset + 4) <= length ? n2uint32(data + offset) : 0;
    }
    uint64_t get_ntoh48(int offset) {
        return (offset + 6) <= length ? n2uint48(data + offset) : 0;
    }
    uint64_t get_ntoh64(int offset) {
        return (offset + 8) <= length ? n2uint64(data + offset) : 0;
    }
    uint8_t get_uint8(int offset) const { return offset < length ? data[offset] : 0; }
    uint8_t get_uint7(int offset) const { return get_uint8(offset) & 0x7f; }
    int     remain(int offset) const { return length - offset; }
};


/** A "real" tvbuff contains a uint8* that points to real data.
 * The data is allocated and contiguous.
 *
 * A "subset" tvbuff has a backing tvbuff. It is a "window" through
 * which the program sees only a portion of the backing tvbuff.
 *
 * tvbuff's of any type can be used as the backing-tvbuff of a
 * "subset" tvbuff or as a member of a "composite" tvbuff.
 * "composite" tvbuffs can have member-tvbuffs of different types.
 *
 * Once a tvbuff is create/initialized/finalized, the tvbuff is read-only.
 * That is, it cannot point to any other data. A new tvbuff must be created if
 * you want a tvbuff that points to other data.
 *
 */
