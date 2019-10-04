#include "../common/definitions.hh"
#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/*8.2.28	Security protected 5GS NAS message*/
result_t de_security_protected_nr_nas_message(dissector                         d,
                                              context*                          ctx,
                                              security_protected_nas_message_t* ret) {
    return de_nas_protected(d, ctx, ret);
}