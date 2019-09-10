#include "../dissect_mm_msg.hh"

// 9.11.3.2	5GMM cause
extern const element_meta mm::mm_cause = {
    0x58,
    nullptr,
    dissect_mm_cause,
    nullptr,
};

// 9.11.3.2	5GMM cause
int mm::dissect_mm_cause(dissector d, context* ctx) {
    const use_context uc(ctx, "5gmm-cause", d, -1);

    (void) d.add_item(1, &hf_mm_cause, enc::be);
    d.step(1);
    
    return 1;
}

namespace mm {
/* * 9.11.3.2 5GMM cause */
extern const val_string mm_cause_values[] = {
    {0x03, "Illegal UE"},
    {0x05, "PEI not accepted"},
    {0x06, "Illegal ME"},
    {0x07, "5GS services not allowed"},
    {0x09, "UE identity cannot be derived by the network"},
    {0x0a, "Implicitly deregistered"},
    {0x0b, "PLMN not allowed"},
    {0x0c, "Tracking area not allowed"},
    {0x0d, "Roaming not allowed in this tracking area"},
    {0x0f, "No suitable cells in tracking area"},
    {0x14, "MAC failure"},
    {0x15, "Synch failure"},
    {0x16, "Congestion"},
    {0x17, "UE security capabilities mismatch"},
    {0x18, "Security mode rejected, unspecified"},
    {0x1a, "Non-5G authentication unacceptable"},
    {0x1b, "N1 mode not allowed"},
    {0x1c, "Restricted service area"},
    {0x2b, "LADN not available"},
    {0x41, "Maximum number of PDU sessions reached"},
    {0x43, "Insufficient resources for specific slice and DNN"},
    {0x45, "Insufficient resources for specific slice"},
    {0x47, "ngKSI already in use"},
    {0x48, "Non-3GPP access to 5GCN not allowed"},
    {0x49, "Serving network not authorized"},
    {0x5a, "Payload was not forwarded"},
    {0x5b, "DNN not supported or not subscribed in the slice"},
    {0x5c, "Insufficient user-plane resources for the PDU session"},
    {0x5f, "Semantically incorrect message"},
    {0x60, "Invalid mandatory information"},
    {0x61, "Message type non-existent or not implemented"},
    {0x62, "Message type not compatible with the protocol state"},
    {0x63, "Information element non-existent or not implemented"},
    {0x64, "Conditional IE error"},
    {0x65, "Message not compatible with the protocol state"},
    {0x6f, "Protocol error, unspecified"},
    {0, nullptr},
};
}
// 5GMM cause   9.11.3.2
const field_meta mm::hf_mm_cause = {
    "5GMM cause",
    "nas_5gs.mm.5gmm_cause",
    ft::ft_uint8,
    fd::base_dec,
    mm_cause_values,
    nullptr,
    nullptr,
    0x0,
};

