#include "../dissect_sm_msg.hh"


const field_meta hf_gsma_sm_ext = {
    "Extension",
    "nas_5gs.gsm.sm.ext",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x80,
};
const field_meta hf_gsma_conf_prot = {
    "Configuration Protocol",
    "nas_5gs.gsm.sm.configuration_protocol",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x7,
};

// Extended protocol configuration options  9.11.4.6
int sm::dissect_ext_pco(dissector d, context* ctx) {
    const use_context uc(ctx, "extended-protocol-conf-options", d, -1);

    // See subclause 10.5.6.3A in 3GPP TS 24.008    
    auto oct = d.uint8();

    /* 1 ext 0 0 0 0 Spare  Configuration protocol */
    d.add_item(1, &hf_gsma_sm_ext, enc::be);
    d.add_item(1, &hf_gsma_conf_prot, enc::be);
    d.step(1);

    // TODO: dissect body

    return uc.length;
}

// Extended protocol configuration options  9.11.4.6
const element_meta sm::ext_pco = {
    0x7B,
    "Extended protocol configuration options",
    dissect_ext_pco,
    nullptr,
};
