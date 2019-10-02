#include "../common/dissector.hh"
#include "../common/use_context.hh"

// Control plane only indication 9.11.4.23
int dissect_control_plane_only_indication(dissector d, context*ctx){
    const use_context uc(&d, ctx, "control-plane-only-indication", -1);

    return 1;
}
