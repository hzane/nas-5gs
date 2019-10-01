#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;

const bool_field hf_5gsrvcc_capability = {
    "5G-SRVCC from NG-RAN to UTRAN (5GSRVCC) capability",
    0,
    tf_supported_or_not,
};

const bool_field hf_user_plane_5gs_optimization = {
    "User plane CIoT 5GS optimization (5G-UP CIoT) ",
    0,
    tf_supported_or_not,
};

const bool_field hf_service_gap_control = {
    "Service gap control (SGC)",
    0x80,
    "service gap control not supported",
    "service gap control supported",
};

const bool_field hf_header_compression_for_ctrl_plane = {
    "Header compression for control plane CIoT 5GS optimization (5G-HC-CP-CIoT)",
    0x40,
    "Header compression for control plane CIoT 5GS optimization not supported",
    "Header compression for control plane CIoT 5GS optimization supported",
};

const bool_field hf_n3data_5 = {
    "N3 data transfer",
    0x20,
    {
        "N3 data transfer supported",
        "N3 data transfer not supported",
    },
};

const bool_field hf_control_plane = {
    "Control plane CIoT 5GS optimization (5G-CP CIoT)",
    0x10,
    hf_header_compression_for_ctrl_plane.values,
};

const bool_field hf_restrict_ec_support = {
    "Restriction on use of enhanced coverage support (RestrictEC)",
    0x08,
    "Restriction on use of enhanced coverage not supported",
    "Restriction on use of enhanced coverage supported",
};

const bool_field hf_lpp_capability = {
    "LTE Positioning Protocol (LPP) capability",
    0x04,
    "LPP in N1 mode not supported",
    "LPP in N1 mode supported",
};

const bool_field hf_handover_attach = {
    "HO attach",
    0x02,
    {
        R"(handover attach not supported)",
        R"(handover attach supported)",
    },
};

const bool_field hf_s1_mode_b0 = {
    "S1 mode",
    0x01,
    "S1 mode not supported",
    "S1 mode supported",
};

/* 9.11.3.1     5GMM capability*/
int mm::dissect_mm_capability(dissector d, context* ctx) {
    const use_context uc(ctx, "5gmm-capability", d, 12);

    static const bool_field* flags[] = {
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

    if (d.length > 0) {
        static const bool_field* o4flags[] = {
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
