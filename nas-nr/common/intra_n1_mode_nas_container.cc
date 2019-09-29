#include "common.hh"
#include "formats.hh"
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
// Type of security context flag (TSC)
const bool_field n1_tsc_flag = {
    "Type of security context flag (TSC)",
    0x04u,
};
// 9.11.2.6 Intra N1 mode NAS transparent container page.349
int cmn::dissect_intra_n1_mode_container(dissector d, context* ctx) {
    use_context uc(ctx, "intra-n1-mode-nas-transparent-container", d, 0);

    /*The value part of the Intra N1 mode NAS transparent container information element is
included in specific information elements within some RRC messages sent to the UE.*/
    d.add_item(4, hstring(d.ptr(), 4));
    d.step(4);

    d.add_item(&hf_integrity_algo_type, false);
    d.add_item(&hf_ciphering_algo_type, false);
    d.step(1);

    (void) d.add_item(&hf_ksi_5g);
    (void) d.add_item(&n1_tsc_flag);
    (void) d.add_item(&hf_kacf);
    d.step(1);

    d.add_item(&hf_sequence_no);
    d.step(1);

    return uc.length;
}
// K_AMF_change_flag
const bool_field hf_kacf = {
    "K-AMF change flag (KACF)",
    0x10u,

    "a new KAMF has not been calculated by the network",
    "a new KAMF has been calculated by the network",
};

namespace cmn {


const tf_string tfs_kacf = {
    "a new KAMF has been calculated by the network",
    "a new KAMF has not been calculated by the network",
};



} // namespace cmn
const uint8_field hf_ksi_5g = {
    "Key set identifier in 5G",
    0x07u,
};