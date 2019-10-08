#include "ies.hh"
#include "messages.hh"

/*
9.11.2.6	Intra N1 mode NAS transparent container
*/
result_t die_intra_n1_mode_container(dissector                  d,
                                     context*                   ctx,
                                     intra_n1_mode_container_t* ret) {
    const use_context uc(&d, ctx, "intra-n1-mode-container", 0);

    // Message authentication code	octet 3  octet 6
    de_fixed(d, ctx, ret->auth_code).step(d);

    // Type of ciphering algorithm	Type of integrity protection algorithm	octet 7
    de_nibble(d, ctx, &ret->integrity_algo);
    de_uint8(d, ctx, &ret->ciphering_algo, 0xf0u).step(d);

    // 0	0 Spare	0	KACF	TSC	Key set identifier in 5G	octet 8
    de_uint8(d, ctx, &ret->kacf, 0x10u);
    de_uint8(d, ctx, &ret->tsc, 0x10u);
    de_uint8(d, ctx, &ret->nksi, 0x07u).step(d);

    // Sequence number	octet 9
    de_uint8(d, ctx, &ret->seq_no).step(d);

    return {uc.consumed()};
}


// 9.11.2.7	N1 mode to S1 mode NAS transparent container
result_t die_n1_mode_to_s1_mode_container(dissector                       d,
                                          context*                        ctx,
                                          n1_mode_to_s1_mode_container_t* ret) {
    const use_context uc(&d, ctx, "n1-mode-to-s1-mode-container", 0);

    de_uint8(d, ctx, &ret->seq_no).step(d);
    return {uc.consumed()};
}


//    9.11.2.8	S-NSSAI
result_t die_s_nssai(dissector d, context* ctx, s_nssai_t* ret) {
    auto              len = d.length;
    const use_context uc(&d, ctx, "s-nssai", 0);

    // SST	octet 3
    de_uint8(d, ctx, &ret->sst).step(d);

    if (len == 0x02) { // sst and mapped hplmn sst
        ret->mapped_hplmn_sst.present = true;
        de_uint8(d, ctx, &ret->mapped_hplmn_sst.v).step(d);
    }
    if (len >= 0x04) { // sst and sd
        ret->sd.present = true;
        de_fixed(d, ctx, ret->sd.v).step(d);
    }
    if (len >= 0x05) { // sst, sd and mapped hplmn sst
        ret->mapped_hplmn_sst.present = true;
        de_uint8(d, ctx, &ret->mapped_hplmn_sst.v).step(d);
    }
    if (len == 0x08) { // sst, sd, mapped hplmn sst and hplmn sd
        ret->mapped_hplmn_sd.present = true;
        de_fixed(d, ctx, ret->mapped_hplmn_sd.v).step(d);
    }
    return {uc.consumed()};
}


// 9.11.2.9
result_t die_s1_mode_to_n1_mode_containers(dissector                       d,
                                           context*                        ctx,
                                           s1_mode_to_n1_mode_container_t* ret) {
    const use_context uc(&d, ctx, "s1-mode-to-n1-mode-container", 2);

    de_fixed(d, ctx, ret->auth_code).step(d);

    de_uint8(d, ctx, &ret->integrity_algo, 0x0f);
    de_uint8(d, ctx, &ret->ciphering_algo, 0xf0u).step(d);

    de_uint8(d, ctx, &ret->nksi, 0x07u);
    de_uint8(d, ctx, &ret->tsc, 0x04);
    de_uint8(d, ctx, &ret->ncc, 0x70u).step(d);

    return {uc.length};
}


// 9.11.3.1	5GMM capability
result_t die_nmm_capability(dissector d, context* ctx, nmm_capability_t* ret) {
    const use_context uc(&d, ctx, "nmm-capability", 11);
    auto              o3 = d.uint8(true);
    ret->s1_mode         = mask_u8(o3, 0x01);
    ret->ho_attach       = mask_u8(o3, 0x02);
    ret->lpp             = mask_u8(o3, 0x04);
    ret->restrict_ec     = mask_u8(o3, 0x08);
    ret->ncp_ciot        = mask_u8(o3, 0x10);
    ret->n3data          = mask_u8(o3, 0x20);
    ret->nhccp_ciot      = mask_u8(o3, 0x40);
    ret->sgc             = mask_u8(o3, 0x80u);

    if (d.length > 0) {
        auto o4       = d.uint8(true);
        ret->nsrvcc   = mask_u8(o4, 0x01);
        ret->nup_ciot = mask_u8(o4, 0x02);
    }

    return {uc.length};
}


