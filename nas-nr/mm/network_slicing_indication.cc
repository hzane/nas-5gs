#include "../common/dissector.hh"
#include "../common/use_context.hh"

//  9.11.3.36    Network slicing indication
int dissect_network_slicing_indicationication(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "nw-slicing-indication", -1);

    return 1;
}
