#include "../dissect_mm_msg.hh"

// Payload container  9.11.3.39
// int dissect_pld_cont(dissector d, context* ctx = nullptr);

// Payload container  9.11.3.39
const element_meta mm::pld_cont = {
    0x7B,
    "Payload container",
    dissect_pld_cont,
    nullptr,
};