result_t die_mcc_mnc(dissector d, context* ctx, mcc_mnc_t* ret) {
    const use_context uc(&d, ctx, "mcc-mnc", 0);
    auto              a = d.uint8(true), b = d.uint8(true), c = d.uint8(true);

    ret->mcc = (a & 0x0fu) * 100 + ((a & 0xf0u) >> 4u) * 10 + (b & 0x0fu);

    /* MNC, Mobile network code (octet 3 bits 5 to 8, octet 4)  */
    const auto mnc3 = b >> 4u;
    const auto mnc1 = c & 0x0fu;
    const auto mnc2 = c >> 4u;

    ret->mnc = 10 * mnc1 + mnc2;
    if (mnc3 != 0xf) ret->mnc = ret->mnc * 10 + mnc3;

    return {uc.consumed()};
}


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


result_t die_suci_nai_nmid(dissector d, context* ctx, suci_nmid_t::nai_t* ret) {
    const use_context uc(&d, ctx, "suci-nmid-nai", 0);

    de_uint8(d, ctx, &ret->type, 0x07);
    de_uint8(d, ctx, &ret->supi_format, 0x70u).step(d);
    de_octet(d, ctx, &ret->suci_nai).step(d);

    return {uc.consumed()};
}
result_t die_suci_imsi_nmid(dissector d, context *ctx, suci_nmid_t::imsi_t* ret) {
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
        ret->scheme_output = std::make_shared<octet_t>(d.safe_ptr(), d.safe_ptr() + d.length);
        d.step(d.length);
    }
    return {uc.consumed()};
}

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


result_t die_s_tmsi_nmid(dissector d, context* ctx, s_tmsi_nmid_t* ret) {
    const use_context uc(&d, ctx, "s-tmsi-nr-mobile-id", 0);

    ret->type        = mask_u8(d.uint8(true), 0x07u);
    ret->amf_set_id  = mask_u16(d.uint16(false), 0xffc0u);
    ret->amf_pointer = mask_u8(d.uint8(true, 1), 0x3fu);
    de_fixed(d, ctx, ret->tmsi).step(d);

    return {uc.consumed()};
}


result_t die_noid_nmid(dissector d, context* ctx, noid_nmid_t* ret) {
    ret->type = mask_u8(d.uint8(true), 0x07u);
    return {1};
}


result_t die_mac_nmid(dissector d, context* ctx, mac_nmid_t* ret) {
    ret->type = mask_u8(d.uint8(true), 0x07u);
    de_fixed(d, ctx, ret->mac).step(d);

    return {7};
}


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


result_t die_nr_network_feature_support(dissector                     d,
                                        context*                      ctx,
                                        nr_network_feature_support_t* ret) {
    const use_context uc(&d, ctx, "nr-network-feature-support", 1);
    auto              o3 = d.uint8(true), o4 = d.uint8(true);

    ret->ims_vops_3gpp  = mask_u8(o3, 0x01);
    ret->ims_vops_n3gpp = mask_u8(o3, 0x02);
    ret->emc            = mask_u8(o3, 0x0c);

    ret->emf     = mask_u8(o3, 0x30u);
    ret->iwk_n26 = mask_u8(o3, 0x40u);
    ret->mpsi    = mask_u8(o3, 0x80u);

    ret->emcn3       = mask_u8(o4, 0x01);
    ret->mcsi        = mask_u8(o4, 0x02);
    ret->restrict_ec = mask_u8(o4, 0x04);
    ret->ncp_ciot    = mask_u8(o4, 0x08);

    ret->n3data      = mask_u8(o4, 0x10);
    ret->nhc_cp_ciot = mask_u8(o4, 0x20);
    ret->nup_ciot    = mask_u8(o4, 0x40);

    return {uc.length};
}


