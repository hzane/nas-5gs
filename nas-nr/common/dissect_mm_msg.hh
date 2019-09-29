#pragma once
#include "../mm/mm_dissects.hh"     // NOLINT
#include "../mm/mm_element_meta.hh" // NOLINT
#include "../mm/mm_field_meta.hh"   // NOLINT
#include "common.hh"                // NOLINT
#include "dissect_nas5g.hh"

/* 5GS mobility management messages */
namespace mm {
inline const dissect_fnc_t no_dissect = nullptr;

extern const message_meta      msgs[];

inline const tf_string tfs_requested_not_requested = {
    "Requested",
    "Not Requested",
};

inline const tf_string tfs_odd_even = {
    "Odd number of identity digits",
    "Even number of identity digits",
};

inline const tf_string tfs_requested_or_not = {
    "Requested",
    "Not Requested",
};
} // namespace mm
