#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  8.2.9 Registration reject */
int dissect_registration_reject(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "registration-reject", 0);
    //network to UE
    down_link(d.pinfo);

    /* 5GMM cause   9.11.3.2  M   V   1 */

    return uc.length;
}
