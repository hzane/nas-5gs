#include "../dissect_mm_msg.hh"
#include "../common/common.hh"

using namespace cmn;

/* 9.11.3.4    5GS mobile identity */
extern const val_string mm::mm_type_id_values[] = {
    {0x0, "No identity"},
    {0x1, "SUCI"},
    {0x2, "5G-GUTI"},
    {0x3, "IMEI"},
    {0x4, "5G-S-TMSI"},
    {0x5, "IMEISV"},
    {0, nullptr},
};

// 5GS mobile identity  9.11.3.4
const element_meta mm::mobile_id = {
    0x77,
    "5GS mobile identity",
    dissect_mobile_id,
    nullptr,
};

/* * 9.11.3.4    5GS mobile identity */
const field_meta mm::hfm_mm_type_id = {
    "Type of identity",
    "nas_5gs.mm.type_id",
    ft::ft_uint8,
    fd::base_dec,
    mm_type_id_values,
    nullptr,
    nullptr,
    0x07,
};

namespace mm {
const field_meta hf_spare_b7 = {
    "Spare",
    "nas_5gs.spare_b7",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x80,
};

const field_meta* flags_odd_even_tid[] = {
    &hf_mm_odd_even,
    &hf_mm_type_id,
    nullptr,
};
const field_meta hf_mac_address = {
    "MAC address",
    "nas_5gs.mac",
    ft::ft_bytes,
    fd::sep_colon,
    nullptr,
    nullptr,
    nullptr,
    0,
};
const val_string nas_5gs_mm_supi_fmt_vals[] = {
    {0x0, "IMSI"},
    {0x1, "Network Specific Identifier"},
    {0, nullptr},
};
const field_meta hf_nas_5gs_mm_supi_fmt = {
    "SUPI format",
    "nas_5gs.mm.suci.supi_fmt",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_mm_supi_fmt_vals),
    nullptr,
    nullptr,
    0x70,
};

