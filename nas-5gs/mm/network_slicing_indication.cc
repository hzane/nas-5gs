#include "../dissect_mm_msg.hh"


// Network slicing indication  9.11.3.36
extern const element_meta mm::nw_slicing_ind = {
    0x90,
    "Network slicing indication",
    mm::dissect_nw_slicing_ind,
    nullptr,
};

