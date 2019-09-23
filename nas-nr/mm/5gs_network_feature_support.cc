#include "../common/dissect_mm_msg.hh"

using namespace cmn;
using namespace mm;

/* 9.11.3.5     5GS network feature support*/
int mm::dissect_network_feature_support(dissector d, context* ctx) {
    const use_context uc(ctx, "5gs-network-feature-support", d, 1);

    static const field_meta* flags[] = {
        &hf_mps_indicator,
        &hf_interworking_without_n26,
        &hf_emergency_service_fallback_indicator,
        &hf_emergency_service_support_indicator,
        &hf_ims_voice_over_ps_session_indicator,
        nullptr,
    };
    /* MPSI    IWK N26    EMF    EMC    IMS VoPS    octet 3*/
    d.add_bits(flags);
    d.step(1);

    static const field_meta* oct4[] = {
        &hf_emergency_service_support_n3gpp,
        &hf_mcs_indicator,
        &hf_restrict_ec,
        &hf_nr_control_plane_ciot,
        &hf_nwfs_n3data_b4,
        &hf_header_compression_control_plane,
        &hf_nwfs_5gup_ciot_b6,
        nullptr,
    };
    // octet 4 may be non-exist
    if (d.length > 0) {
        d.add_bits(oct4);
        d.step(1);
    }

    // oct 5 is optional
    return uc.length; // 1-3
}

namespace mm {
const value_string emergency_services_fallback_values[] = {
    {0x0, "Emergency services fallback not supported"},
    {0x1, "Emergency services fallback supported in NR connected to 5GCN only"},
    {
        0x2,
        "Emergency services fallback supported in E-UTRA connected to 5GCN only",
    },
    {
        0x3,
        "emergency services fallback supported in NR "
        "connected to 5GCN and E-UTRA connected  to 5GCN",
    },
    {0, nullptr},
};

const true_false_string tfs_access_identity_1_valid_or_not = {
    "Access identity 1 valid in RPLMN or equivalent PLMN",
    "Access identity 1 not valid in RPLMN or equivalent PLMN",
};
const field_meta hf_mps_indicator = {
    "MPS indicator (MPSI)",
    "nas.nr.nw.feature.support.mpsi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_access_identity_1_valid_or_not,
    nullptr,
    0x80,
};

static const tf_string tfs_iwi = {
    "Interworking without N26 interface supported",
    "Interworking without N26 interface not supported",
};

/* 9.11.3.5    5GS network feature support */
const field_meta hf_interworking_without_n26 = {
    "Interworking without N26",
    "nas.nr.nw.feature.support.n26",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_iwi,
    nullptr,
    0x40,
};
const field_meta hf_emergency_service_fallback_indicator = {
    "Emergency service fallback indicator (EMF)",
    "nas.nr.nw.feature.ims.emf",
    ft::ft_uint8,
    fd::base_dec,
    emergency_services_fallback_values,
    nullptr,
    nullptr,
    0x30,
};

const value_string emergency_services_values[] = {
    {0x0, "Emergency services not supported"},
    {0x1, "Emergency services supported in NR connected to 5GCN only"},
    {
        0x2,
        "Emergency services supported in E-UTRA connected to 5GCN only",
    },
    {0x3,
        "Emergency services supported in NR connected "
        "to 5GCN and E-UTRA connected to 5GCN",
    },
    {0, nullptr},
};
const field_meta hf_emergency_service_support_indicator = {
    "Emergency service support indicator (EMC)",
    "nas.nr.nf.feature.ims.emc",
    ft::ft_uint8,
    fd::base_dec,
    emergency_services_values,
    nullptr,
    nullptr,
    0x0c,
};

const value_string ims_voice_over_ps_session_values[] = {
    {0x0, "IMS voice over PS session not supported"},
    {0x1, "IMS voice over PS session supported over 3GPP access"},
    {0x2, "IMS voice over PS session supported over non - 3GPP access"},
    {0x3, "Reserved"},
    {0, nullptr},
};

const field_meta hf_ims_voice_over_ps_session_indicator = {
    "IMS voice over PS session indicator (IMS VoPS)",
    "nas.nr.mm.nw.feature.ims.vops",
    ft::ft_uint8,
    fd::base_dec,
    ims_voice_over_ps_session_values,
    nullptr,
    nullptr,
    0x03,
};

const true_false_string tfs_emergency_services_over_n3gpp = {
    "Emergency services supported over non-3GPP access",
    "Emergency services not supported over non-3GPP access",
};

const true_false_string tfs_access_identity2_valid = {
    "Access identity 2 valid",
    "Access identity 2 not valid",
};

const true_false_string tfs_use_of_enhanced_coverage_restricted = {
    "Use of enhanced coverage is restricted",
    "Use of enhanced coverage is not restricted",
};

const true_false_string tfs_control_plane_nr_optimization = {
    "Control plane CIoT 5GS optimization supported",
    "Control plane CIoT 5GS optimization not supported",
};

const true_false_string tfs_n3_data_transfer = {
    "N3 data transfer not supported",
    "N3 data transfer supported",
};

const true_false_string tfs_header_compression = {
    "Header compression for control plane CIoT 5GS optimization supported",
    "Header compression for control plane CIoT 5GS optimization not supported",
};

const true_false_string tfs_user_plane_ciot_nr_optimization = {
    "User plane CIoT 5GS optimization supported",
    "User plane CIoT 5GS optimization not supported",
};

const field_meta hf_emergency_service_support_n3gpp = {
    "Emergency service support for non-3GPP access indicator (EMCN3)",
    "nas.nr.network.feature.support.emcn3",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_emergency_services_over_n3gpp,
    nullptr,
    0x01,
};

const field_meta hf_mcs_indicator = {
    "MCS indicator (MCSI)",
    "nas.nr.mm.nw.feature.mcs",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_access_identity2_valid,
    nullptr,
    0x02,
};

const field_meta hf_restrict_ec = {
    "Restriction on enhanced coverage (RestrictEC)",
    "nas.nr.nw.feature.restrict.ec",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_use_of_enhanced_coverage_restricted,
    nullptr,
    0x04,
};
const field_meta hf_nr_control_plane_ciot = {
    "Control plane CIoT 5GS optimization (5G-CP CIoT)",
    "nas.nr.mm.nw.feature.ciot.cp",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_control_plane_nr_optimization,
    nullptr,
    0x08,
};
const field_meta hf_nwfs_n3data_b4 = {
    "N3 data transfer (N3 data)",
    "nas.nr.mm.nw.feature.n3",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_n3_data_transfer,
    nullptr,
    0x10,
};
const field_meta hf_header_compression_control_plane = {
    "Header compression for control plane CIoT 5GS optimization (5G-HC-CP CIoT)",
    "nas.nr.mm.nw.feature.hc.cp.ciot",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_header_compression,
    nullptr,
    0x20,
};
const field_meta hf_nwfs_5gup_ciot_b6 = {
    "User plane CIoT 5GS optimization (5G-UP CIoT)",
    "nas.nr.mm.nw.feature.up.ciot",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_user_plane_ciot_nr_optimization,
    nullptr,
    0x40,
};
}

// 5GS network feature support   9.11.3.5
const element_meta mm::network_feature_support = {
    0x21,
    "5GS network feature support",
    dissect_network_feature_support,
    nullptr,
};
