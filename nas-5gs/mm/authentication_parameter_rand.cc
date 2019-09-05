#include "../dissect_mm_msg.hh"


/* * 9.11.3.16	Authentication parameter RAND */
int mm::dissect_auth_parm_rand(dissector d, context* ctx) {
    // See subclause 10.5.3.1 in 3GPP TS 24.008 [12].
    /* The RAND value is 16 octets long */
    d.add_item(16, &hf_dtap_rand, enc::be);

    /* no length check possible */
    return 16;
}
