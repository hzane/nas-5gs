#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

/* 9.11.3.44    PDU session status  */
namespace mm {

inline const psi_field status_psi_1 = {
    "PSI",
    0xffu,
    0,
    "PDU SESSION INACTIVE",
    "Not PDU SESSION INACTIVE",
};

inline const psi_field status_psi_8 = {
    "PSI",
    0xffu,
    8,
    "PDU SESSION INACTIVE",
    "Not PDU SESSION INACTIVE",
};
} // namespace mm

// PDU session status   9.11.3.44
int mm::dissect_pdu_session_status(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-status", d, 30);

    d.add_item(&status_psi_1);
    d.step(1);

    d.add_item(&status_psi_8);
    d.step(1);

    // All bits in octet 5 to 34 are spare and shall be coded as zero,
    // if the respective octet is included in the information element
    return uc.length;
}
