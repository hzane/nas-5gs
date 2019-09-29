#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

const tf_string ebitf = {
    "BEARER CONTEXT-ACTIVE",
    "BEARER CONTEXT-INACTIVE",
};

inline const psi_field ebi0={
    "EBI",
    0,
    0,
    ebitf.false_string,
    ebitf.false_string,
};
inline const psi_field ebi1={
    "EBI",
    0,
    8,
    ebitf.false_string,
    ebitf.false_string,
};

/*  9.11.3.59  EPS bearer context status
 * See subclause 9.9.2.1 in 3GPP TS 24.301 [15]. */
int mm::dissect_eps_bearer_context_status(dissector d, context* ctx) {
    const use_context uc(ctx, "eps-bearer-context-status", d, 0);

    /* EBI(7)  EBI(6)  EBI(5)  EBI(4)  EBI(3)  EBI(2)  EBI(1) EBI(0) octet 3 */
    /* EBI(0): Bit 1 of octet 3 is spare and shall be coded as zero. */
    d.add_item(&ebi0);
    d.step(1);

    /* EBI(15) EBI(14) EBI(13) EBI(12) EBI(11) EBI(10) EBI(9) EBI(8) octet 4 */
    d.add_item(&ebi1);
    d.step(1);

    return 2;
}
