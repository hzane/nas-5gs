#include "common.hh"
#include "../common/use_context.hh"

// S-NSSAI   9.11.2.8
extern const element_meta cmn::s_nssai = {
    0x22,
    "S-NSSAI",
    cmn::dissect_s_nssai,
};


const uint8_field hf_slice_service_type = {
    "Slice/service type (SST)",
    0x0,
};

// The coding of the SD value part is defined in 3GPP TS 23.003 [4].
const uint24_field hf_slice_differentiator = {
    "Slice differentiator (SD)",
    0x0,
};

const uint8_field hf_mapped_conf_sst = {
    "Mapped configured SST",
    0x0,
};

const uint24_field hf_mapped_conf_sd = {
    "Mapped configured SD",
    0x0,
};


/* 9.11.2.8    S-NSSAI */
int cmn::dissect_s_nssai(dissector d, context* ctx) {
    const use_context uc(ctx, "s-nssai", d, 0);

    /* SST    octet 3
     * This field contains the 8 bit SST value. The coding of the SST value part is
     * defined in 3GPP TS 23.003
     */
    (void) d.add_item(&hf_slice_service_type);
    d.step(1);
    if (d.length<=0) return uc.length;

    /* SD    octet 4 - octet 6* */
    (void) d.add_item(&hf_slice_differentiator);
    d.step(3);

    if (d.length <= 0) return uc.length;

    /* Mapped configured SST    octet 7* */
    (void) d.add_item(&hf_mapped_conf_sst);
    d.step(1);
    if (d.length <= 0) return uc.length;

    /* Mapped configured SD    octet 8 - octet 10* */
    (void) d.add_item(&hf_mapped_conf_sd);
    d.step(3);

    return uc.length;
}

