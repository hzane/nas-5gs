#include "common.hh"
#include "../common/use_context.hh"

// S-NSSAI   9.11.2.8
extern const element_meta cmn::s_nssai = {
    0x22,
    "S-NSSAI",
    cmn::dissect_s_nssai,
    nullptr,
};

namespace {
const field_meta hf_slice_service_type = {
    "Slice/service type (SST)",
    "nas.nr.mm.sst",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

// The coding of the SD value part is defined in 3GPP TS 23.003 [4].
const field_meta hf_slice_differentiator = {
    "Slice differentiator (SD)",
    "nas.nr.mm.slice.differentiator",
    ft::ft_uint24,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_mapped_conf_sst = {
    "Mapped configured SST",
    "nas.nr.mm.mapped.configured.sst",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_mapped_conf_sd = {
    "Mapped configured SD",
    "nas.nr.mm.mapped.configured.sd",
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
    (void) d.add_item(1, &hf_slice_service_type);
    d.step(1);
    if (d.length<=0) return uc.length;

    /* SD    octet 4 - octet 6* */
    (void) d.add_item(3, &hf_slice_differentiator);
    d.step(3);

    if (d.length <= 0) return uc.length;

    /* Mapped configured SST    octet 7* */
    (void) d.add_item(1, &hf_mapped_conf_sst);
    d.step(1);
    if (d.length <= 0) return uc.length;

    /* Mapped configured SD    octet 8 - octet 10* */
    (void) d.add_item(3, &hf_mapped_conf_sd);
    d.step(3);

    return uc.length;
}

struct sd_t {
    uint8_t _[3];
};
struct mapped_configured_sst_t {
    uint8_t _;
};

struct nssai_t {
    uint8_t sst{};
    std::optional<sd_t> sd;
    std::optional<mapped_configured_sst_t> mapped_configured_sst;
    std::optional<sd_t> mapped_configured_sd;
};
