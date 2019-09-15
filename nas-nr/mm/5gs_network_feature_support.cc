#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace mm;

/* 9.11.3.5     5GS network feature support*/
int mm::dissect_nw_feature_support(dissector d, context* ctx) {
    const use_context uc(ctx, "5gs-network-feature-support", d, 1);

    static const field_meta* flags[] = {
        &hf_nw_feat_sup_mpsi_b7,
        &hf_nw_feat_sup_ims_iwk_n26_b6,
        &hf_nw_feat_sup_ims_emf_b5b4,
        &hf_nw_feat_sup_ims_emc_b3b2,
        &hf_nw_feat_sup_ims_vops_b1b0,
        nullptr,
    };
    /* MPSI    IWK N26    EMF    EMC    IMS VoPS    octet 3*/
    d.add_bits(flags);
    d.step(1);

    static const field_meta* oct4[] = {
        &hf_nwfs_emcn3_b0,
        &hf_nwfs_mcsi_b1,
        &hf_nwfs_restrict_ec_b2,
        &hf_nwfs_5gcp_ciot_b3,
        &hf_nwfs_n3data_b4,
        &hf_nwfs_5ghc_cp_ciot_b5,
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
const value_string nas_5gs_nw_feat_sup_emf_values[] = {
    {0x0, "Emergency services fallback not supported"},
    {0x1, "Emergency services fallback supported in NR connected to 5GCN only"},
    {
        0x2,
        "Emergency services fallback supported in E-UTRA connected to 5GCN only",
    },
    {
        0x3,
        "mergency services fallback supported in NR "
        "connected to 5GCN and E-UTRA connected  to 5GCN",
    },
    {0, nullptr},
};

const true_false_string tfs_nas_5gs_nw_feat_sup_mpsi = {
    "Access identity 1 valid in RPLMN or equivalent PLMN",
    "Access identity 1 not valid in RPLMN or equivalent PLMN",
};
const field_meta hf_nw_feat_sup_mpsi_b7 = {
    "MPS indicator (MPSI)",
    "nas.nr.nw_feat_sup.mpsi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_nw_feat_sup_mpsi,
    nullptr,
    0x80,
};

static const tf_string tfs_iwi = {
    "Interworking without N26 interface supported",
    "Interworking without N26 interface not supported",
};

/* 9.11.3.5    5GS network feature support */
const field_meta hf_nw_feat_sup_ims_iwk_n26_b6 = {
    "Interworking without N26",
    "nas.nr.nw.feature.support.n26",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_iwi,
    nullptr,
    0x40,
};
const field_meta hf_nw_feat_sup_ims_emf_b5b4 = {
    "Emergency service fallback indicator (EMF)",
    "nas.nr.nw.feature.ims.emf",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_nw_feat_sup_emf_values,
    nullptr,
    nullptr,
    0x30,
};

const value_string nas_5gs_nw_feat_sup_emc_values[] = {
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
const field_meta hf_nw_feat_sup_ims_emc_b3b2 = {
    "Emergency service support indicator (EMC)",
    "nas.nr.nf.feature.ims.emc",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_nw_feat_sup_emc_values,
    nullptr,
    nullptr,
    0x0c,
};

const value_string nas_5gs_nw_feat_sup_ims_vops_values[] = {
    {0x0, "IMS voice over PS session not supported"},
    {0x1, "IMS voice over PS session supported over 3GPP access"},
    {0x2, "IMS voice over PS session supported over non - 3GPP access"},
    {0x3, "Reserved"},
    {0, nullptr},
};

const field_meta hf_nw_feat_sup_ims_vops_b1b0 = {
    "IMS voice over PS session indicator (IMS VoPS)",
    "nas.nr.mm.nw.feature.ims.vops",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_nw_feat_sup_ims_vops_values,
    nullptr,
    nullptr,
    0x03,
};

const true_false_string tfs_nwfs_b0 = {
    "Emergency services supported over non-3GPP access",
    "Emergency services not supported over non-3GPP access",
};

const true_false_string tfs_nwfs_b1 = {
    "Access identity 2 valid",
    "Access identity 2 not valid",
};

const true_false_string tfs_nwfs_b2 = {
    "Use of enhanced coverage is restricted",
    "Use of enhanced coverage is not restricted",
};

const true_false_string tfs_nwfs_b3 = {
    "Control plane CIoT 5GS optimization supported",
    "Control plane CIoT 5GS optimization not supported",
};

const true_false_string tfs_nwfs_b4 = {
    "N3 data transfer not supported",
    "N3 data transfer supported",
};

const true_false_string tfs_nwfs_b5 = {
    "Header compression for control plane CIoT 5GS optimization supported",
    "Header compression for control plane CIoT 5GS optimization not supported",
};

const true_false_string tfs_nwfs_b6 = {
    "User plane CIoT 5GS optimization supported",
    "User plane CIoT 5GS optimization not supported",
};

const field_meta hf_nwfs_emcn3_b0 = {
    "Emergency service support for non-3GPP access indicator (EMCN3)",
    "nas.nr.network.feature.support.emcn3",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_nwfs_b0,
    nullptr,
    0x01,
};

const field_meta hf_nwfs_mcsi_b1 = {
    "MCS indicator (MCSI)",
    "nas.nr.mm.nw.feature.mcs",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_nwfs_b1,
    nullptr,
    0x02,
};

const field_meta hf_nwfs_restrict_ec_b2 = {
    "Restriction on enhanced coverage (RestrictEC)",
    "nas.nr.nw.feature.restrict.ec",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_nwfs_b2,
    nullptr,
    0x04,
};
const field_meta hf_nwfs_5gcp_ciot_b3 = {
    "Control plane CIoT 5GS optimization (5G-CP CIoT)",
    "nas.nr.mm.nw.feature.ciot.cp",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_nwfs_b3,
    nullptr,
    0x08,
};
const field_meta hf_nwfs_n3data_b4 = {
    "N3 data transfer (N3 data)",
    "nas.nr.mm.nw.feature.n3",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_nwfs_b4,
    nullptr,
    0x10,
};
const field_meta hf_nwfs_5ghc_cp_ciot_b5 = {
    "Header compression for control plane CIoT 5GS optimization (5G-HC-CP CIoT)",
    "nas.nr.mm.nw.feature.hc.cp.ciot",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_nwfs_b5,
    nullptr,
    0x20,
};
const field_meta hf_nwfs_5gup_ciot_b6 = {
    "User plane CIoT 5GS optimization (5G-UP CIoT)",
    "nas.nr.mm.nw.feature.up.ciot",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_nwfs_b6,
    nullptr,
    0x40,
};
}

// 5GS network feature support   9.11.3.5
const element_meta mm::nw_feature_support = {
    0x21,
    "5GS network feature support",
    dissect_nw_feature_support,
    nullptr,
};
