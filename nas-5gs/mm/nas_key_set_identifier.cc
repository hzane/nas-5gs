#include "../dissect_mm_msg.hh"

// NAS key set identifier 9.11.3.32
// int dissect_key_set_id(dissector d, context* ctx);

// NAS key set identifier 9.11.3.32
const element_meta mm::key_set_id = {
    0xff,
    "NAS key set identifier - ngKSI",
    dissect_key_set_id,
    nullptr,
};