result_t die_nr_tracking_area_id(dissector d, context* ctx, nr_tracking_area_id_t* ret) {
    die_mcc_mnc(d, ctx, &ret->mccmnc).step(d);
    de_fixed(d, ctx, ret->tac).step(d);

    return {6};
}


result_t die_partial_tai_list_00(dissector d, context* ctx, partial_tai_list_00_t* ret) {
    const use_context uc(&d, ctx, "partial-tai-id", 0);

    de_uint8(d, ctx, &ret->number, 0x1fu);
    de_uint8(d, ctx, &ret->type, 0x60u).step(d);

    die_mcc_mnc(d, ctx, &ret->mccmnc).step(d);

    for (auto n = ret->number; n > 0;) {
        o3_t o3 = {};
        de_fixed(d, ctx, o3.v).step(d);
        ret->taces.push_back(o3);
        --n;
    }
    return {uc.consumed()};
}


result_t die_partial_tai_list_01(dissector d, context* ctx, partial_tai_list_01_t* ret) {
    const use_context uc(&d, ctx, "partial-tai-id", 0);

    de_uint8(d, ctx, &ret->number, 0x1fu);
    de_uint8(d, ctx, &ret->type, 0x60u).step(d);

    die_mcc_mnc(d, ctx, &ret->mccmnc).step(d);
    de_fixed(d, ctx, ret->tac).step(d);

    for (auto n = ret->number; n > 1; --n) {
        o3_t o3 = {};
        de_fixed(d, ctx, o3.v).step(d);
        ret->others.push_back(o3);
    }

    return {uc.consumed()};
}


result_t die_partial_tai_list_10(dissector d, context* ctx, partial_tai_list_10_t* ret) {
    const use_context uc(&d, ctx, "partial-tai-id", 0);

    de_uint8(d, ctx, &ret->number, 0x1fu);
    de_uint8(d, ctx, &ret->type, 0x60u).step(d);

    for (auto n = ret->number; n > 0;) {
        nr_tracking_area_id_t tai = {};
        die_nr_tracking_area_id(d, ctx, &tai).step(d);
        ret->ids.push_back(tai);
        --n;
    }
    return {uc.consumed()};
}


result_t die_partial_tai(dissector d, context* ctx, partial_tai_t* ret) {
    const use_context uc(&d, ctx, "partial-tai", -1);

    ret->type = mask_u8(d.uint8(false), 0x60u);
    if (ret->type == 0) {
        ret->l00 = std::make_shared< partial_tai_list_00_t >();
        die_partial_tai_list_00(d, ctx, ret->l00.get()).step(d);
    }
    if (ret->type == 1) {
        ret->l01 = std::make_shared< partial_tai_list_01_t >();
        die_partial_tai_list_01(d, ctx, ret->l01.get()).step(d);
    }
    if (ret->type == 2) {
        ret->l10 = std::make_shared< partial_tai_list_10_t >();
        die_partial_tai_list_10(d, ctx, ret->l10.get()).step(d);
    }

    return {uc.consumed()};
}

result_t die_nr_tracking_id_list(dissector d, context* ctx, nr_tracking_area_id_list_t* ret) {
    const use_context uc(&d, ctx, "nr-tracking-area-id-list", 0);

    while (d.length > 0) {
        partial_tai_t ptai = {};
        die_partial_tai(d, ctx, &ptai).step(d);
        ret->partials.push_back(ptai);
    }
    return {uc.length};
}


/*
9.11.3.9A	5GS update type
*/
result_t die_nr_update_type(dissector d, context* ctx, nr_update_type_t* ret) {
    const use_context uc(&d, ctx, "nr-update-type", 0);
    de_uint8(d, ctx, &ret->sms_requested, 0x01);
    de_uint8(d, ctx, &ret->nran_rcu, 0x02);
    de_uint8(d, ctx, &ret->pnb_ciot, 0x0c).step(d);

    return {1};
}


result_t die_configuration_update_indication(dissector                          d,
                                             context*                           ctx,
                                             configuration_update_indication_t* ret) {
    de_uint8(d, ctx, &ret->ack, 0x01);
    de_uint8(d, ctx, &ret->red, 0x02).step(d);

    return {1};
}


