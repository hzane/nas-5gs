#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;
using namespace mm;

/*8.2.21 Identity request */
int mm::dissect_identity_request(dissector d, context* ctx) {
    use_context uc(ctx, "identity-request", d, -1);
    // AMF to UE
    down_link(d.packet);

    /* Identity type    5GS identity type 9.11.3.3    M    V    1/2 */
    (void) dissect_identity_type(d, ctx);

    /* Spare half octet    Spare half octet 9.5    M    V    1/2 */

    d.step(1);

    return 1;
}
