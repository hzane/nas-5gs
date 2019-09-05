#include "../dissect_mm_msg.hh"

namespace{
const true_false_string tfs_sgc_7 = {
    "service gap control supported",
    "service gap control not supported",
};

const field_meta hf_sgc_7 = {
    "Service gap control SGC",
    "nas_5gs.mm.sgc",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_sgc_7),
    nullptr,
    0x80,
};
const true_false_string tfs_hccp_ciot_6 = {
    "Header compression for control plane CIoT 5GS optimization supported",
    "Header compression for control plane CIoT 5GS optimization not supported",
};
const field_meta hf_hccp_ciot_6 = {
    "Header compression for control plane CIoT 5GS optimization (5G-HC-CP-CIoT)",
    "nas_5gs.mm.5g_hc_cp_ciot",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_hccp_ciot_6),
    nullptr,
    0x40,
};

const true_false_string tfs_n3data_5 = {
    "N3 data transfer not supported",
    "N3 data transfer supported",
};

const field_meta hf_n3data_5 = {
    "N3 data transfer",
    "nas_5gs.mm.n3data",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_n3data_5),
    nullptr,
    0x20,
};

const true_false_string tfs_5gcp_ciot_4 = {
    "Header compression for control plane CIoT 5GS optimization supported",
    "Header compression for control plane CIoT 5GS optimization not supported",
};

const field_meta hf_5gcp_ciot_4 = {
    "Control plane CIoT 5GS optimization (5G-CP CIoT)",
    "nas_5gs.mm.5g_cp_ciot",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_5gcp_ciot_4),
    nullptr,
    0x10,
};

const true_false_string tfs_restrict_ec_3 = {
    "Restriction on use of enhanced coverage supported",
    "Restriction on use of enhanced coverage not supported",
};

const field_meta hf_restrict_ec_3 = {
    "Restriction on use of enhanced coverage support (RestrictEC)",
    "nas_5gs.mm.restrict_ec",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_restrict_ec_3),
    nullptr,
    0x08,
};

const true_false_string tfs_lpp_2 = {
    "LPP in N1 mode supported",
    "LPP in N1 mode not supported",
};

const field_meta hf_lpp_b2 = {
    "LTE Positioning Protocol (LPP) capability",
    "nas_5gs.mm.lpp_cap_b2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_lpp_2),
    nullptr,
    0x04,
};

const true_false_string tfs_ho_attach_1 = {
    "ATTACH REQUEST message containing PDN CONNECTIVITY REQUEST message with request "
    "type set to \"handover\" or \"handover of emergency bearer services\" to "
    "transfer PDU session from N1 mode to S1 mode supported",
    "ATTACH REQUEST message containing PDN CONNECTIVITY REQUEST message with request "
    "type set to \"handover\" or \"handover of emergency bearer services\" to transfer "
    "PDU session from N1 mode to S1 mode not supported",
};

const field_meta hf_ho_attach_b1 = {
    "HO attach",
    "nas_5gs.mm.ho_attach_b1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_ho_attach_1),
    nullptr,
    0x02,
};

const true_false_string tfs_s1_mode_0 = {
    "S1 mode supported",
    "S1 mode not supported",
};

const field_meta hf_s1_mode_b0 = {
    "S1 mode",
    "nas_5gs.mm.s1_mode_b0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_s1_mode_0),
    nullptr,
    0x01,
};
}

/*10    5GMM capability  9.11.3.1    O    TLV    3-15*/
const element_meta mm::mm_cap = {
    0x10,
    "5GMM capability",
    dissect_mm_cap,
    nullptr,
};

/* 9.11.3.1     5GMM capability*/
int mm::dissect_mm_cap(dissector d, context* ctx) {
    use_context uc(ctx, "5gmm-capability", d, 0);

    static const field_meta* flags[] = {
        &hf_sgc_7,
        &hf_hccp_ciot_6,
        &hf_n3data_5,
        &hf_5gcp_ciot_4,
        &hf_restrict_ec_3,
        &hf_lpp_b2,
        &hf_ho_attach_b1,
        &hf_s1_mode_b0,
        nullptr,
    };
    d.add_bits(flags);
    d.step(1);

    return 1;
}


