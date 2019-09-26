#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.2.1.1    Authentication request */
int dissect_authentication_request(dissector                 d,
                                   context*                  ctx,
                                   authentication_request_t* ret) {
    const use_context uc(ctx, "authentication-request", d, 0);
    down_link(d.pinfo); // network to UE


    return uc.length;
}
