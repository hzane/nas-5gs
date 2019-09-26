#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*8.2.28	Security protected 5GS NAS message*/
int dissect_security_protected_5gs_nas_msg(dissector d, context* ctx) {
    return dissect_nas5g_security_protected(d, ctx);
}