result_t die_deregistration_type(dissector d, context* ctx, deregistration_type_t* ret) {
    de_uint8(d, ctx, &ret->access_type, 0x03);
    de_uint8(d, ctx, &ret->reregistration_required, 0x04);
    de_uint8(d, ctx, &ret->switch_off, 0x08).step(d);

    return {1};
}


result_t die_number(dissector d, context* ctx, emergency_number_list_t::number_t* ret) {
    static char bcds[] = "0123456789????\0";
    auto        len    = d.length;
    de_uint8(d, ctx, &ret->service_category).step(d);
    while (d.length > 0) {
        auto o = d.uint8(true);
        ret->digits.push_back(bcds[mask_u8(o, 0x0f)]);
        ret->digits.push_back(bcds[mask_u8(0, 0xf0u)]);
    }
    return {len};
}
result_t die_emergency_number_list(dissector              d,
                                   context*               ctx,
                                   emergency_number_list_t* ret) {
    const use_context uc(&d, ctx, "emergency-number-list", 0);
    while (d.length > 0) {
        auto     len = d.uint8(true);
        emergency_number_list_t::number_t n   = {};
        die_number(d.slice(len), ctx, &n).step(d);
        ret->numbers.push_back(n);
    }
    return {uc.length};
}
result_t de_configuration_update_complete(dissector                        d,
                                          context*                         ctx,
                                          configuration_update_complete_t* ret) {
    const use_context uc(&d, ctx, "configuration-update-complete", 0);
    de_nmm_header(d, ctx, &ret->header).step(d);

    return {uc.consumed()};
}

result_t die_additional_nr_security_infomation(
    dissector                             d,
    context*                              ctx,
    additional_nr_security_information_t* ret) {
    de_uint8(d, ctx, &ret->hdp, 0x01);
    de_uint8(d, ctx, &ret->rinmr, 0x02).step(d);

    return {1};
}

result_t die_eps_nas_security_algorighms(dissector                      d,
                                         context*                       ctx,
                                         eps_nas_security_algorithms_t* ret) {
    de_uint8(d, ctx, &ret->integrity_algo, 0x07);

    de_uint8(d, ctx, &ret->ciphering_algo, 0x70);

    return {1};
}


result_t die_sub_service(dissector                                    d,
                         context*                                     ctx,
                         extended_emergency_number_list_t::service_t* ret) {
    static const char bcds[] = "0123456789????\0";
    auto              nlen   = d.uint8(true);
    for (auto i = nlen; i > 0; --i) {
        auto o = d.uint8(true);
        ret->digits.push_back(bcds[mask_u8(o, 0x0fu)]);
        ret->digits.push_back(bcds[mask_u8(0, 0xf0u)]);
    }

    auto slen              = d.uint8(true);
    ret->sub_service_field = string((const char*) d.safe_ptr(), d.safe_length(slen));
    d.step(slen);

    return {1 + nlen + 1 + slen};
}

result_t die_extended_emergency_number_list(dissector                         d,
                                            context*                          ctx,
                                            extended_emergency_number_list_t* ret) {
    auto len   = d.length;
    ret->eenlv = d.uint8(true) & 0x01u;

    while (d.length > 0) {
        extended_emergency_number_list_t::service_t svc = {};
        die_sub_service(d, ctx, &svc).step(d);
        ret->services.push_back(svc);
    }
    return {len};
}


result_t die_ladn_indication(dissector d, context* ctx, ladn_indication_t* ret) {
    auto len = d.length;
    while (d.length > 0) {
        auto l = d.uint8(true);
        ret->dnns.emplace_back(d.safe_ptr(), d.safe_ptr() + d.safe_length(l));
    }
    return {len};
}


/*
Figure 9.11.3.30.1: LADN information information element
8	7	6	5	4	3	2	1
Length of DNN value	octet 4
DNN value	octet 5  octet m
5GS tracking area identity list	octet m+1  octet a
*/
result_t die_ladn(dissector d, context* ctx, ladn_information_t::ladn_t* ret) {
    const use_context uc(&d, ctx, "ladn", 0);

    auto dl = d.uint8(true);
    de_octet(d.slice(dl), ctx, &ret->dnn).step(d);

    auto tl = d.uint8(true);
    die_nr_tracking_id_list(d.slice(tl), ctx, &ret->ntai).step(d);

    return {uc.length};
}

