#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// type_id = 2, 5G-GUTI
result_t die_guti_nmid(dissector d, context* ctx, guti_nmid_t* ret) {
    const use_context uc(&d, ctx, "guti-nr-mobile-id", 0);

    de_uint8(d, ctx, &ret->type, 0x07).step(d);
    die_mcc_mnc(d, ctx, &ret->mccmnc).step(d);

    ret->amf_region_id = d.uint8(true);
    ret->amf_set_id    = mask_u16(d.uint16(false), 0xffc0u);
    ret->amf_pointer   = mask_u8(d.uint8(true, 1), 0x3f);

    de_fixed(d, ctx, ret->tmsi).step(d);

    return {uc.consumed()};
}

// type_id = 3, IMEI
// type_id = 5, IMEISV
result_t die_imeisv_nmid(dissector d, context* ctx, imeisv_nmid_t* ret) {
    const use_context uc(&d, ctx, "imeisv-nr-mobile-id", 0);

    static const char bcds[] = "0123456789????\0";
    ret->type                = mask_u8(d.uint8(false), 0x07);
    ret->odd_ind             = mask_u8(d.uint8(false), 0x08);
    ret->digits.push_back(bcds[mask_u8(d.uint8(true), 0xf0u)]);
    while (d.length > 0) {
        auto i = d.uint8(true);
        ret->digits.push_back(bcds[mask_u8(i, 0x0fu)]);
        ret->digits.push_back(bcds[mask_u8(i, 0xf0u)]);
    }

    return {uc.consumed()};
}

// type_id = 1, SUCI, nai
result_t die_suci_nai_nmid(dissector d, context* ctx, suci_nmid_t::nai_t* ret) {
    const use_context uc(&d, ctx, "suci-nmid-nai", 0);

    de_uint8(d, ctx, &ret->type, 0x07);
    de_uint8(d, ctx, &ret->supi_format, 0x70u).step(d);
    de_octet(d, ctx, &ret->suci_nai).step(d);

    return {uc.consumed()};
}

// type_id = 1, SUCI, imsi
result_t die_suci_imsi_nmid(dissector d, context* ctx, suci_nmid_t::imsi_t* ret) {
    const use_context uc(&d, ctx, "suci-nmid-imsi", 0);

    de_uint8(d, ctx, &ret->type, 0x07);
    de_uint8(d, ctx, &ret->supi_format, 0x70u).step(d);
    die_mcc_mnc(d, ctx, &ret->mccmnc).step(d);
    de_fixed(d, ctx, ret->routing_indicator).step(d);
    de_nibble(d, ctx, &ret->protection_scheme_id).step(d);
    de_uint8(d, ctx, &ret->home_network_public_key_id).step(d);

    if (ret->protection_scheme_id == 0) { // null scheme
        ret->msin = std::make_shared< std::vector< bit_4 > >();
        while (d.length > 0) {
            auto a = d.uint8(true);
            ret->msin->push_back(mask_u8(a, 0x0fu));
            ret->msin->push_back(mask_u8(a, 0xf0u));
        }
    } else {
        ret->scheme_output =
            std::make_shared< octet_t >(d.safe_ptr(), d.safe_ptr() + d.length);
        d.step(d.length);
    }
    return {uc.consumed()};
}

// type_id = 1, SUCI
result_t die_suci_nmid(dissector d, context* ctx, suci_nmid_t* ret) {
    const use_context uc(&d, ctx, "suci-nr-mobile-id", 0);
    ret->supi_format = mask_u8(d.uint8(false), 0x70u);
    if (ret->supi_format == 0) { // imsi
        ret->imsi = std::make_shared< suci_nmid_t::imsi_t >();
        die_suci_imsi_nmid(d, ctx, ret->imsi.get()).step(d);
    }
    if (ret->supi_format == 1) { // network specific identifier
        ret->nai = std::make_shared< suci_nai_nmid_t >();
        die_suci_nai_nmid(d, ctx, ret->nai.get()).step(d);
    }
    return {uc.consumed()};
}

// type_id = 4, 5G-S-TMSI
result_t die_s_tmsi_nmid(dissector d, context* ctx, s_tmsi_nmid_t* ret) {
    const use_context uc(&d, ctx, "s-tmsi-nr-mobile-id", 0);

    ret->type        = mask_u8(d.uint8(true), 0x07u);
    ret->amf_set_id  = mask_u16(d.uint16(false), 0xffc0u);
    ret->amf_pointer = mask_u8(d.uint8(true, 1), 0x3fu);
    de_fixed(d, ctx, ret->tmsi).step(d);

    return {uc.consumed()};
}

// type_id = 0, no identity
result_t die_noid_nmid(dissector d, context* ctx, noid_nmid_t* ret) {
    ret->type = mask_u8(d.uint8(true), 0x07u);
    return {1};
}

// type_id = 6, MAC address
result_t die_mac_nmid(dissector d, context* ctx, mac_nmid_t* ret) {
    ret->type = mask_u8(d.uint8(true), 0x07u);
    de_fixed(d, ctx, ret->mac).step(d);

    return {7};
}

// 9.11.3.4 5GS mobile identity
result_t die_nmid(dissector d, context* ctx, nmid_t* ret) {
    ret->type = d.uint8(false) & 0x07u;
    switch (ret->type) {
    case 0: // no id
        ret->noid = std::make_shared< noid_nmid_t >();
        return die_noid_nmid(d, ctx, ret->noid.get());
    case 1: // suci
        ret->suci = std::make_shared< suci_nmid_t >();
        return die_suci_nmid(d, ctx, ret->suci.get());
    case 2: // nr-guti
        ret->guti = std::make_shared< guti_nmid_t >();
        return die_guti_nmid(d, ctx, ret->guti.get());
    case 3: // imei
        ret->imei = std::make_shared< imei_nmid_t >();
        return die_imeisv_nmid(d, ctx, ret->imei.get());
    case 4: // nr-s-tmsi
        ret->stmsi = std::make_shared< s_tmsi_nmid_t >();
        return die_s_tmsi_nmid(d, ctx, ret->stmsi.get());
    case 5: // imeisv
        ret->imei = std::make_shared< imei_nmid_t >();
        return die_imeisv_nmid(d, ctx, ret->imei.get());
    case 6: // mac
        ret->mac = std::make_shared< mac_nmid_t >();
        return die_mac_nmid(d, ctx, ret->mac.get());
    }
    return {d.length};
}
