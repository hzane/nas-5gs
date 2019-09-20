#include "../dissect_sm_msg.hh"

// 9.11.4.22	ATSSS container
const field_meta hf_atsss_container = {
    "ATSSS container",
    "nas.nr.atsss.container",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0,
};

// 9.11.4.22	ATSSS container
int dissect_atsss_container(dissector d, context*ctx){
    const use_context uc(ctx, "atsss-container", d, -1);

    (void) d.add_item(d.length, &hf_atsss_container, enc::na);
    d.step(d.length);

    return uc.length;
}
struct atsss_container_t {
    payload_t _;
};
