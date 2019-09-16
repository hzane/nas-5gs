#include "../dissect_mm_msg.hh"

/* 9.11.3.53A   UE parameters update transparent container */
int mm::dissect_ue_parameters_update_transparent_container(dissector d, context*ctx) {
    const use_context uc(ctx, "ue-parameters-update-transprent-container", d, -1);
    diag("no dissect yet\n");

    (void) d.add_item(1, &hf_upu_data_type, enc::be);
    const NASNR_AUTO(uint8_t) uput = d.uint8() & 0x01u;
    if (uput) {
        (void) d.add_item(1, &hf_ack, enc::be);
        (void) d.add_item(1, &hf_reregistration, enc::be);
    }
    d.step(1);

    // (void) d.add_item(16, &hf_upu_mac_i, enc::na);
    if (uput) {
    }

    return d.length;
}

const tf_string  tfs_upu_data_type = {
    "The UE parameters update transparent container carries an acknowledgement of successful reception of a UE parameters update list",
    "The UE parameters update transparent container carries a UE parameters update list",
};
const field_meta mm::hf_upu_data_type = {
    "UPU data type",
    "nas.nr.mm.ue.parameters.update.data.type",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_upu_data_type,
    nullptr,
    0x01,
};

const tf_string tfs_ack = {
    "acknowledgement not requested",
    "acknowledgement requested",
};

const field_meta mm::hf_ack = {
    "ACK",
    "nas.nr.mm.ue.parameters.update.ack",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ack,
    nullptr,
    0,
};
const tf_string  tfs_reregistration               = {
    "re-registration requested","re-registration not requested"
};
const field_meta mm::hf_reregistration                = {
    "Re-registration (REG)",
    "nas.nr.mm.ue.parameters.rereg",
    ft::ft_boolean, fd::base_dec,
    nullptr,
    &tfs_reregistration,
    nullptr,
    0,
};
// UPU-MAC-IAUSF, UPU-MAC-IUE and CounterUPU are coded as specified in 3GPP TS 33.501 [24]
const field_meta mm::hf_upu_mac_i = {
    "UPU-MAC-I",
    "nas.nr.upu",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_reregistration,
    nullptr,
    0,
};
extern const val_string ue_param_update_data_set_type_values[] = {
    {1, "Routing indicator update data"},
    {2, "Default configured NSSAI update data"},
    {0, nullptr},
};

const field_meta hf_ue_param_update_data_set_type = {
    "UE parameters update data set type",
    "nas.nr.mm.ue.parameters.update.data.set.type",
    ft::ft_uint8,
    fd::base_dec,
    ue_param_update_data_set_type_values,
    nullptr,
    nullptr,
    0,
};
