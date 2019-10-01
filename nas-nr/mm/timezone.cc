#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"


using namespace nas;
using namespace mm;


const timezone_field hf_timezone = {
    "Time Zone",
};

/* 3GPP TS 23.040 version 6.6.0 Release 6
 * 10.5.3.8 Time Zone  in 3GPP TS 24.008 [12]*/
int mm::dissect_timezone_set(dissector d, context* ctx) {
    const use_context uc(ctx, "local-time-zone", d, -1);

    /* 3GPP TS 23.040 version 6.6.0 Release 6
     * 9.2.3.11 TP-Service-Centre-Time-Stamp (TP-SCTS)
     */

    d.set_item(1, gmt_string(d.ptr()));
    d.step(1);

    /* no length check possible */
    return 1;
}
