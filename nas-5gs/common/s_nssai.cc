#include "../common.hh"

// S-NSSAI   9.11.2.8
extern const element_meta cmn::s_nssai = {
    0x22,
    "S-NSSAI",
    dissect_s_nssai,
    nullptr,
};

namespace {
const field_meta hf_sst = {
    "Slice/service type (SST)",
    "nas_5gs.mm.sst",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_sd = {
    "Slice differentiator (SD)",
    "nas_5gs.mm.mm_sd",
    ft::ft_uint24,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_mapped_conf_sst = {
    "Mapped configured SST",
    "nas_5gs.mm.mapped_conf_sst",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_mapped_conf_ssd = {
    "Mapped configured SD",
    "nas_5gs.mm.mapped_conf_ssd",
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
    auto len = d.length;
    /* SST    octet 3
     * This field contains the 8 bit SST value. The coding of the SST value part is
     * defined in 3GPP TS 23.003
     */
    d.add_item(1, &hf_sst, enc::be);
    d.step(1);
    if (len == 1) return len;

    /* SD    octet 4 - octet 6* */
    d.add_item(3, &hf_sd, enc::be);
    d.step(3);

    if (len == 4) return len;

    /* Mapped configured SST    octet 7* */
    d.add_item(1, &hf_mapped_conf_sst, enc::be);
    d.step(1);
    if (len == 5) return len;

    /* Mapped configured SD    octet 8 - octet 10* */
    d.add_item(3, &hf_mapped_conf_ssd, enc::be);
    d.step(3);

    d.extraneous_data_check(0);
    return len;
}
