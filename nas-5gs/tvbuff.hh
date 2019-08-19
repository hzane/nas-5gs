#pragma once
#include "config.hh"

/**
 * "testy, virtual(-izable) buffer".  They are testy in that they get mad when
 * an attempt is made to access data beyond the bounds of their array. In that
 * case, they throw an exception.
 *
 * They are virtualizable in that new tvbuff's can be made from other tvbuffs,
 * while only the original tvbuff may have data. That is, the new tvbuff has
 * virtual data.
 */
struct tvbuff {
    bool     initialized = true;
    uint32_t flags       = 0;
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

    uint8_t get_uint8(int offset) const { return data[offset]; }
    int     remain(int offset) const { return length - offset; }
};

/** @defgroup tvbuff Testy, Virtual(-izable) Buffers
 *
 * Dissector use and management
 *
 *  Consider a collection of tvbs as being a chain or stack of tvbs.
 *
 *  When dissecting a frame:
 *   The top-level dissector (packet.c) pushes the initial tvb (containing
 *   the complete frame) onto the stack (starts the chain) and then calls
 *   a sub-dissector which in turn calls the next sub-dissector and so on.
 *   Each sub-dissector may chain additional tvbs (see below) to the tvb
 *   handed to that dissector. After dissection is complete and control has
 *   returned to the top-level dissector, the chain of tvbs (stack) is free'd
 *   via a call to tvb_free_chain() (in epan_dissect_cleanup()).
 *
 * A dissector:
 *  - Can chain new tvbs (subset, real, composite) to the
 *    tvb handed to the dissector using tvb_new_subset_length_caplen(),
 *    tvb_new_subset_length(), tvb_new_subset_remaining(),
 *    tvb_new_child_real_data(), tvb_set_child_real_data_tvbuff(),
 *    tvb_composite_finalize(), and tvb_child_uncompress(). (Composite
 *    tvbs should reference only tvbs which are already part of the chain).
 *  - Must not save for later use (e.g., when dissecting another frame) a
 *    pointer to a tvb handed to the dissector; (A higher level function
 *    may very well free the chain thus leaving a dangling pointer).
 *    This (obviously) also applies to any tvbs chained to the tvb handed
 *    to the dissector.
 *  - Can create its own tvb chain (using tvb_new_real_data() which the
 *
 *    dissector is free to manage as desired.
 * @{
 */

/** A "real" tvbuff contains a guint8* that points to real data.
 * The data is allocated and contiguous.
 *
 * A "subset" tvbuff has a backing tvbuff. It is a "window" through
 * which the program sees only a portion of the backing tvbuff.
 *
 * A "composite" tvbuff combines multiple tvbuffs sequentially to
 * produce a larger byte array.
 *
 * tvbuff's of any type can be used as the backing-tvbuff of a
 * "subset" tvbuff or as a member of a "composite" tvbuff.
 * "composite" tvbuffs can have member-tvbuffs of different types.
 *
 * Once a tvbuff is create/initialized/finalized, the tvbuff is read-only.
 * That is, it cannot point to any other data. A new tvbuff must be created if
 * you want a tvbuff that points to other data.
 *
 * tvbuff's are normally chained together to allow efficient de-allocation of
 * tvbuff's.
 */
