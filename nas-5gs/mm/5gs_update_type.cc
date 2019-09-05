#include "../dissect_mm_msg.hh"
// 9.11.3.9A 5GS update type
const element_meta mm::update_type = {
    0x53,
    "5GS update type",
    dissect_update_type,
    nullptr,
};
