#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;

namespace mm {
extern const field_meta hf_5gsrvcc_capability;
extern const field_meta hf_user_plane_5gs_optimization;
} // namespace mm

/* 9.11.3.1     5GMM capability*/
int mm::dissect_mm_capability(dissector d, context* ctx) {
    const use_context uc(ctx, "5gmm-capability", d, 12);

    static const field_meta* flags[] = {
        &hf_service_gap_control,
        &hf_header_compression_for_ctrl_plane,
        &hf_n3data_5,
        &hf_control_plane,
        &hf_restrict_ec_support,
        &hf_lpp_capability,
        &hf_handover_attach,
        &hf_s1_mode_b0,
        nullptr,
    };
    d.add_bits(flags);
    d.step(1);

    if (d.length>0) {
        static const field_meta* o4flags[] = {
            &hf_5gsrvcc_capability,
            &hf_user_plane_5gs_optimization,
            nullptr,
        };
        d.add_bits(o4flags);
        d.step(1);
    }
    // 5-15 octets is spare
    return uc.length;
}

struct mm_capability_t {
    uint8_t service_gap_control;
    uint8_t header_compression_for_control_plane;
    uint8_t n3_data;
    uint8_t control_plane;
    uint8_t restrict_ec_support;
    uint8_t lpp_capability;
    uint8_t handover_attach;
    uint8_t s1_mode;
    std::optional<uint8_t> nrsr_vcc;
    std::optional<uint8_t> user_plane_nr_optimization;
};

namespace mm {
const field_meta        hf_5gsrvcc_capability = {
    "5G-SRVCC from NG-RAN to UTRAN (5GSRVCC) capability",
    "nas.nr.mm.cap.5gsrvcc",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0,
};

const field_meta        hf_user_plane_5gs_optimization = {
    "User plane CIoT 5GS optimization (5G-UP CIoT) ",
    "nas.nr.mm.cap.5gup.ciot",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0,
};

const true_false_string tfs_service_gap_control = {
    "service gap control supported",
    "service gap control not supported",
};

const field_meta hf_service_gap_control = {
    "Service gap control (SGC)",
    "nas.nr.mm.sgc",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_service_gap_control,
    nullptr,
    0x80,
};

const true_false_string tfs_header_compression_for_control = {
    "Header compression for control plane CIoT 5GS optimization supported",
    "Header compression for control plane CIoT 5GS optimization not supported",
};

const field_meta hf_header_compression_for_ctrl_plane = {
    "Header compression for control plane CIoT 5GS optimization (5G-HC-CP-CIoT)",
    "nas.nr.mm.5g_hc_cp_ciot",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_header_compression_for_control,
    nullptr,
    0x40,
};

const true_false_string tfs_n3data_5 = {
    "N3 data transfer not supported",
    "N3 data transfer supported",
};

const field_meta hf_n3data_5 = {
    "N3 data transfer",
    "nas.nr.mm.n3data",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_n3data_5,
    nullptr,
    0x20,
};

const field_meta hf_control_plane = {
    "Control plane CIoT 5GS optimization (5G-CP CIoT)",
    "nas.nr.mm.cp.ciot",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_header_compression_for_control,
    nullptr,
    0x10,
};

const true_false_string tfs_restrict_ec = {
    "Restriction on use of enhanced coverage supported",
    "Restriction on use of enhanced coverage not supported",
};

const field_meta hf_restrict_ec_support = {
    "Restriction on use of enhanced coverage support (RestrictEC)",
    "nas.nr.mm.restrict_ec",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_restrict_ec,
    nullptr,
    0x08,
};

const true_false_string tfs_lte_positioning_protocol = {
    "LPP in N1 mode supported",
    "LPP in N1 mode not supported",
};

const field_meta hf_lpp_capability = {
    "LTE Positioning Protocol (LPP) capability",
    "nas.nr.mm.lpp_cap_b2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_lte_positioning_protocol,
    nullptr,
    0x04,
};

const true_false_string tfs_ho_attach_1 = {
    R"(ATTACH REQUEST message containing PDN CONNECTIVITY REQUEST message with request )"
    R"(type set to "handover" or "handover of emergency bearer services" to )"
    R"(transfer PDU session from N1 mode to S1 mode supported)",
    R"(ATTACH REQUEST message containing PDN CONNECTIVITY REQUEST message with request )"
    R"(type set to "handover" or "handover of emergency bearer services" to transfer )"
    R"(PDU session from N1 mode to S1 mode not supported)",
};

const field_meta hf_handover_attach = {
    "HO attach",
    "nas.nr.mm.ho.attach.b1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ho_attach_1,
    nullptr,
    0x02,
};

const true_false_string tfs_s1_mode_0 = {
    "S1 mode supported",
    "S1 mode not supported",
};

const field_meta hf_s1_mode_b0 = {
    "S1 mode",
    "nas.nr.mm.s1.mode.b0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_s1_mode_0,
    nullptr,
    0x01,
};
}

/*10    5GMM capability  9.11.3.1    O    TLV    3-15*/
const element_meta mm::nrmm_capability = {
    0x10,
    "5GMM capability",
    mm::dissect_mm_capability,
    nullptr,
};