const field_meta hf_nas_5gs_mm_suci_nai = {
    "NAI",
    "nas_5gs.mm.suci.nai",
    ft::ft_bytes,
    fd::base_string,
    nullptr,
    nullptr,
    nullptr,
    0,
};
const field_meta hf_nas_5gs_mm_imei = {
    "IMEI",
    "nas_5gs.mm.imei",
    ft::ft_bytes,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0,
};
const field_meta hf_spare_b3 = {
    "Spare",
    "nas_5gs.spare_b3",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x08,
};
const field_meta* flags_supi_fmt_tid[] = {
    &hf_spare_b7,
    &hf_nas_5gs_mm_supi_fmt,
    &hf_spare_b3,
    &hf_mm_type_id,
    nullptr,
};
const field_meta hf_nas_5gs_mm_imeisv = {
    "IMEISV",
    "nas_5gs.mm.imeisv",
    ft::ft_bytes,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0,
};
const field_meta hf_nas_5gs_amf_set_id = {
    "AMF Set ID",
    "nas_5gs.amf_set_id",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0xffc0,
};
const field_meta hf_nas_5gs_amf_pointer = {
    "AMF Pointer",
    "nas_5gs.amf_pointer",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x3f,
};
const field_meta hf_nas_5gs_tmsi = {
    "5G-TMSI",
    "nas_5gs.5g_tmsi",
    ft::ft_uint32,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_mm_routing_ind = {
    "Routing indicator",
    "nas_5gs.mm.suci.routing_indicator",
    ft::ft_bytes,
    fd::base_string,
    nullptr,
    nullptr,
    nullptr,
    0,
};

static const value_string nas_5gs_mm_prot_scheme_id_vals[] = {
    {0x0, "NULL scheme"},
    {0x1, "ECIES scheme profile A"},
    {0x2, "ECIES scheme profile B"},
    {0, nullptr},
};

const field_meta hf_mm_prot_scheme_id = {
    "Protection scheme Id",
    "nas_5gs.mm.suci.scheme_id",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_mm_prot_scheme_id_vals),
    nullptr,
    nullptr,
    0x0f,
};
const field_meta hf_mm_pki = {
    "Home network public key identifier",
    "nas_5gs.mm.suci.pki",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_mm_supi_null_scheme = {
    "Scheme output",
    "nas_5gs.mm.suci.supi_null_scheme",
    ft::ft_bytes,
    fd::base_string,
    nullptr,
    nullptr,
    nullptr,
    0,
};

const field_meta hf_mm_scheme_output = {
    "Scheme output",
    "nas_5gs.mm.suci.scheme_output",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_amf_region_id = {
    "AMF Region ID",
    "nas_5gs.amf_region_id",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_amf_set_id = {
    "AMF Set ID",
    "nas_5gs.amf_set_id",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0xffc0,
};
const field_meta hf_amf_pointer = {
    "AMF Pointer",
    "nas_5gs.amf_pointer",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x3f,
};
const field_meta hf_5g_tmsi = {
    "5G-TMSI",
    "nas_5gs.5g_tmsi",
    ft::ft_uint32,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};


} // namespace


extern const field_meta mm::hf_mm_type_id = {
    "Type of identity",
    "nas_5gs.mm.type_id",
    ft::ft_uint8,
    fd::base_dec,
    (mm_type_id_values),
    nullptr,
    nullptr,
    0x07,
};

const true_false_string mm::tfs_odd_even = {
    "Odd number of identity digits",
    "Even number of identity digits",
};
extern const field_meta mm::hf_mm_odd_even = {
    "Odd/even indication",
    "nas_5gs.mm.odd_even",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_odd_even,
    nullptr,
    0x08,
};


// type_id = 6, MAC address
int mm::dissect_mobile_id_mac(dissector d, context* ctx) {
    d.add_bits(flags_odd_even_tid);
    d.step(1);

    d.add_item(6, &hf_mac_address, enc::be);
    d.step(6);

    d.extraneous_data_check(0);
    return 7;
}

// type_id = 0, no identity
int mm::dissect_mobile_id_noid(dissector d, context* ctx) {
    d.add_bits(flags_odd_even_tid);
    d.step(1);

    d.extraneous_data_check(0);
    return 1;
}

// type_id = 4, 5G-S-TMSI
int mm::dissect_mobile_id_5gstmsi(dissector d, context* ctx) {
    d.add_bits(flags_odd_even_tid);
    d.step(1);

    /* AMF Set ID */
    auto item = d.add_item(2, &hf_nas_5gs_amf_set_id, enc::be);

    d.step(1);
    /* AMF Pointer AMF Set ID (continued) */
    d.add_item(1, &hf_nas_5gs_amf_pointer, enc::be);
    d.step(1);

    d.add_item(4, &hf_nas_5gs_tmsi, enc::be);
    d.step(4);

    d.extraneous_data_check(0);
    return 7;
}

// type_id = 1, SUCI
int mm::dissect_mobile_id_suci(dissector d, context* ctx) {
    auto oct = d.uint8();
    d.add_bits(flags_supi_fmt_tid);
    d.step(1);

    const auto supi_fmt = oct & 0x70;
    if (supi_fmt == 0) {
        // IMSI
        /* MCC digit 2    MCC digit 1
         * MNC digit 3    MCC digit 3
         * MNC digit 2    MNC digit 1             */
        auto consumed = dissect_e212_mcc_mnc(d, ctx);
        d.step(consumed);

        /* Routing indicator octet 8-9 */
        d.add_item(2, &hf_mm_routing_ind, enc::na);
        d.step(2);

        /* Protection scheme id octet 10 */
        const auto scheme_id = d.uint8() & 0x0fu;
        d.add_item(1, &hf_mm_prot_scheme_id, enc::be);
        d.step(1);

        /* Home network public key identifier octet 11 */
        d.add_item(1, &hf_mm_pki, enc::be);
        d.step(1);

        /* Scheme output octet 12-x */
        if (scheme_id == 0) {
            // Null scheme
            d.add_item(d.length, &hf_mm_supi_null_scheme, enc::be);
        } else {
            d.add_item(d.length, &hf_mm_scheme_output, enc::na);
        }
        d.step(d.length);
    } else if (supi_fmt == 1) {
        // nai, network specific identifier
        d.add_item(d.length, &hf_nas_5gs_mm_suci_nai, enc::be);
    } else {
        diag("unknown supi format %d\n", supi_fmt);
    }
    return d.length;
}

// type_id = 2, 5G-GUTI
int mm::dissect_mobile_id_5gguti(dissector d, context* ctx) {
    d.add_bits(flags_odd_even_tid);
    d.step(1);

    /* MCC digit 2    MCC digit 1
     * MNC digit 3    MCC digit 3
     * MNC digit 2    MNC digit 1 */
    auto consumed = dissect_e212_mcc_mnc(d, ctx);
    d.step(consumed);

    /* AMF Region ID octet 7 */
    d.add_item(1, &hf_amf_region_id, enc::be);
    d.step(1);

    /* AMF Set ID octet 8 */
    d.add_item(1, &hf_amf_set_id, enc::be);
    d.step(1);

    /* AMF AMF Pointer AMF Set ID (continued) */
    d.add_item(1, &hf_amf_pointer, enc::be);
    d.step(1);

    d.add_item(4, &hf_5g_tmsi, enc::be);
    d.step(4);
    return 11;
}

// type_id = 3, IMEI
int mm::dissect_mobile_id_imei(dissector d, context* ctx) {
    auto len = d.length;
    d.add_bits(flags_odd_even_tid);
    d.step(1);

    d.add_item(d.length, &hf_nas_5gs_mm_imeisv, enc::be);
    d.step(d.length);
    return len;
}

// type_id = 5, IMEISV
int mm::dissect_mobile_id_imeisv(dissector d, context* ctx) {
    return dissect_mobile_id_imei(d, ctx);
}

// 9.11.3.4
int mm::dissect_mobile_id(dissector d, context* ctx) {
    use_context uc(ctx, "mobile-id", d, 0);

    const auto oct     = d.uint8();
    const auto type_id = oct & 0x07u;
    auto       consumed = 0;

    switch (type_id) {
    case 0: {
        // no identity
        d.add_bits(flags_odd_even_tid);
    } break;
    case 1: {
        // SUCI
        consumed = dissect_mobile_id_suci(d, ctx);
        d.step(consumed);
    } break;
    case 2: {
        // 5G-GUTI
        consumed = dissect_mobile_id_5gguti(d, ctx);
        d.step(consumed);
    } break;
    case 3: {
        // IMEI
        dissect_mobile_id_imei(d, ctx);
        d.step(d.length);
    } break;
    case 4: {
        // 5G-S-TMSI
        consumed = dissect_mobile_id_5gstmsi(d, ctx);
        d.step(consumed);
    } break;
    case 5: {
        // IMEISV
        dissect_mobile_id_imeisv(d, ctx);
        d.step(d.length);
    } break;
    case 6: {
        // MAC address
        dissect_mobile_id_mac(d, ctx);
        d.step(7);
    } break;
    default: {
        auto item = d.add_item(d.length, &hf_mm_type_id, enc::be);
        diag("unknown mobile type id %d\n", type_id);
    } break;
    }

    return uc.length;
}

/*5GS mobile identity     5GS mobile identity 9.11.3.4    M    LV-E    6-n */


// *   9.11.3.32    NAS key set identifier
int mm::dissect_key_set_id(dissector d, context* ctx) { return dissect_nas_ksi(d, ctx); }
