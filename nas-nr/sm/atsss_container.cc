#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

// 9.11.4.22	ATSSS container
const octet_field hf_atsss_container = {
    "ATSSS container",
};

// 9.11.4.22	ATSSS container
int dissect_atsss_container(dissector d, context*ctx){
    const use_context uc(ctx, "atsss-container", d, -1);

    (void) d.add_item(d.length, &hf_atsss_container);
    d.step(d.length);

    return uc.length;
}
