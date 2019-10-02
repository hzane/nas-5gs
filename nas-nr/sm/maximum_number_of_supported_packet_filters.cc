#include "../common/dissector.hh"
#include "../common/use_context.hh"

//  9.11.4.9    Maximum number of supported packet filters
int dissect_max_number_supported_packet_filter(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "max-nof-supported-packet-filters", -1);

    return 2;
}
