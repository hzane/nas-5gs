#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

/* Mobile Station Classmark Revision level */
static const value_string revision_values[] = {
    {0, "Reserved for GSM phase 1"},
    {1, "Used by GSM phase 2 mobile stations"},
    {2, "Used by mobile stations supporting R99 or later versions of the protocol"},
    {3, "Reserved for future use"},
    {0, nullptr},
};

const field_meta hf_msc_revision_level = {
    "Revision Level",
    "gsm_a.MSC_rev",
    ft::ft_uint8,
    fd::base_dec,
    revision_values,
    nullptr,
    nullptr,
    0x40,
};

/* ES IND (octet 3, bit 5) "Controlled Early Classmark Sending" option implementation */
static const tf_string tfs_es_indication = {
    "Controlled Early Classmark Sending option is implemented in the MS",
    "Controlled Early Classmark Sending option is not implemented in the MS",
};

const field_meta hf_es_indication = {
    "ES IND",
    "gsm_a.ES_IND",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_es_indication,
    nullptr,
    0x10,
};

/* A5/1 algorithm supported (octet 3, bit 4) */
static const tf_string tfs_a51_algorithm_support_values = {
    "encryption algorithm A5/1 not available",
    "encryption algorithm A5/1 available",
};

/* RF Power Capability (Octet 3) */
static const value_string rf_power_capability_values[] = {
    {0, "class 1"},
    {1, "class 2"},
    {2, "class 3"},
    {3, "class 4"},
    {4, "class 5"},
    {7, "RF Power capability is irrelevant in this information element"},
    {0, nullptr},
};

const field_meta hf_a51_algorithm_support = {
    "A5/1 algorithm supported",
    "gsm_a.A5_1_algorithm_sup",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_a51_algorithm_support_values,
    nullptr,
    0x08,
};
const field_meta hf_rf_power_capability = {
    "RF Power Capability",
    "gsm_a.RF_power_capability",
    ft::ft_uint8,
    fd::base_dec,
    rf_power_capability_values,
    nullptr,
    nullptr,
    0x07,
};

/* PS capability (pseudo-synchronization capability) (octet 4) */
static const tf_string tfs_ps_sup_capability = {
    "PS capability present",
    "PS capability not present",
};

const field_meta hf_ps_support_capability = {
    "PS capability (pseudo-synchronization capability)",
    "gsm_a.ps_sup_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ps_sup_capability,
    nullptr,
    0x40,
};

/* SS Screening Indicator (octet 4)defined in 3GPP TS 24.080 */
static const value_string ss_screening_indicator_values[] = {
    {0, "Default value of phase 1"},
    {1, "Capability of handling of ellipsis notation and phase 2 error handling "},
    {2, "For future use"},
    {3, "For future use"},
    {0, nullptr},
};

const field_meta hf_ss_screening_indicator = {
    "SS Screening Indicator",
    "gsm_a.SS_screening_indicator",
    ft::ft_uint8,
    fd::base_dec,
    ss_screening_indicator_values,
    nullptr,
    nullptr,
    0x30,
};

/* SM capability (MT SMS pt to pt capability) (octet 4)*/
static const tf_string tfs_nrsm_capability = {
    "Mobile station supports mobile terminated point to point SMS",
    "Mobile station does not support mobile terminated point to point SMS",
};

const field_meta hf_nrsm_capability = {
    "SM capability (MT SMS pt to pt capability)",
    "gsm_a.SM_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nrsm_capability,
    nullptr,
    0x08,
};

/* VBS notification reception (octet 4) */
static const tf_string tfs_vbs_notification_reception = {
    "VBS capability and notifications wanted",
    "no VBS capability or no notifications wanted",
};

const field_meta hf_vbs_notification_rec = {
    "VBS notification reception",
    "gsm_a.VBS_notification_rec",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_vbs_notification_reception,
    nullptr,
    0x04,
};

/* VGCS notification reception (octet 4) */
static const tf_string tfs_vgcs_notification_reception = {
    "VGCS capability and notifications wanted",
    "no VGCS capability or no notifications wanted",
};

const field_meta hf_vgcs_notification_reception = {
    "VGCS notification reception",
    "gsm_a.VGCS_notification_rec",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_vgcs_notification_reception,
    nullptr,
    0x02,
};

/* FC Frequency Capability (octet 4 ) */
static const tf_string tfs_fc_frequency_capability = {
    "The MS does support the E-GSM or R-GSM",
    "The MS does not support the E-GSM or R-GSM band"};
