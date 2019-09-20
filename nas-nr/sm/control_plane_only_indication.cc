#include "../dissect_sm_msg.hh"

const tf_string tfs_cpoi = {
    "PDU session can be used for control plane CIoT 5GS optimization only",
    "reserved",
};

const field_meta hf_cpoi = {
    "Control plane only indication value (CPOI)",
    "nas.nr.sm.cpoi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_cpoi,
    nullptr,
    0x01u,
};

// Control plane only indication 9.11.4.23
int sm::dissect_control_plane_only_indication(dissector d, context*ctx){
    const use_context uc(ctx, "control-plane-only-indication", d, -1);

    (void) d.add_item(1, &hf_cpoi, enc::be);
    d.step(1);

    return 1;
}
// XX Control plane only indication 9.11.4.23	O	TV	1
const element_meta sm::control_plane_only_indication  = {
    0xffu,
    "Control plane only indication",
    sm::dissect_control_plane_only_indication, nullptr,
};

struct control_plane_only_indication_t {
    uint8_t indication;
};
