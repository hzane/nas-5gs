#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

const bool_field hf_cpoi = {
    "Control plane only indication value (CPOI)",
    0x01u,
    "reserved",
    "PDU session can be used for control plane CIoT 5GS optimization only",
    };

// Control plane only indication 9.11.4.23
int sm::dissect_control_plane_only_indication(dissector d, context*ctx){
    const use_context uc(ctx, "control-plane-only-indication", d, -1);

    (void) d.add_item(&hf_cpoi);
    d.step(1);

    return 1;
}