const field_meta hf_fc_frequency_capability = {
    "FC Frequency Capability",
    "gsm_a.FC_frequency_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_fc_frequency_capability,
    nullptr,
    0x01,
};

/* CM3 (octet 5, bit 8) */
static const tf_string tfs_cm3 = {
    "The MS supports options that are indicated in classmark 3 IE",
    "The MS does not support any options that are indicated in CM3",
};
const field_meta hf_cm3 = {{
    "CM3",
    "gsm_a.CM3",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_cm3,
    nullptr,
    0x80,
}};

/* LCS VA capability (LCS value added location request notification capability) (octet
 * 5,bit 6) */
static const tf_string tfs_lcs_va_capability = {
    "LCS value added location request notification capability supported",
    "LCS value added location request notification capability not supported",
};

const field_meta hf_lcs_va_capability = {{
    "LCS VA capability (LCS value added location request notification capability)",
    "gsm_a.LCS_VA_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_lcs_va_capability,
    nullptr,
    0x20,
}};

/* UCS2 treatment (octet 5, bit 5) */
static const tf_string tfs_ucs2_treatment = {
    "the ME has no preference between the use of the default alphabet and the use of "
    "UCS2",
    "the ME has a preference for the default alphabet",
};

const field_meta hf_ucs2_treatmeant = {{
    "UCS2 treatment",
    "gsm_a.UCS2_treatment",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ucs2_treatment,
    nullptr,
    0x10,
}};

/* SoLSA (octet 5, bit 4) */
static const tf_string tfs_solsa = {
    "The ME supports SoLSA",
    "The ME does not support SoLSA",
};
const field_meta hf_solsa = {{
    "SoLSA",
    "gsm_a.SoLSA",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_solsa,
    nullptr,
    0x08,
}};

/* CMSP: CM Service Prompt (octet 5, bit 3) */
static const tf_string tfs_cmsp = {
    "Network initiated MO CM connection request supported for at least one CM protocol",
    "Network initiated MO CM connection request not supported"};
const field_meta hf_cmsp = {{
    "CMSP: CM Service Prompt",
    "gsm_a.CMSP",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_cmsp,
    nullptr,
    0x04,
}};

/* A5/3 algorithm supported (octet 5, bit 2) */
static const tf_string tfs_a53_algorithm_support = {
    "encryption algorithm A5/3 available",
    "encryption algorithm A5/3 not available",
};
const field_meta hf_a53_algorighm_support = {{
    "A5/3 algorithm supported",
    "gsm_a.A5_3_algorithm_sup",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_a53_algorithm_support,
    nullptr,
    0x02,
}};

/* A5/2 algorithm supported (octet 5, bit 1) */
static const tf_string tfs_a52_algorithm_support = {
    "encryption algorithm A5/2 available",
    "encryption algorithm A5/2 not available",
};
const field_meta hf_a52_algorithm_support = {{
    "A5/2 algorithm supported",
    "gsm_a.A5_2_algorithm_sup",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_a52_algorithm_support,
    nullptr,
    0x01,
}};

// 9.11.3.61	Mobile station classmark 2
// See subclause 10.5.1.6 in 3GPP TS 24.008 [12].
int dissect_mobile_station_classmark2(dissector d, context* ctx) {
    const use_context uc(ctx, "mobile-station-classmark2", d, 0);

    (void) d.add_item(1, &hf_msc_revision_level);
    (void) d.add_item(1, &hf_es_indication);
    (void) d.add_item(1, &hf_a51_algorithm_support);
    (void) d.add_item(1, &hf_rf_power_capability);

    d.step(1);

    if (d.length <= 0) return uc.length;

    (void) d.add_item(1, &hf_ps_support_capability);
    (void) d.add_item(1, &hf_ss_screening_indicator);
    (void) d.add_item(1, &hf_nrsm_capability);
    (void) d.add_item(1, &hf_vbs_notification_rec);
    (void) d.add_item(1, &hf_vgcs_notification_reception);
    (void) d.add_item(1, &hf_fc_frequency_capability);

    d.step(1);
    if (d.length <= 0) return uc.length;

    d.add_item(1, &hf_cm3);
    d.add_item(1, &hf_lcs_va_capability);
    d.add_item(1, &hf_ucs2_treatmeant);
    d.add_item(1, &hf_solsa);
    d.add_item(1, &hf_cmsp);
    d.add_item(1, &hf_a53_algorighm_support);
    d.add_item(1, &hf_a52_algorithm_support);

    d.step(1);
    return d.offset - uc.offset;
}
