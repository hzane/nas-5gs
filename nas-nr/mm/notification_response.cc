#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.2.24 Notification response */
int dissect_notification_response(dissector d, context* ctx) {
    const use_context uc(ctx, "notification-response", d, 0);
    // UE to network
    up_link(d.pinfo);

    return uc.length;
}
