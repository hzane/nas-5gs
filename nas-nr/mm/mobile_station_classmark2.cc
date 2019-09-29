#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

/* Mobile Station Classmark Revision level */
const tag_field hf_msc_revision_level = {
    "Revision Level",
    0x40,
    (const v_string[]){
        {0, "Reserved for GSM phase 1"},
        {1, "Used by GSM phase 2 mobile stations"},
        {2, "Used by mobile stations supporting R99 or later versions of the protocol"},
        {3, "Reserved for future use"},
        {0, nullptr},
    },
};

/* ES IND (octet 3, bit 5) "Controlled Early Classmark Sending" option implementation */
const bool_field hf_es_indication = {
    "ES IND",
    0x10,
    "Controlled Early Classmark Sending option is not implemented in the MS",
    "Controlled Early Classmark Sending option is implemented in the MS",
};


/* A5/1 algorithm supported (octet 3, bit 4) */
const bool_field hf_a51_algorithm_support = {
    "A5/1 algorithm supported",
    0x08,
    "encryption algorithm A5/1 available",
    "encryption algorithm A5/1 not available",
};

/* RF Power Capability (Octet 3) */
const tag_field hf_rf_power_capability = {
    "RF Power Capability",
    0x07,
    (const v_string[]){
        {0, "class 1"},
        {1, "class 2"},
        {2, "class 3"},
        {3, "class 4"},
        {4, "class 5"},
        {7, "RF Power capability is irrelevant in this information element"},
        {0, nullptr},
    },
};

/* PS capability (pseudo-synchronization capability) (octet 4) */
const bool_field hf_ps_support_capability = {
    "PS capability (pseudo-synchronization capability)",
    0x40,
    "PS capability not present",
    "PS capability present",
};

/* SS Screening Indicator (octet 4)defined in 3GPP TS 24.080 */
const tag_field hf_ss_screening_indicator = {
    "SS Screening Indicator",
    0x30,
    (const v_string[]){
        {0, "Default value of phase 1"},
        {1, "Capability of handling of ellipsis notation and phase 2 error handling "},
        {2, "For future use"},
        {3, "For future use"},
        {0, nullptr},
    },
};

/* SM capability (MT SMS pt to pt capability) (octet 4)*/
const bool_field hf_nrsm_capability = {
    "SM capability (MT SMS pt to pt capability)",
    0x08,
    "Mobile station does not support mobile terminated point to point SMS",
    "Mobile station supports mobile terminated point to point SMS",
};

/* VBS notification reception (octet 4) */
const bool_field hf_vbs_notification_rec = {
    "VBS notification reception",
    0x04,
    "no VBS capability or no notifications wanted",
    "VBS capability and notifications wanted",
};

/* VGCS notification reception (octet 4) */
const bool_field hf_vgcs_notification_reception = {
    "VGCS notification reception",
    0x02,
    "no VGCS capability or no notifications wanted",
    "VGCS capability and notifications wanted",
};

/* FC Frequency Capability (octet 4 ) */
const bool_field hf_fc_frequency_capability = {
    "FC Frequency Capability",
    0x01,
    "The MS does support the E-GSM or R-GSM",
    "The MS does not support the E-GSM or R-GSM band",
};

/* CM3 (octet 5, bit 8) */
const bool_field hf_cm3 = {
    "CM3",
    0x80,
    "The MS does not support any options that are indicated in CM3",
    "The MS supports options that are indicated in classmark 3 IE",
};

/* LCS VA capability (LCS value added location request notification capability) (octet
 * 5,bit 6) */
const bool_field hf_lcs_va_capability = {
    "LCS VA capability (LCS value added location request notification capability)",
    0x20,
    "LCS value added location request notification capability not supported",
    "LCS value added location request notification capability supported",
};

/* UCS2 treatment (octet 5, bit 5) */
static const tf_string tfs_ucs2_treatment = {
};

const bool_field hf_ucs2_treatmeant = {
    "UCS2 treatment",
    0x10,
                                           "the ME has a preference for the default alphabet",
                                           "the ME has no preference between the use of the default alphabet and the use of "
                                           "UCS2",
};

/* SoLSA (octet 5, bit 4) */
const bool_field hf_solsa = {
    "SoLSA",
    0x08,
    "The ME does not support SoLSA",
    "The ME supports SoLSA",
};

/* CMSP: CM Service Prompt (octet 5, bit 3) */
const bool_field hf_cmsp = {
    "CMSP: CM Service Prompt",
    0x04,
    "Network initiated MO CM connection request supported for at least one CM protocol",
    "Network initiated MO CM connection request not supported",
};

/* A5/3 algorithm supported (octet 5, bit 2) */
const bool_field hf_a53_algorighm_support = {
    "A5/3 algorithm supported",
    0x02,
    "encryption algorithm A5/3 not available",
    "encryption algorithm A5/3 available",
};

/* A5/2 algorithm supported (octet 5, bit 1) */
const bool_field hf_a52_algorithm_support = {
    "A5/2 algorithm supported",
    0x01,
    "encryption algorithm A5/2 not available",
    "encryption algorithm A5/2 available",
};

// 9.11.3.61	Mobile station classmark 2
// See subclause 10.5.1.6 in 3GPP TS 24.008 [12].
int dissect_mobile_station_classmark2(dissector d, context* ctx) {
    const use_context uc(ctx, "mobile-station-classmark2", d, 0);

    (void) d.add_item( &hf_msc_revision_level);
    (void) d.add_item( &hf_es_indication);
    (void) d.add_item( &hf_a51_algorithm_support);
    (void) d.add_item( &hf_rf_power_capability);

    d.step(1);

    if (d.length <= 0) return uc.length;

    (void) d.add_item( &hf_ps_support_capability);
    (void) d.add_item( &hf_ss_screening_indicator);
    (void) d.add_item( &hf_nrsm_capability);
    (void) d.add_item( &hf_vbs_notification_rec);
    (void) d.add_item( &hf_vgcs_notification_reception);
    (void) d.add_item( &hf_fc_frequency_capability);

    d.step(1);
    if (d.length <= 0) return uc.length;

    d.add_item( &hf_cm3);
    d.add_item( &hf_lcs_va_capability);
    d.add_item( &hf_ucs2_treatmeant);
    d.add_item( &hf_solsa);
    d.add_item( &hf_cmsp);
    d.add_item( &hf_a53_algorighm_support);
    d.add_item( &hf_a52_algorithm_support);

    d.step(1);
    return d.offset - uc.offset;
}
