#include "common.hh"
#include "format.hh"
#include "use_context.hh"

// NAS security algorithms information element (see subclause 9.11.3.34
const uint8_field hf_integrity_algo_type = {
    "Type of integrity protection algorithm",
    0x0fu,
};

const tag_field hf_ciphering_algo_type = {
    "Type of ciphering algorithm",
    0xf0u,
    (const v_string[]){
        {0x0, "5G-EA0 (null ciphering algorithm)"},
        {0x1, "128-5G-EA1"},
        {0x2, "128-5G-EA2"},
        {0x3, "128-5G-EA3"},
        {0x4, "5G-EA4"},
        {0x5, "5G-EA5"},
        {0x6, "5G-EA6"},
        {0x7, "5G-EA7"},
        {0, nullptr},
    },
};
// 9.11.2.6 Intra N1 mode NAS transparent container page.349
int cmn::dissect_intra_n1_mode_container(dissector d, context* ctx) {
    use_context uc(ctx, "intra-n1-mode-nas-transparent-container", d, 0);

    /*The value part of the Intra N1 mode NAS transparent container information element is
included in specific information elements within some RRC messages sent to the UE.*/
    d.add_item(4, hstring(d.ptr(), 4));
    d.step(4);

    hf_integrity_algo_type.add(d, ctx);
    hf_ciphering_algo_type.add(d, ctx);
    d.step(1);

    (void) d.add_item(1, &hf_ksi_5g);
    (void) d.add_item(1, &hf_security_context_type);
    (void) d.add_item(1, &hf_kacf);
    d.step(1);

    d.add_item(1, "Sequence number", istring(d.uint8()));
    return uc.length;
}


namespace cmn {


// Type of security context flag (TSC)
const field_meta hf_security_context_type = {
    "Type of security context flag (TSC)",
    "nas.nr.cmn.tsc",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x04u,
};
const true_false_string tfs_kacf = {
    "a new KAMF has been calculated by the network",
    "a new KAMF has not been calculated by the network",
};

// K_AMF_change_flag
const field_meta hf_kacf = {
    "K-AMF change flag (KACF)",
    "nas.nr.cmn.kacf",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_kacf,
    nullptr,
    0x10u,
};

const field_meta hf_ksi_5g             = {
    "Key set identifier in 5G",
    "nas.nr.cmn.ksi",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x07u,
};


}
