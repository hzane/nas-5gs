#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

static const psi_field uppsi_a = {
    "PSI",
    0xffu,
    0,
    "Not supported",
    "Supported",
};

static const psi_field uppsi_b = {
    "PSI",
    0xffu,
    8,
    "Not supported",
    "Supported",
};

/*40    Uplink data status    Uplink data status 9.11.3.57    O    TLV    4-34 */
int mm::dissect_uplink_data_status(dissector d, context* ctx) {
    const use_context        uc(ctx, "uplink-data-status", d, -1);

    d.add_item(&uppsi_a);
    d.step(1);

    d.add_item(&uppsi_b);
    d.step(1);

    return 2;
}
