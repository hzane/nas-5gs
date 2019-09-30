#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace mm;


const bool_field hf_mps_indicator = {
    "MPS indicator (MPSI)",
    0x80,
    "Access identity 1 not valid in RPLMN or equivalent PLMN",
    "Access identity 1 valid in RPLMN or equivalent PLMN",
};

/* 9.11.3.5    5GS network feature support */
const bool_field hf_interworking_without_n26 = {
    "Interworking without N26",
    0x40,
    "Interworking without N26 interface not supported",
    "Interworking without N26 interface supported",
};
const tag_field hf_emergency_service_fallback_indicator = {
    "Emergency service fallback indicator (EMF)",
    0x30,
    (const v_string[]){
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
    }
};

const tag_field hf_emergency_service_support_indicator = {
    "Emergency service support indicator (EMC)",
    0x0c,
    (const v_string[]){
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
    }
};


const tag_field hf_ims_voice_over_ps_session_indicator = {
    "IMS voice over PS session indicator (IMS VoPS)",
    0x03,
    (const v_string[]){
        {0x0, "IMS voice over PS session not supported"},
        {0x1, "IMS voice over PS session supported over 3GPP access"},
        {0x2, "IMS voice over PS session supported over non - 3GPP access"},
        {0x3, "Reserved"},
        {0, nullptr},
    }
};

const tf_string tfs_emergency_services_over_n3gpp = {
    "Emergency services supported over non-3GPP access",
    "Emergency services not supported over non-3GPP access",
};

const tf_string tfs_access_identity2_valid = {
    "Access identity 2 valid",
    "Access identity 2 not valid",
};

const tf_string tfs_use_of_enhanced_coverage_restricted = {
    "Use of enhanced coverage is restricted",
    "Use of enhanced coverage is not restricted",
};

const tf_string tfs_control_plane_nr_optimization = {
    "Control plane CIoT 5GS optimization supported",
    "Control plane CIoT 5GS optimization not supported",
};

const tf_string tfs_n3_data_transfer = {
    "N3 data transfer not supported",
    "N3 data transfer supported",
};

const tf_string tfs_header_compression = {
    "Header compression for control plane CIoT 5GS optimization supported",
    "Header compression for control plane CIoT 5GS optimization not supported",
};


const bool_field hf_emergency_service_support_n3gpp = {
    "Emergency service support for non-3GPP access indicator (EMCN3)",
    0x01,
    {
        "Emergency services not supported over non-3GPP access",
        "Emergency services supported over non-3GPP access",
    },
};

const bool_field hf_mcs_indicator = {
    "MCS indicator (MCSI)",
    0x02,
    {
        "Access identity 2 not valid",
        "Access identity 2 valid",
    },
};

const bool_field hf_restrict_ec = {
    "Restriction on enhanced coverage (RestrictEC)",
    0x04,
    {
        "Use of enhanced coverage is not restricted",
        "Use of enhanced coverage is restricted",
    },
};
const bool_field hf_nr_control_plane_ciot = {
    "Control plane CIoT 5GS optimization (5G-CP CIoT)",
    0x08,
    {
        "Control plane CIoT 5GS optimization not supported",
        "Control plane CIoT 5GS optimization supported",
    },
};
const bool_field hf_nwfs_n3data_b4 = {
    "N3 data transfer (N3 data)",
    0x10,
    {
        "N3 data transfer supported",
        "N3 data transfer not supported",
    },
};
const bool_field hf_header_compression_control_plane = {
    "Header compression for control plane CIoT 5GS optimization (5G-HC-CP CIoT)",
    0x20,
    {
        "Header compression for control plane CIoT 5GS optimization not supported",
        "Header compression for control plane CIoT 5GS optimization supported",
    },
};
const bool_field hf_nwfs_5gup_ciot_b6 = {
    "User plane CIoT 5GS optimization (5G-UP CIoT)",
    0x40,
    {
        "User plane CIoT 5GS optimization not supported",
        "User plane CIoT 5GS optimization supported",
    },
};


/* 9.11.3.5     5GS network feature support*/
int mm::dissect_network_feature_support(dissector d, context* ctx) {
    const use_context uc(ctx, "5gs-network-feature-support", d, 1);

    /* MPSI    IWK N26    EMF    EMC    IMS VoPS    octet 3*/
    d.add_item(&hf_mps_indicator);
    d.add_item(&hf_interworking_without_n26);
    d.add_item(&hf_emergency_service_fallback_indicator);
    d.add_item(&hf_emergency_service_support_indicator);
    d.add_item(&hf_ims_voice_over_ps_session_indicator);
    d.step(1);

    static const bool_field* oct4[] = {
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


const v_string emergency_services_fallback_values[] = {
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
