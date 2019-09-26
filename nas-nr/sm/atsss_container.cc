#include "../common/dissector.hh"
#include "../common/use_context.hh"

// 9.11.4.22	ATSSS container
int dissect_atsss_container(dissector d, context*ctx){
    const use_context uc(ctx, "atsss-container", d, -1);

    return uc.length;
}
