#include "../common/dissector.hh"
#include "../common/use_context.hh"

// Extended protocol configuration options  9.11.4.6
int dissect_extended_protocol_configuration_options(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "extended-protocol-conf-options", -1);

    // See subclause 10.5.6.3A in 3GPP TS 24.008

    /* 1 ext 0 0 0 0 Spare  Configuration protocol */

    return uc.length;
}
