#include "../common/dissect_mm_msg.hh"

/*  9.11.3.50A    SMS indication */
int mm::dissect_sms_indication(dissector d, context* ctx) {
    const use_context uc(ctx, "sms-indication", d, -1);

    (void) d.add_item(1, &hf_sms_over_nas_ind, enc::be);
    d.step(1);

    return 1;
}

static const tf_string tfs_sms_sai = {
    "SMS over NAS available",
    "SMS over NAS not available",
};

const field_meta mm::hf_sms_over_nas_ind = {
    "SMS over NAS",
    "nas.nr.mm.sms.indication.sai",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_sms_sai,
    nullptr,
    0x01,
};
