#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  8.2.23 Notification */
int dissect_notification(dissector d, context* ctx) {
    const use_context uc(ctx, "notification", d, -1);
    // network to UE
    down_link(d.pinfo);


    return 1;
}
