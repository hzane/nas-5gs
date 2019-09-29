#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace mm;
using namespace nas;

/* 9.11.3.18    Configuration update indication */
int mm::dissect_configuration_update_indication(dissector d, context* ctx) {
    const use_context        uc(ctx, "configuration-update-indication", d, -1);

    d.add_item(&hf_conf_upd_ind_reg_b1);
    d.add_item(&hf_conf_upd_ind_ack_b0);

    return 1;
}
extern const element_meta mm::configure_update_indication = {
    0xD0,
    "Configuration update indication",
    dissect_configuration_update_indication,
};

