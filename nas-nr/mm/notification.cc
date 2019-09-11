#include "../dissect_mm_msg.hh"
#include "../ber.hh"

using namespace nas;

/*  8.2.23 Notification */
int mm::dissect_notification(dissector d, context* ctx) {
    const use_context uc(ctx, "notification", d, -1);
    // network to UE
    down_link(d.pinfo);

    /* Access type    Access type 9.11.3.11    M    V    1/2  */        
    const auto consumed = dissect_access_type(d, ctx);
    d.step(consumed);

    /* Spare half octet    Spare half octet 9.5    M    V    1/2  */

    d.step(1);
    
    return 1;
}
