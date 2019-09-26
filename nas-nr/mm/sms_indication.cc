#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  9.11.3.50A    SMS indication */
int dissect_sms_indication(dissector d, context* ctx) {
    const use_context uc(ctx, "sms-indication", d, -1);


    return 1;
}
