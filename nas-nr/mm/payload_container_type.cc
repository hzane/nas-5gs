#include "../common/dissector.hh"
#include "../common/use_context.hh"

// Payload container type   9.11.3.40
int dissect_payload_container_type(dissector d, context* ctx) {
    const use_context uc(ctx, "payload-container-type", d, -1);
    return 1;
}
