#include "../common.hh"

// S-NSSAI   9.11.2.8
extern const element_meta cmn::s_nssai = {
    0x22,
    "S-NSSAI",
    cmn::dissect_s_nssai,
    nullptr,
};

namespace {
const field_meta hf_sst = {
    "Slice/service type (SST)",
    "nas.nr.mm.sst",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_sd = {
    "Slice differentiator (SD)",
    "nas.nr.mm.mm_sd",
    ft::ft_uint24,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_mapped_conf_sst = {
    "Mapped configured SST",
    "nas.nr.mm.mapped_conf_sst",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_mapped_conf_ssd = {
    "Mapped configured SD",
    "nas.nr.mm.mapped_conf_ssd",
    ft::ft_uint24,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
}

/* 9.11.2.8    S-NSSAI */
int cmn::dissect_s_nssai(dissector d, context* ctx) {
    const use_context uc(ctx, "s-nssai", d, 0);

    /* SST    octet 3
     * This field contains the 8 bit SST value. The coding of the SST value part is
     * defined in 3GPP TS 23.003
     */
    (void) d.add_item(1, &hf_sst, enc::be);
    d.step(1);
    if (d.length<=0) return uc.length;

    /* SD    octet 4 - octet 6* */
    (void) d.add_item(3, &hf_sd, enc::be);
    d.step(3);

    if (d.length <= 0) return uc.length;

    /* Mapped configured SST    octet 7* */
    (void) d.add_item(1, &hf_mapped_conf_sst, enc::be);
    d.step(1);
    if (d.length <= 0) return uc.length;

    /* Mapped configured SD    octet 8 - octet 10* */
    (void) d.add_item(3, &hf_mapped_conf_ssd, enc::be);
    d.step(3);

    return uc.length;
}