result_t dissect_ladn_information(dissector d, context* ctx, ladn_information_t* ret) {
    const use_context uc(&d, ctx, "ladn-information", 0);

    while (d.length > 0) {
        ladn_information_t::ladn_t ladn = {};
        die_ladn(d, ctx, &ladn).step(d);
        ret->ladns.push_back(ladn);
    }
    return {uc.length};
}


result_t die_mico_indication(dissector d, context* ctx, mico_indication_t* ret) {
    de_uint8(d, ctx, &ret->raai, 0x01);

    de_uint8(d, ctx, &ret->sprti, 0x02).step(d);

    return {1};
}


result_t die_nas_key_set_identifier(dissector                 d,
                                    context*                  ctx,
                                    nas_key_set_identifier_t* ret) {
    de_uint8(d, ctx, &ret->nksi, 0x07);

    de_uint8(d, ctx, &ret->tsc, 0x08).step(d);

    return {1};
}


result_t die_nas_security_algorithm(dissector                 d,
                                    context*                  ctx,
                                    nas_security_algorithm_t* ret) {
    de_uint8(d, ctx, &ret->integrity_algo);
    de_uint8(d, ctx, &ret->ciphering_algo, 0xf0u).step(d);

    return {1};
}


result_t die_network_name(dissector d, context* ctx, network_name_t* ret) {
    const use_context uc(&d, ctx, "network-name", 0);

    de_uint8(d, ctx, &ret->unused_bits, 0x07);
    de_uint8(d, ctx, &ret->add_ci, 0x08u);
    de_uint8(d, ctx, &ret->coding_scheme, 0x70u);
    de_uint8(d, ctx, &ret->ext, 0x80u).step(d);

    ret->text = octet_t(d.safe_ptr(), d.safe_ptr()+d.safe_length(d.length));

    return {uc.consumed()};
}


result_t die_network_slicing_indication(dissector                     d,
                                        context*                      ctx,
                                        network_slicing_indication_t* ret) {
    de_uint8(d, ctx, &ret->nssci, 0x01);

    de_uint8(d, ctx, &ret->dcni, 0x02).step(d);

    return {1};
}


result_t die_operator_defined_access_category_definition(
    dissector                                      d,
    context*                                       ctx,
    operator_defined_access_category_definition_t* ret) {
    const use_context uc(&d, ctx, "operator-defined-access-category-definition", 0);
    de_uint8(d, ctx, &ret->precedence).step(d);

    de_uint8(d, ctx, &ret->psac, 0x80u);
    de_uint8(d, ctx, &ret->number, 0x1fu).step(d);

    de_l_octet(d, ctx, &ret->criteria).step(d);
    if (d.length>0){
        ret->standardized_access_category.present = true;
        de_uint8(d, ctx, &ret->standardized_access_category.v, 0x1fu).step(d);
    }
    return {uc.length};
}


result_t die_operator_defined_access_category_definitions(
    dissector                                      d,
    context*                                       ctx,
    operator_defined_access_category_definitions_t* ret) {
    const use_context uc(&d, ctx, "operator-defined-access-category-definitions", 0);
    while(d.length>0){
        auto l = d.uint8(true);
        operator_defined_access_category_definition_t v = {};
        die_operator_defined_access_category_definition(d.slice(l), ctx, &v).step(d);
        ret->definitions.push_back(v);
    }
    return {uc.length};
}


result_t die_pdu_session_reactivation_result(dissector d, context* ctx, pdu_session_reactivation_result_t* ret){
    const use_context uc(&d, ctx, "pdu-session-reactivation-result", 0);

    ret->psi_a = d.uint8(true);
    ret->psi_b = d.uint8(true);

    return {2};
}


