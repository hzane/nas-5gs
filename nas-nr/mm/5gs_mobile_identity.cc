#include "../common/common.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace mm;

extern const tag_field hf_identity_type;

// 9.11.3.4 5GS mobile identity
int mm::dissect_mobile_id(dissector d, context* ctx) {
    const use_context uc(ctx, "mobile-id", d, 0);

    const auto oct      = d.uint8();
    const auto type_id  = oct & 0x07u;

    int consumed = 0;
    switch (type_id) {
    case 0:
        // no identity
        consumed = dissect_mobile_id_noid(d, ctx);
        d.step(consumed);
        break;
    case 1:
        // SUCI
        consumed = dissect_mobile_id_suci(d, ctx);
        d.step(consumed);
        break;
    case 2:
        // 5G-GUTI
        consumed = dissect_mobile_id_5gguti(d, ctx);
        d.step(consumed);
        break;
    case 3:
        // IMEI
        dissect_mobile_id_imei(d, ctx);
        d.step(d.length);
        break;
    case 4:
        // 5G-S-TMSI
        consumed = dissect_mobile_id_5gstmsi(d, ctx);
        d.step(consumed);
        break;
    case 5:
        // IMEISV
        dissect_mobile_id_imeisv(d, ctx);
        d.step(d.length);
        break;
    case 6:
        // MAC address
        dissect_mobile_id_mac(d, ctx);
        d.step(7);
        break;
    default:
        (void) d.add_item(&hf_identity_type);
        diag("unknown mobile type id %d\n", type_id);
        break;
    }

    return uc.length;
}

const mac_field hf_mac_address = {
    "MAC address",
};

// type_id = 6, MAC address
int mm::dissect_mobile_id_mac(dissector d, context* ctx) {
    const use_context uc(ctx, "mobile-id-mac", d, 0);

    (void) d.add_item(&hf_identity_type);
    d.step(1);

    (void) d.add_item(&hf_mac_address);
    d.step(6);

    return 7;
}

const uint16_field hf_amf_set_id = {
    "AMF Set ID",
    0xffc0,
};

extern const bool_field hf_odd_even_indication = {
    "Odd/even indication",
    0x08,
    tfs_odd_even,
};

// type_id = 0, no identity
int mm::dissect_mobile_id_noid(dissector d, context* ctx) {
    const use_context uc(ctx, "mobile-no-identity", d, -1);

    d.add_item(&hf_odd_even_indication);
    d.add_item(&hf_identity_type);
    d.step(1);

    return 1;
}


const uint8_field hf_amf_pointer = {
    "AMF Pointer",
    0x3f,
};


const octet_field hf_5g_tmsi = {
    "5G-TMSI",
};

// type_id = 4, 5G-S-TMSI
int mm::dissect_mobile_id_5gstmsi(dissector d, context* ctx) {
    const use_context uc(ctx, "mobile-id-5gs-tmis", d, 0);

    (void) d.add_item(&hf_identity_type);
    d.step(1);

    /* AMF Set ID */
    (void) d.add_item(&hf_amf_set_id);
    d.step(1);

    /* AMF Pointer AMF */
    (void) d.add_item(&hf_amf_pointer);
    d.step(1);

    (void) d.add_item(&hf_5g_tmsi, 4);
    d.step(4);

    return 7;
}


const tag_field hf_supi_format = {
    "SUPI format",
    0x70,
    (const v_string[]){
        {0x0, "IMSI"},
        {0x1, "Network Specific Identifier"},
        {0, nullptr},
    },
};


const bcd_field hf_routing_indication = {
    "Routing indicator",
};


const tag_field hf_protection_scheme_id = {
    "Protection scheme Id",
    0x0f,
    (const v_string[]){
        {0x0, "NULL scheme"},
        {0x1, "ECIES scheme profile A"},
        {0x2, "ECIES scheme profile B"},
        {0, nullptr},
    },
};


const uint8_field hf_public_key_identifier = {
    "Home network public key identifier",
    0x0,
};


const bcd_field hf_msin = {
    "Scheme output - MSIN",
};


const string_field hf_suci_nai = {
    "NAI",
};


const octet_field hf_mm_scheme_output = {
    "Scheme output - Network specific identifier",
};

// type_id = 1, SUCI
int mm::dissect_mobile_id_suci(dissector d, context* ctx) {
    const use_context uc(ctx, "mobile-id-suci", d, 0);

    const auto oct = d.uint8();

    d.add_item(&hf_supi_format);
    d.add_item(&hf_identity_type);

    d.step(1);

    const auto supi_fmt = oct & 0x70u;
    if (supi_fmt != 1) { // supi_fmt == 0
        // IMSI
        const auto consumed = dissect_e212_mcc_mnc(d, ctx);
        d.step(consumed);

        /* Routing indicator octet 8-9 */
        (void) d.add_item(&hf_routing_indication, 2);
        d.step(2);

        /* Protection scheme id octet 10 */
        const auto scheme_id = d.uint8() & 0x0fu;
        (void) d.add_item(&hf_protection_scheme_id);
        d.step(1);

        /* Home network public key identifier octet 11 */
        (void) d.add_item(&hf_public_key_identifier);
        d.step(1);

        /* Scheme output octet 12-x */
        // Null scheme
        if (scheme_id == 0)
            (void) d.add_item(&hf_msin, d.length);
        else
            (void) d.add_item(&hf_mm_scheme_output, d.length);

        d.step(d.length);
    }
    if (supi_fmt == 1) {
        // nai, network specific identifier
        (void) d.add_item(&hf_suci_nai, d.length);
        d.step(d.length);
    }
    return uc.length;
}


const uint8_field hf_amf_region_id = {
    "AMF Region ID",
};

// type_id = 2, 5G-GUTI
int mm::dissect_mobile_id_5gguti(dissector d, context* ctx) {
    const use_context uc(ctx, "mobile-id-5g-guti", d, 0);

    (void) d.add_item( &hf_identity_type);
    d.step(1);

    const auto consumed = dissect_e212_mcc_mnc(d, ctx);
    d.step(consumed);

    /* AMF Region ID octet 7 */
    (void) d.add_item(&hf_amf_region_id);
    d.step(1);

    /* AMF Set ID octet 8-9 10bits */
    (void) d.add_item(&hf_amf_set_id);
    d.step(1);

    /* AMF AMF Pointer*/
    (void) d.add_item(&hf_amf_pointer);
    d.step(1);

    (void) d.add_item(&hf_5g_tmsi, 4);
    d.step(4);

    return 11;
}


const imei_field hf_imei = {
    "IMEI",
};

// type_id = 3, IMEI
int mm::dissect_mobile_id_imei(dissector d, context* ctx) {
    const use_context uc(ctx, "mobile-id-imei", d, 0);

    d.add_item(&hf_odd_even_indication);
    d.add_item(&hf_identity_type);
    d.step(1);

    // The format of the IMEI is described in 3GPP TS 23.003
    (void) d.add_item(&hf_imei, d.length);
    d.step(d.length);

    return uc.length;
}

const imei_field hf_imeisv = {
    "IMEISV",
};

// type_id = 5, IMEISV
int mm::dissect_mobile_id_imeisv(dissector d, context* ctx) {
    const use_context uc(ctx, "mobile-id-imeisv", d, 0);

    d.add_item(&hf_odd_even_indication);
    d.add_item(&hf_identity_type);
    d.step(1);

    // The format of the IMEISV is described in 3GPP TS 23.003
    (void) d.add_item(&hf_imeisv, d.length);
    d.step(d.length);

    return uc.length;
}
