#include "dissector.hh"
#include "use_context.hh"

/* 9.11.2.8    S-NSSAI */
int dissect_s_nssai(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "s-nssai", 0);

    /* SST    octet 3
     * This field contains the 8 bit SST value. The coding of the SST value part is
     * defined in 3GPP TS 23.003
     */

    return uc.length;
}