result_t die_pdu_session_reactivation_result_error_cause(dissector d, context* ctx, pdu_session_reactivation_result_error_cause_t *ret){
    const use_context uc(&d, ctx, "pdu-session-reactivation-result-error-cause", 0);
    while(d.length>0){
        pdu_session_reactivation_result_error_cause_t::cause_t v = {};
        de_uint8(d, ctx, &v.pdu_session_id).step(d);
        de_uint8(d, ctx, &v.cause).step(d);
        ret->causes.push_back(v);
    }
    return {uc.length};
}


result_t die_pdu_session_status(dissector d, context* ctx, pdu_session_status_t* ret) {
    const use_context uc(&d, ctx, "pdu-session-reactivation-result", 0);

    ret->psi_a = d.uint8(true);
    ret->psi_b = d.uint8(true);

    return {2};
}


result_t die_plmn_list(dissector d, context* ctx, plmn_list_t*ret){
    const use_context uc(&d, ctx, "plmn-list", 0);
    while(d.length>0){
        mcc_mnc_t mm = {};
        die_mcc_mnc(d, ctx, &mm).step(d);
        ret->plmns.push_back(mm);
    }
    return {uc.length};
}

result_t die_rejected_nssai(dissector d, context* ctx, rejected_nssai_t*ret){
    const use_context uc(&d, ctx, "rejected-nssai", 0);
    while(d.length> 0 ){
        rejected_nssai_t::nssai_t n = {};
        auto                      l = mask_u8(d.uint8(false), 0xf0u);
        de_uint8(d, ctx, &n.cause, 0x0fu).step(d);
        de_uint8(d, ctx, &n.sst).step(d);
        if (l>2){
            n.sd.present = true;
            de_octet(d.slice(l-2), ctx, &n.sd.v).step(d);
        }
        ret->nssais.push_back(n);
    }
    return {uc.length};
}

result_t die_sor_transparent_container(dissector d, context* ctx, sor_transparent_container_t*ret){
    const use_context uc(&d, ctx, "sor-transparent-container", 0);
    de_uint8(d, ctx, &ret->header.sor_data_type, 0x01u);
    de_uint8(d, ctx, &ret->header.list_ind, 0x02u);
    de_uint8(d, ctx, &ret->header.list_type, 0x04u);
    de_uint8(d, ctx, &ret->header.ack, 0x08u).step(d);

    de_fixed(d, ctx, ret->maci).step(d);
    if (ret->header.sor_data_type == 1){
        return {uc.length};
    }
    de_uint16(d, ctx, &ret->counter).step(d);

    if (ret->header.list_type == 1) {
        ret->access_technology = std::make_shared< std::vector< sor_transparent_container_t::plmn_id_t > >();
        for (auto i = ret->counter; i > 0; --i) {
            sor_transparent_container_t::plmn_id_t v = {};
            de_fixed(d, ctx, v.id).step(d);
            de_uint16(d, ctx, &v.access_technology_id).step(d);
            ret->access_technology->push_back(v);
        }
        return {uc.length};
    }

    ret->packet = std::make_shared< octet_t >();
    de_octet(d, ctx, ret->packet.get()).step(d);

    return {uc.length};
}

result_t die_timezone_time(dissector d, context*ctx, time_zone_time_t*ret){
    auto year = d.uint8(true);
    auto month = d.uint8(true);
    auto day   = d.uint8(true);
    auto hour  = d.uint8(true);
    auto minute = d.uint8(true);
    auto second = d.uint8(true);
    auto tz = d.uint8(true);

    ret->year = mask_u8(year, 0x0fu) * 10 + mask_u8(year, 0xf0u) + 2000;
    ret->month = mask_u8(month, 0x0fu) * 10 + mask_u8(month, 0xf0u);
    ret->mday   = mask_u8(day, 0x0fu) * 10 + mask_u8(day, 0xf0u);
    ret->hour  = mask_u8(hour, 0x0fu) * 10 + mask_u8(hour, 0xf0u);
    ret->minute = mask_u8(minute, 0x0fu) * 10 + mask_u8(minute, 0xf0u);
    ret->second = mask_u8(second, 0x0fu) * 10 + mask_u8(second, 0xf0u);

    ret->gmt = mask_u8(tz , 0x07u) * 10 + mask_u8(tz , 0xf0u);
    if (tz & 0x08u) ret->gmt = -ret->gmt;
    return {7};
}

