#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace mm;

// Allowed PDU session status
const element_meta mm::allowed_pdu_session_status = {
    0x25,
    "Allowed PDU session status",
    dissect_allowed_pdu_session_status,
};
inline const psi_field hf_psi={
    "PSI",
    0,
    0,
    "user-plane resources of corresponding PDU session "
    "is not allowed to be re-established over 3GPP access",
    "user-plane resources of corresponding PDU session "
    "can be re-established over 3GPP access",
};
inline const psi_field hf_psi_b={
    "PSI",
    0,
    8,
    "user-plane resources of corresponding PDU session "
    "is not allowed to be re-established over 3GPP access",
    "user-plane resources of corresponding PDU session "
    "can be re-established over 3GPP access",
};

/*  9.11.3.13    Allowed PDU session status */
int mm::dissect_allowed_pdu_session_status(dissector d, context* ctx) {
    const use_context uc(ctx, "allowed-pdu-session-status", d, 30);

    d.add_item(&hf_psi);
    d.step(1);

    d.add_item(&hf_psi_b);
    d.step(1);

    // All bits in octet 5 to 34 are spare and shall be coded as zero, if the respective
    // octet is included in the information element.

    return uc.length;
}

