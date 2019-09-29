#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

/*0	indicates establishment of user-plane resources of the PDU session
 *was not requested in the Uplink data status IE
 *or establishment of user-plane resources of the PDU session
 *was not allowed in the Allowed PDU session status IE
 *or establishment of user-plane resource of the PDU session is successful.
 *1	indicates either establishment of user-plane resources of the PDU session
 *was requested in the Uplink data status IE
 *but establishment of user-plane resource of the PDU session is not successful
 *or indicates establishment of user-plane resources of the PDU session
 *was allowed in the Allowed PDU session status IE but establishment of
 *user-plane resource of the PDU session is either not performed or not successful.
 */

//  *   9.11.3.42    PDU session reactivation result
inline const psi_field psi_0 = {
    "PSI",
    0,
    0,
    "Not requested / not allowed / not successful",
    "Requested / allowed / successful",
};

inline const psi_field psi_8 = {
    "PSI",
    0,
    8,
    "Not requested nor allowed",
    "Requested or Allowed",
};

// PDU session reactivation result   9.11.3.42
int mm::dissect_pdu_session_reactive_result(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-reactivation-result", d, 30);

    d.add_item(&psi_0);
    d.step(1);

    d.add_item(&psi_8);
    d.step(1);

    // 5-34 is optional

    return uc.length;
}
