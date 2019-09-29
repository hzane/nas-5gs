#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

/* 9.11.3.53A   UE parameters update transparent container */
int mm::dissect_ue_parameters_update_transparent_container(dissector d, context*ctx) {
    const use_context uc(ctx, "ue-parameters-update-transprent-container", d, -1);
    diag("no dissect yet\n");

    (void) d.add_item(1, &hf_upu_data_type);
    const auto uput = d.uint8() & 0x01u;
    if (uput) {
        (void) d.add_item(1, &hf_ue_parameters_update_ack);
        (void) d.add_item(1, &hf_reregistration);
    }
    d.step(1);

    // (void) d.add_item(16, &hf_upu_mac_i);
    if (uput) {
    }

    return d.length;
}

const bool_field mm::hf_upu_data_type = {
    "UPU data type",
    0x01,
    "The UE parameters update transparent container carries a UE parameters update list",
    "The UE parameters update transparent container carries an acknowledgement of successful reception of a UE parameters update list",
};


const bool_field mm::hf_ue_parameters_update_ack = {
    "ACK",
    0,
    "acknowledgement not requested",
    "acknowledgement requested",
};

static const tf_string  reg_req_or_not               = {
    "re-registration requested",
    "re-registration not requested"
};
const bool_field mm::hf_reregistration                = {
    "Re-registration (REG)",
    0,
    reg_req_or_not.false_string,
    reg_req_or_not.true_string,
};

// UPU-MAC-IAUSF, UPU-MAC-IUE and CounterUPU are coded as specified in 3GPP TS 33.501 [24]
const bool_field mm::hf_upu_mac_i = {
    "UPU-MAC-I",
    0,
    reg_req_or_not.false_string,
    reg_req_or_not.true_string,
};

const tag_field hf_ue_param_update_data_set_type = {
    "UE parameters update data set type",
    0,
    (const v_string[]){
        {1, "Routing indicator update data"},
        {2, "Default configured NSSAI update data"},
        {0, nullptr},
    },
};
