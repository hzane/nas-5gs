#pragma once
#include "core.hh"
#include "field_meta.hh"

// dissect_msg_fnc_t
int dissect_sm_msg(dissector d, context* ctx);
int dissect_mm_msg(dissector d, context* ctx);

int dissect_nas5g_plain(dissector d, context* ctx);
int dissect_nas5g_security_protected(dissector d, context* ctx);

const message_meta* find_dissector(uint8_t iei, const message_meta* meta);

namespace nas {

inline extern const tf_string tfs_supported_not_supported = {
    "Supported",
    "Not supported",
};

inline extern const tf_string tfs_allowed_not_allowed = {
    "Allowed",
    "Not Allowed",
};
} // namespace nas
