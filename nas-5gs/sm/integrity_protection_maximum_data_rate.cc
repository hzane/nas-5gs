#include "../dissect_sm_msg.hh"


// Integrity protection maximum data rate   9.11.4.7
extern const element_meta sm::int_prot_max_data_rate = {
    0x13,
    "Integrity protection maximum data rate",
    dissect_int_prot_max_data_rate,
    nullptr,

};
