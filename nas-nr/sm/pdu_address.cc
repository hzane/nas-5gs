#include "../common/dissector.hh"
#include "../common/use_context.hh"

// PDU address 9.11.4.10 15 octets
int dissect_pdu_address(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-address", d, 8);

    return uc.length;
}
