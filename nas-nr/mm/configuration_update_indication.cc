#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"


using namespace mm;
using namespace nas;

static const char* req = "Requested";
static const char* nreq= "Not requested";

const bool_field hf_conf_upd_ind_reg_b1 = {
    "Registration",
    0x02,
    req,
    nreq,
};

const bool_field hf_conf_upd_ind_ack_b0 = {
    "Acknowledgement",
    0x01,
    req,
    nreq,
};

/* 9.11.3.18    Configuration update indication */
int mm::dissect_configuration_update_indication(dissector d, context* ctx) {
    const use_context        uc(ctx, "configuration-update-indication", d, -1);

    d.add_item(&hf_conf_upd_ind_reg_b1);
    d.add_item(&hf_conf_upd_ind_ack_b0);

    return 1;
}
