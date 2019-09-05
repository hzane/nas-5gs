#include "../dissect_mm_msg.hh"

// SOR transparent container   9.11.3.51
// int dissect_sor_trans_cont(dissector d, context* ctx = nullptr);

// SOR transparent container   9.11.3.51
const element_meta mm::sor_trans_cont = {
    0x73,
    "SOR transparent container",
    dissect_sor_trans_cont,
    nullptr,
};
