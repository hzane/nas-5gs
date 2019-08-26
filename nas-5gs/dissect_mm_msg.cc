#include "dissect_mm_msg.hh"
#include "ts24007.hh"


extern const field_meta hf_abba = {
    "ABBA Contents",
    "nas_5gs.mm.abba_contents",
    ft::ft_uint16,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x00,
};
/*
 * 8.2.15 De-registration accept (UE terminated de-registration)
 */
/* No data */

/*
 * 9.11.3.10    ABBA
 */
int dissect_abba(dissector d, context* ctx) {
    d.add_item(d.length, &hf_abba, enc::be);
    return d.length;
}



extern const field_meta hf_sst = {
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

int dissect_nssai(dissector d, context* ctx) {
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

    return len;
}

const field_meta hf_mm_length = {
    "Length",
    "nas_5gs.mm.length",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

/*
 *   9.11.3.37    NSSAI
 */
int mm::dissect_allowed_nssai(dissector d, context* ctx) {
    auto len = d.length;
    auto i   = 0;
    while (d.length > 0) {
        auto subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, "S-NSSAI %u", i);
        d.tree       = subtree;
        auto l       = d.tvb->get_uint8(d.offset);
        auto item    = d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        auto consumed = dissect_nssai(d.slice(l), ctx);
        d.tree->set_length(consumed + 1);
        d.step(consumed);

        i++;
    }
    return len;
}
