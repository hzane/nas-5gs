#pragma once
#include "../sm/sm_dissects.hh"
#include "../sm/sm_element_meta.hh"
#include "../sm/sm_field_meta.hh"
#include "common.hh"
#include "config.hh"
#include "core.hh"
#include "dissect_nas5g.hh"

struct context;

/* 5GS session management messages */
namespace sm {
inline const dissect_fnc_t no_dissect = nullptr;
extern const message_meta      msgs[];

inline const tf_string tfs_allowed_not_allowed = {
    "Allowed",
    "Not Allowed",
};

} // namespace sm
