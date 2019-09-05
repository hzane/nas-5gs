#include "../dissect_mm_msg.hh"


//  9.11.3.46    Rejected NSSAI
extern const element_meta mm::rej_nssai = {
    0x11,
    "Rejected NSSAI",
    dissect_rejected_nssai,
    nullptr,
};

// Configured NSSAI    NSSAI 9.11.3.37
extern const element_meta mm::configured_nssai = {
    0x31,
    "Configured NSSAI",
    dissect_configured_nssai,
    nullptr,
};
