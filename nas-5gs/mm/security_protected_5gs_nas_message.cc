#include "../dissect_mm_msg.hh"
#include "../gsm.hh"
#include "../ber.hh"

using namespace cmn;
using namespace mm;
using namespace nas;

/*8.2.28	Security protected 5GS NAS message*/
int mm::dissect_security_protected_5gs_nas_msg(dissector d, context* ctx) {
    return dissect_nas5g_security_protected(d, ctx);
}
