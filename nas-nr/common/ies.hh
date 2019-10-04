#pragma once
#include <cstdint>
#include <vector>

#include "ber.hh"
#include "definitions.hh"

/*
9.11.2.1A	DNN
8	7	6	5	4	3	2	1
DNN IEI	octet 1
Length of DNN contents	octet 2
DNN value	octet 3  octet n
*/
using dnn_t = octet_t;

/*
9.11.2.2	EAP message
8	7	6	5	4	3	2	1
EAP message IEI	octet 1
Length of EAP message contents	octet 2  octet 3
EAP message	octet 4  octet n
*/
using eap_t = octet_t;

/*
9.11.2.6	Intra N1 mode NAS transparent container
8	7	6	5	4	3	2	1
Intra N1 mode NAS transparent container IEI	octet 1
Length of Intra N1 mode NAS transparent container contents	octet 2
Message authentication code	octet 3  octet 6
Type of ciphering algorithm	Type of integrity protection algorithm	octet 7
0	0 Spare	0	KACF	TSC	Key set identifier in 5G	octet 8
Sequence number	octet 9
*/
struct intra_n1_mode_container_t {
    octet_4 auth_code;      // Message authentication code	octet 3-6
    bit_4   integrity_algo; // Type of integrity protection algorithm	octet 7
    bit_4   ciphering_algo; // Type of ciphering algorithm
    bit_3   nksi;           // TSC	Key set identifier in 5G	octet 8
    bit_1   tsc;            // TSC
    bit_1   kacf;           // KACF
    uint8_t seq_no;         // Sequence number	octet 9
};

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
    de_nibble(d, ctx, ret->integrity_algo);
    de_nibble(d, ctx, ret->ciphering_algo, 0xf0u).step(d);

    // 0	0 Spare	0	KACF	TSC	Key set identifier in 5G	octet 8
    de_nibble(d, ctx, &ret->kacf, 0x10u);
    de_nibble(d, ctx, &ret->tsc, 0x10u);
    de_nibble(d, ctx, &ret->nksi, 0x07u).step(d);

    // Sequence number	octet 9
    de_uint8(d, ctx, &ret->seq_no).step(d);

    return {uc.consumed()};
}

/*
9.11.2.7	N1 mode to S1 mode NAS transparent container
8	7	6	5	4	3	2	1
N1 mode to S1 mode NAS transparent container IEI	octet 1
Sequence number	octet 2
*/
struct n1_mode_to_s1_mode_container_t {
    uint8_t seq_no; // Sequence number	octet 2
};

// 9.11.2.7	N1 mode to S1 mode NAS transparent container
result_t die_n1_mode_to_s1_mode_container(dissector                       d,
                                          context*                        ctx,
                                          n1_mode_to_s1_mode_container_t* ret) {
    const use_context uc(&d, ctx, "n1-mode-to-s1-mode-container", 0);

    de_uint8(d, ctx, &ret->seq_no).step(d);
    return {uc.consumed()};
}

/*
9.11.2.8	S-NSSAI
8	7	6	5	4	3	2	1
S-NSSAI IEI	octet 1
Length of S-NSSAI contents	octet 2
SST	octet 3
SD	octet 4*  octet 6*
Mapped HPLMN SST	octet 7*
Mapped HPLMN SD	octet 8*  octet 10*
*/
struct s_nssai_t {
    uint8_t          sst              = {}; // SST	octet 3
    opt_t< octet_3 > sd               = {}; // SD	octet 4-6*
    opt_t< uint8_t > mapped_hplmn_sst = {}; // Mapped HPLMN SST	octet 7*
    opt_t< octet_3 > mapped_hplmn_sd  = {}; // Mapped HPLMN SD	octet 8-10*
};

//    9.11.2.8	S-NSSAI
result die_s_nssai(dissector d, context* ctx, s_nssai_t* ret) {
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
        de_fixed(d, ctx, &ret->sd.v).step(d);
    }
    if (len >= 0x05) { // sst, sd and mapped hplmn sst
        ret->mapped_hplmn_sst.present = true;
        de_uint8(d, ctx, &ret->mapped_hplmn_sst.v).step(d);
    }
    if (len == 0x08) { // sst, sd, mapped hplmn sst and hplmn sd
        ret->mapped_hplmn_sd.present = true;
        de_fixed(d, ctx, &ret->mapped_hplmn_sd.v).step(d);
    }
    return {uc.consumed()};
}

/* 9.11.2.9
8	7	6	5	4	3	2	1
S1 mode to N1 mode NAS transparent container IEI	octet 1
Length of S1 mode to N1 mode NAS transparent container contents	octet 2
Message authentication code	octet 3  octet 6
Type of ciphering algorithm	Type of integrity protection algorithm	octet 7	0 Spare
NCC	TSC	Key set identifier in 5G	octet 8
0 Spare	octet 9  octet 10
0 Spare
*/
struct s1_mode_to_n1_mode_container_t {
    octet_4 auth_code      = {}; // Message authentication code	octet 3-6
    bit_4   integrity_algo = {}; // Type of integrity protection algorithm	octet 7
    bit_4   ciphering_algo = {}; // Type of ciphering algorithm
    bit_3   nksi           = {}; // Key set identifier in 5G	octet 8
    bit_1   tsc            = {}; // TSC
    bit_3   ncc            = {}; // NCC
    uint8_t spare_9        = {}; // octet 9
    uint8_t spare_a        = {};
};

// 9.11.2.9
result_t die_s1_mode_to_n1_mode_containers(dissector                       d,
                                           context*                        ctx,
                                           s1_mode_to_n1_mode_container_t* ret) {
    const use_context uc(&d, ctx, "s1-mode-to-n1-mode-container", 2);

    de_fixed(d, ctx, &ret->auth_code).step(d);

    de_nibble(d, ctx, &ret->integrity_algo, 0x0f);
    de_nibble(d, ctx, &ret->ciphering_algo, 0xf0u).step(d);

    de_nibble(d, ctx, &ret->nksi, 0x07u);
    de_nibble(d, ctx, &ret->tsc, 0x04);
    de_nibble(d, ctx, &0x70u).step(d);

    return {uc.length};
}

/*
9.11.3.1	5GMM capability
8	7	6	5	4	3	2	1
5GMM capability IEI	octet 1
Length of 5GMM capability contents	octet 2	SGC
5G-HC-CP CIoT	N3 data	5G-CP CIoT	RestrictEC	LPP	HO attach	S1 mode	octet 3
0 Spare	5G-UP CIoT	5GSRVCC	octet 4*
0	octet 5*-15*
Spare	0
*/
struct nmm_capability_t {
    bool  oct4_present = false;
    bit_1 s1_mode      = {}; // S1 modeoctet 3
    bit_1 ho_attach    = {}; // HO attach
    bit_1 lpp          = {}; // LPP
    bit_1 restrict_ec  = {}; // RestrictEC
    bit_1 ncp_ciot     = {}; // 5G-CP CIoT
    bit_1 n3data       = {}; // N3 data
    bit_1 nhccp_ciot   = {}; // 5G-HC-CP CIoT
    bit_1 sgc          = {}; // SGC
    bit_1 nsrvcc       = {}; // 5GSRVCC	octet 4*
    bit_1 nup_ciot     = {}; // 5G-UP CIoT
};

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

/*
9.11.3.2	5GMM cause
8	7	6	5	4	3	2	1
5GMM cause IEI	octet 1
Cause value	octet 2
*/
using nmm_cause_t = uint8_t;

/*
9.11.3.2A	5GS DRX parameters
8	7	6	5	4	3	2	1
5GS DRX parameters IEI	octet 1
Length of 5GS DRX parameters contents	octet 2
0	DRX value
spare	DRX value	octet 3
*/
using drx_parameters = bit_4;

/* 9.11.3.3 5GS identity type
8	7	6	5	4	3	2
5GS identity type IEI	0 spare	Type of identity
*/
using nid_type_t = bit_3;

struct mcc_mnc_t {
    uint16_t mcc; //
    uint16_t mnc; //
};

result_t die_mcc_mnc(dissector d, context* ctx, mcc_mnc_t*ret){
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

/*
9.11.3.4	5GS mobile identity
Figure 9.11.3.4.1: 5GS mobile identity information element for type of identity "5G-GUTI"
8	7	6	5	4	3	2	1
5GS mobile identity IEI	octet 1
Length of 5GS mobile identity contents	octet2  octet 3
1	0 spare	Type of identity	octet 4
MCC digit 2	MCC digit 1	octet 5
MNC digit 3	MCC digit 3	octet 6
MNC digit 2	MNC digit 1	octet 7
AMF Region ID	octet 8
AMF Set ID	octet 9
AMF Set ID (continued)	AMF Pointer	octet 10
5G-TMSI	octet 11
5G-TMSI (continued)	octet 12
5G-TMSI (continued)	octet 13
5G-TMSI (continued)	octet 14
*/

struct guti_nmid_t {
    bit_3     type          = {}; // octet 4
    mcc_mnc_t mccmnc        = {}; // octet 5-7
    uint8_t   amf_region_id = {}; // octet 8
    bit_a     amf_set_id    = {}; // octet 9
    bit_6     amf_pointer   = {}; // octet 10
    octet_4   tmsi          = {}; // octet 11-14
};

result_t die_guti_nmid(dissector d, context* ctx, guti_nmid_t*ret){
    const use_context uc(&d, ctx, "guti-nr-mobile-id", 0);

    de_uint8(d, ctx, &ret->type, 0x07).step(d);
    die_mcc_mnc(d, ctx, &ret->mccmnc).step(d);

    ret->amf_region_id = d.uint8(true);
    ret->amf_set_id    = mask_u16(d.uint16(false), 0xffc0u);
    ret->amf_pointer   = mask_u8(d.uint8(true, skip = 1), 0x3f);

    de_fixed(d, ctx, &ret->tmsi).step(d);

    return {uc.consumed()};
}

/*
Figure 9.11.3.4.2: 5GS mobile identity information element for type of identity or "IMEI"
or "IMEISV"
8	7	6	5	4	3	2	1
5GS mobile identity IEI	octet 1
Length of 5GS mobile identity contents	octet 2  octet 3
Identity digit 1	odd/ even indic	Type of identity	octet 4
Identity digit p+1	Identity digit p	octet 5*
*/
struct imeisv_nmid_t {
    bit_3                type;    // Type of identity	octet 4
    bit_1                odd_ind; // odd/ even indic
    std::string          digits; // octet 5*
};

using imei_nmid_t = imeisv_nmid_t;

result_t die_imeisv_nmid(dissector d, context* ctx, imeisv_nmid_t*ret){
    const use_context uc(&d, ctx, "imeisv-nr-mobile-id", 0);

    static const char bcds[] = "0123456789????\0";
    ret->type                = umask_u8(d.uint8(false), 0x07);
    ret->odd_ind = mask_u8(d.uint8(false) , 0x08);
    ret->digits.push_back(bcds[mask_u8(d.uint8(true), 0xf0u)]);
    while(d.length>0){
        auto i = d.uint8(true);
        ret->digits.push_back(bcds[mask_u8(i, 0x0fu)]);
        ret->digits.push_back(bcds[mask_u8(i, 0xf0u)]);
    }

    return {uc.consumed()};
}

/*
Figure 9.11.3.4.3: 5GS mobile identity information element for type of identity "SUCI" and
SUPI format "IMSI"
8	7	6	5	4	3	2	1 5GS mobile identity IEI	octet 1 Length of 5GS
mobile identity contents	octet 2  octet 3 0 spare	SUPI format	0 spare	Type of
identity	octet 4 MCC digit 2	MCC digit 1	octet 5 MNC digit 3	MCC digit 3	octet 6 MNC
digit 2	MNC digit 1	octet 7 Routing indicator digit 2	Routing indicator digit 1 octet 8
Routing indicator digit 4	Routing indicator digit 3	octet 9
0 Spare	Protection scheme Id	octet 10
Home network public key identifier	octet 11
Scheme output	octet 12 - x

*/

/*
Figure 9.11.3.4.3a: Scheme output for type of identity "SUCI", SUPI format "IMSI" and
Protection scheme Id "Null scheme"
8	7	6	5	4	3	2	1 MSIN digit 2	MSIN digit 1	octet 12 …
MSIN digit n+1	MSIN digit n	octet x

*/

/*
Figure 9.11.3.4.4: 5GS mobile identity information element for type of identity "SUCI" and
SUPI format "Network specific identifier"

8	7	6	5	4	3	2	1 5GS mobile identity IEI
octet 1 Length of 5GS mobile identity contents	octet 2  octet 3 0 Spare	SUPI format	0
Spare	Type of identity	octet 4 SUCI NAI	octet 5 - y

*/

struct suci_nmid_t {
    struct imsi_t {
        bit_3                                   type;        // Type of identity	octet 4
        bit_3                                   supi_format; //
        mcc_mnc_t                               mccmnc;      //
        octet_2                                 routing_indicator;          //
        bit_4                                   protection_scheme_id;       //
        uint8_t                                 home_network_public_key_id; //
        std::shared_ptr< octet_t >              scheme_output;              //
        std::shared_ptr< std::vector< bit_4 > > msin;                       // null scheme
    };
    struct nai_t {
        bit_3   type;        //
        bit_3   supi_format; //
        octet_t suci_nai;    //
    };

    bit_3                           supi_format = {}; //
    std::shared_ptr< nai_t > nai         = {}; // supi_format = 000
    std::shared_ptr< imsi_t > imsi        = {}; // supi_format = 001
};
using suci_imsi_nmid_t = suci_nmid_t::imsi_t;
using suci_nai_nmid_t = suci_nmid_t::nai_t;

result_t die_suci_nai_nmid(dissector d, context* ctx, suci_nmid_t::nai_t*ret){
    const use_context uc(&d, ctx, "suci-nmid-nai", 0);

    de_uint8(d, ctx, &ret->type, 0x07);
    de_uint8(d, ctx, &ret->supi_format, 0x70u).step(d);
    de_octet(d, ctx, &ret->suci_nai).step(d);

    return {uc.consumed()};
}
result die_suci_imsi_nmid(dissector d, context, suci_nmid_t::imsi_t*ret){
    const use_context uc(&d, ctx, "suci-nmid-imsi", 0);

    de_uint8(d, ctx, &ret->type, 0x07);
    de_uint8(d, ctx, &ret->supi_format, 0x70u).step(d);
    die_mcc_mnc(d, ctx, &ret->mccmnc).step(d);
    de_fixed(d, ctx, &ret->routing_indicator).step(d);
    de_nibble(d, ctx, &ret->protection_scheme_id).step(d);
    de_uint8(d, ctx, &ret->home_network_public_key_id).step(d);

    if (ret->protection_scheme_id == 0){ // null scheme
        ret->msin = std::make_shared< std::vector< bit_4 > >();
        while (d.length > 0) {
            auto a = d.uint8(true);
            ret->msin->push_back(mask_u8(a, 0x0fu));
            ret->msin->push_back(mask_u8(a, 0xf0u));
        }
    }else{
        ret->scheme_output = std::move(octet_t(d.safe_ptr(), d.safe_ptr() + d.length));
        d.step(d.length);
    }
    return {uc.consumed()};
}

result_t die_suci_nmid(dissector d, context* ctx, suci_nmid_t*ret){
    const use_context uc(&d, ctx, "suci-nr-mobile-id", 0);
    ret->supi_format = mask_u8(d.uint8(false), 0x70u);
    if (ret->supi_format == 0) { // imsi
        ret->imsi = std::make_shared< imsi_t >();
        die_suci_imsi_nmid(d, ctx, ret->imsi.get()).step(d);
    }
    if (ret->supi_format == 1) { // network specific identifier
        ret->nai = std::make_shared< suci_nai_nmid_t >();
        die_suci_nai_nmid(d, ctx, ret->nai.get()).step(d);
    }
    return {uc.consumed()};
}

/*
Figure 9.11.3.4.5: 5GS mobile identity information element for type of identity
"5G-S-TMSI"

8	7	6	5	4	3	2	1 5GS mobile identity
IEI	octet 1 Length of 5GS mobile identity contents	octet 2  octet 3 1	0 spare	Type of
identity	octet 4 AMF Set ID	octet 5 AMF Set ID (continued)	AMF Pointer	octet 6
5G-TMSI	octet 7
5G-TMSI (continued)	octet 8
5G-TMSI (continued)	octet 9
5G-TMSI (continued)	octet 10

*/
struct s_tmsi_nmid_t {
    bit_3   type        = {}; //
    bit_a   amf_set_id  = {}; //
    bit_6   amf_pointer = {}; //
    octet_4 tmsi        = {}; //
};

result_t die_s_tmsi_nmi(dissector d, context* ctx, s_tmsi_nmid_t*ret){
    const use_context uc(&d, ctx, "s-tmsi-nr-mobile-id", 0);

    ret->type = mask_u8(d.uint8(true), 0x07u);
    ret->amf_set_id = mask_u16(d.uint16(false), 0xffc0u);
    ret->amf_pointer = mask_u8(d.uint8(true, 1), 0x3fu);
    de_fixed(d, ctx, &ret->tmsi).step(d);

    return {uc.consumed()};
}

/*
Figure 9.11.3.4.6: 5GS mobile identity information element for type of identity "No
identity"
8	7	6	5	4	3	2	1 5GS mobile identity IEI	octet 1 Length of 5GS
mobile identity contents	octet 2  octet 3 0	Type of identity	octet 4 spare	Type
of identity	octet 4

*/
struct noid_nmid_t {
    bit_3 type = {}; //
};

result_t die_noid_nmid(dissector d, context* ctx, noid_nmid_t*ret){
    ret->type = mask_u8(d.uint8(true), 0x07u);
    return {1};
}

/* MAC address
8	7	6	5	4	3	2	1 5GS mobile identity IEI	octet 1 Length of 5GS
mobile identity contents	octet 2  octet 3 0 spare	Type of identity	octet 4 MAC
address	octet 5  octet 10
*/
struct mac_nmid_t {
    bit_3   type = {}; //
    octet_6 mac  = {}; //
};

result_t die_mac_nmid(dissector d, context* ctx, mac_nmid_t*ret){
    ret->type = mask_u8(d.uint8(true), 0x07u);
    de_fixed(d, ctx, ret->mac).step(d);

    return {7};
}

struct nmid_t {
    bit_3                            type;  //
    std::shared_ptr< guti_nmid_t >   guti;  //
    std::shared_ptr< imeisv_nmid_t > imei;  //
    std::shared_ptr< suci_nmid_t >   suci;  //
    std::shared_ptr< stmsi_nmid_t >  stmsi; //
    std::shared_ptr< noid_nmid_t >   noid;  //
    std::shared_ptr< mac_nmid_t >    mac;   //
};
using nmobile_id_t = nmid_t;

result_t die_nmid(dissector d, context* ctx, nmid_t*ret){
    ret->type = d.uint8(false)& 0x07u;
    switch (ret->type) {
    case 0: // no id
        ret->noid = std::make_shared<noid_nmid_t>();
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
        ret->stmsi=std::make_shared< stmsi_nmid_t >();
        return die_s_tmsi_nmi(d, ctx, ret->stmsi.get());
    case 5: // imeisv
        ret->imei = std::make_shared< imei_nmid_t >();
        return die_imeisv_nmid(d, ctx, ret->imei.get());
    case 6: // mac
        ret->mac = std::make_shared< mac_nmid_t >();
        return die_mac_nmid(d, ctx, ret->mac.get());
    }
    return {d.length};
}

/*
9.11.3.5	5GS network feature support
8	7	6	5	4	3	2
5GS network feature support IEI
Length of 5GS network feature support contents
MPSI	IWK N26	EMF	EMC	IMS- VoPS-N3GPP	IMS- VoPS-3GPP
0 Spare	5G-UP CIoT	5G-HC-CP CIoT	N3 data	5G-CP CIoT	RestrictEC	MCSI	EMCN3

Spare
*/
// 9.11.3.5	5GS network feature support
struct nr_network_feature_support_t {
    bit_1 ims_vops_3gpp  = {}; //
    bit_1 ims_vops_n3gpp = {}; //
    bit_2 emc            = {}; //
    bit_2 emf            = {}; //
    bit_1 iwk_n26        = {}; //
    bit_1 mpsi           = {}; //
    bit_1 emcn3          = {}; //
    bit_1 mcsi           = {}; //
    bit_1 restrict_ec    = {}; //
    bit_1 ncp_ciot       = {}; //
    bit_1 n3data         = {}; //
    bit_1 nhc_cp_ciot    = {}; //
    bit_1 nup_ciot       = {}; //
    uint8_t spare          = {};
};

result_t die_nr_network_feature_support(dissector d, context* ctx, nr_network_feature_support_t*ret){
    const use_context uc(&d, ctx, "nr-network-feature-support", 1);
    auto              o3 = d.uint8(true), o4 = d.uint8(true);

    ret->ims_vops_3gpp = mask_u8(o3, 0x01);
    ret->ims_vops_n3gpp       = mask_u8(o3, 0x02);
    ret->emc = mask_u8(o3, 0x0c);

    ret->emf                  = mask_u8(o3, 0x30u);
    ret->iwk_n26              = mask_u8(o3, 0x40u);
    ret->mpsi                 = mask_u8(o3, 0x80u);

    ret->emcn3 = mask_u8(o4, 0x01);
    ret->mcsi  = mask_u8(o4, 0x02);
    ret->restrict_ec = mask_u8(o4, 0x04);
    ret->ncp_ciot    = mask_u8(o4, 0x08);

    ret->n3data = mask_u8(o4, 0x10);
    ret->nhc_cp_ciot = mask_u8(o4, 0x20);
    ret->nup_ciot    = mask_u8(o4, 0x40);

    return {uc.length};
}

/* 9.11.3.6 5GS registration result
8	7	6	5	4	3	2	1
5GS registration result IEI	octet 1
Length of 5GS registration result contents	octet 2
0 Spare	SMS allowed	5GS registration result value
*/
struct nr_registration_result_t {
    bit_3 result      = {}; //
    bit_1 sms_allowed = {}; //
};

/* 9.11.3.7 5GS registration type
8	7	6	5	4	3	2	1
5GS registration type IEI	FOR	5GS registration type value	octet 1
*/
using nregistration_type_t = bit_3;

/* 9.11.3.8 5GS tracking area identity
8	7	6	5	4	3	2	1
5GS tracking area identity IEI	octet 1
MCC digit 2	MCC digit 1	octet 2
MNC digit 3	MCC digit 3	octet 3
MNC digit 2	MNC digit 1	octet 4
TAC	octet 5
TAC (continued)	octet 6
TAC (continued)	octet 7
*/
struct nr_tracking_area_id_t {
    mcc_mnc_t mccmnc = {}; //
    octet_3   tac     = {}; //
};

result_t die_nr_tracking_area_id(dissector d, context* ctx, nr_tracking_area_id_t*ret){

    die_mcc_mnc(d, ctx, ret->mccmnc).step(d);
    de_fixed(d, ctx, ret->tac).step(d);

    return {6};
}

struct partial_tai_list_00_t {
    bit_5                  number = {}; // +1
    bit_2                  type   = {}; // 00
    mcc_mnc_t              mccmnc = {}; //
    std::vector< octet_3 > taces    = {}; //
};

result_t die_partial_tai_list_00(dissector d, context* ctx, partial_tai_list_00_t*ret){
    const use_context uc(&d, ctx, "partial-tai-id", 0);

    de_uint8(d, ctx, &ret->number, 0x1fu);
    de_uint8(d, ctx, &ret->type, 0x60u).step(d);

    die_mcc_mnc(d, ctx, &ret->mccmnc).step(d);

    for (auto n = ret->number; n > 0;) {
        octet_3 o3 = {};
        de_fixed(d, ctx, o3).step(d);
        ret->taces.push_back(o3);
        --n;
    }
    return {uc.consumed()};
}

struct partial_tai_list_01_t {
    bit_5     number = {}; // +1
    bit_2     type   = {}; // 01
    mcc_mnc_t mccmnc = {}; //
    octet_3   tac    = {}; //
    std::vector< octet_3 > others = {};
};

result_t die_partial_tai_list_01(dissector d, context* ctx, partial_tai_list_01_t* ret) {
    const use_context uc(&d, ctx, "partial-tai-id", 0);

    de_uint8(d, ctx, &ret->number, 0x1fu);
    de_uint8(d, ctx, &ret->type, 0x60u).step(d);

    die_mcc_mnc(d, ctx, &ret->mccmnc).step(d);
    de_fixed(d, ctx, ret->tac).step(d);

    for (auto n = ret->number; n > 1; --n) {
        octet_3 o3 = {};
        de_fixed(d, ctx, o3).step(d);
        ret->others.push_back(o3);
    }

    return {uc.consumed()};
}

struct partial_tai_list_10_t {
    bit_5                              number; // +1
    bit_2                              type;   // 01
    std::vector< nr_tracking_area_id_t > ids;    //
};

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

struct partial_tai_t {
    bit_2 type;
    std::shared_ptr< partial_tai_list_00_t > l00;
    std::shared_ptr< partial_tai_list_01_t > l01;
    std::shared_ptr< partial_tai_list_10_t > l10;
};
/* 9.11.3.9 5GS tracking area identity list
8	7	6	5	4	3	2	1
5GS tracking area identity list IEI	octet 1
Length of 5GS tracking area identity list contents	octet 2
Partial tracking area identity list 1	octet 3  octet i
Partial tracking area identity list 2	octet i+1*  octet l*
…	octet l+1*  octet m*
Partial tracking area identity list p	octet m+1*  octet n*
*/
struct nr_tracking_area_id_list_t {
    std::vector< partial_tai_t > partials; //
};

result_t die_nr_tracking_id_list(dissector d, context* ctx, nr_tracking_area_id_t*ret){
    const use_context uc(&d, ctx, "nr-tracking-area-id-list", 0);

    return {uc.consumed()};
}


/*
9.11.3.9A	5GS update type
*/
struct nr_update_type_t {
    bit_1 sms_requested = {}; //
    bit_1 nran_rcu      = {}; //
    bit_2 pnb_ciot      = {}; //
};

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

/*
9.11.3.10	ABBA
8	7	6	5	4	3	2	1
ABBA IEI	octet 1
Length of ABBA contents	octet 2
ABBA contents	octet 3  octet n
*/
using abba_t = octet_t;

/*
9.11.3.11	Access type
8	7	6	5	4	3	2	1
Access type IEI	0 spare	Access type	octet 1
*/
using access_type_t = bit_2;

/*
9.11.3.12	Additional 5G security information
8	7	6	5	4	3	2	1
Additional 5G security parameters IEI	octet 1
Length of Additional 5G security parameters contents	octet 2
0 Spare	RINMR	HDP
*/
struct additional_nr_security_information_t {
    bit_1 hdp;   //
    bit_1 rinmr; //
};

result_t die_additional_nr_security_infomation(
    dissector                             d,
    context*                              ctx,
    additional_nr_security_information_t* ret) {

    de_uint8(d, ctx, &ret->hdp, 0x01);
    de_uint8(d, ctx, &ret->rinmr, 0x02).step(d);

    return {1};
}

/*
9.11.3.13	Allowed PDU session status
8	7	6	5	4	3	2	1
Allowed PDU session status IEI	octet 1
Length of Allowed PDU session status contents	octet 2
PSI (7)	PSI (6)	PSI (5)	PSI (4)	PSI (3)	PSI (2)	PSI (1)	PSI (0)	octet 3
PSI (15)	PSI (14)	PSI (13)	PSI (12)	PSI (11)	PSI (10)	PSI (9)	PSI (8)
octet 4
0
Spare	octet 5* -34*
*/
using allowed_pdu_session_status_t = octet_2;

// 9.11.3.14 Authentication failure parameter
// 10.5.3.2.2 in TS 24.008 g10
using authentication_parameter_failure_t = uint8_t[14];

// 9.11.3.15 Authentication parameter AUTN
// 10.5.3.1.1
using authentication_parameter_autn_t = octet_g;

// 9.11.3.16 Authentication parameter RAND
// 10.5.3.1 in TS 24.008

using authentication_parameter_rand_t = octet_g;

// 9.11.3.17 Authentication response parameter
// 9.9.3.4 in TS 24.301 g11
using authentication_response_parameter_t = octet_t;

/*
9.11.3.18	Configuration update indication
8	7	6	5	4	3	2	1
Configuration update indication IEI	0 Spare	RED	ACK	octet 1
*/
struct configuration_update_indication_t {
    bit_1 ack; //
    bit_1 red; //
};

result_t die_configuration_update_indication(
    dissector                             d,
    context*                              ctx,
    configuration_update_indication_t* ret) {
    de_uint8(d, ctx, &ret->ack, 0x01);
    de_uint8(d, ctx, &ret->red, 0x02).step(d);

    return {1};
}

// 9.11.3.19 Daylight saving time
// 10.5.3.12 in TS 24.008 g10
using daylight_saving_time_t = bit_2;

/*
9.11.3.20	De-registration type
8	7	6	5	4	3	2	1
De-registration type IEI	Switch off	Re-registration required	Access type	octet 1
*/
struct deregistration_type_t {
    bit_2 access_type;             //
    bit_1 reregistration_required; //
    bit_1 switch_off;              //
};

result_t die_deregistration_type(dissector                          d,
                                             context*                           ctx,
                                             deregistration_type_t* ret) {
    de_uint8(d, ctx, &ret->access_type, 0x03);
    de_uint8(d, ctx, &ret->reregistration_required, 0x04);
    de_uint8(d, ctx, reg->switch, 0x08).step(d);

    return {1};
}

// 9.11.3.21 void
// 9.11.9.22 void

// 9.11.3.23 Emergency number list
// 10.5.3.13 in TS 24.008 g10
struct emergency_number_list_t {
    struct number_t {
        bit_5                service_category; //
        std::vector< bit_4 > digits;           //
    };

    std::vector< number_t > numbers; //
};

result_t die_number(dissector d, context* ctx, number_t*ret){
    static char bcds[] = "0123456789????\0";
    auto        len    = d.length;
    de_uint8(d, ctx, &ret->service_category).step(d);
    while(d.length>0){
        auto o = d.uint8(true);
        ret->digits.push_back(bcds[mask_u8(o, 0x0f)]);
        ret->digits.push_back(bcds[mask_u8(0, 0xf0u)]);
    }
    return {len};
}
result_t die_emergency_number_list(dissector d, context* ctx, emergency_number_list* ret) {
    const use_context uc(&d, ctx, "emergency-number-list", 0);
    while(d.length>0){
        auto len = d.uint8(true);
        number_t n   = {};
        die_number(d.slice(len), ctx, &n).step(d);
        ret->numbers.push_back(n);
    }
    return {uc.length};
}
/*
9.11.3.24	EPS NAS message container
8	7	6	5	4	3	2	1
EPS NAS message container IEI	octet 1
Length of EPS NAS message container contents	octet 2  octet 3
EPS NAS message container	octet 4  octet n
*/
using eps_nas_message_t = octet_t;

// 9.11.3.25 EPS NAS security algorithms
// 9.9.3.23 in TS 24.301 g11
struct eps_nas_security_algorighms_t {
    bit_3 integirty_algo; //
    bit_1 spare_1;        //
    bit_3 ciphering_algo; //
    bit_1 spare_2;        //
};

// 9.11.3.26 Extended emergency number list
// 9.9.3.37A in TS 24.301 g11
struct extened_emergency_number_list_t {
    struct number_t {
        std::vector< number_t > digits;               //
        uint8_t                 sub_services_present; //
        octet_t                 sub_service_field;    //
    };

    bit_1 eenlv; //
};

// 9.11.3.27 void

// 9.11.3.28 imeisv request
// 10.5.5.10 in TS 24.008 g10
using imeisv_request_t = bit_3;

/*
9.11.3.29	LADN indication
8	7	6	5	4	3	2	1
LADN indication IEI	octet 1
Length of LADN indication contents	octet 2 octet 3
LADN DNN value 1	octet 4*  octet a*
LADN DNN value 2	octet a+1*  octet b*
…	octet b+1*  octet g*
LADN DNN value n	octet g+1*  octet h*
*/
struct ladn_indication_t {
    std::vector< dnn_t > dnn; //
};

/*
9.11.3.30	LADN information
8	7	6	5	4	3	2	1
LADN information IEI	octet 1
Length of LADN information contents	octet 2 octet 3
LADN 1	octet 4  octet a
LADN 2	octet a+1*  octet b*
…	octet b+1*  octet g*
LADN n	octet g+1*  octet h*
*/
struct ladn_information_t {
    struct ladn_t {
        dnn_t                    dnn;  //
        ntracking_area_id_list_t ntai; //
    };
    std::vector< ladn_t > ladn; //
};
/*
Figure 9.11.3.30.1: LADN information information element
8	7	6	5	4	3	2	1
Length of DNN value	octet 4
DNN value	octet 5  octet m
5GS tracking area identity list	octet m+1  octet a
*/

/*
9.11.3.31	MICO indication
8	7	6	5	4	3	2	1
MICO indication IEI	0 Spare	SPRTI	RAAI	octet 1
*/
struct mico_indication_t {
    bit_1 raai;  //
    bit_1 sprti; //
};

/*
9.11.3.32	NAS key set identifier
8	7	6	5	4	3	2	1
NAS key set identifier IEI	TSC	NAS key set identifier	octet 1
*/
struct nas_key_set_identifier_t {
    bit_3 nksi; //
    bit_1 tsc;  //
};

struct nas_message_t;
/*
9.11.3.33	NAS message container
8	7	6	5	4	3	2	1
NAS message container IEI	octet 1
Length of NAS message container contents	octet 2
octet 3
octet 4
NAS message container contents
octet n
*/
using nas_message_container_t = nas_message_t;

/*
9.11.3.34	NAS security algorithms
8	7	6	5	4	3	2	1
NAS security algorithms IEI	octet 1
Type of ciphering algorithm	Type of integrity protection algorithm	octet 2
*/
struct nas_security_algorithm_t {
    bit_4 integrity_algo; //
    bit_4 ciphering_algo; //
};

// 9.11.3.35 Network name
// 10.5.3.5a in TS 24.008 g10
struct network_name_t {
    bit_3   unused_bits;   //
    bit_1   add_ci;        //
    bit_3   coding_scheme; //
    bit_1   ext;           //
    octet_t text;          //
};

/*
9.11.3.36	Network slicing indication
8	7	6	5	4	3	2	1
Network slicing indication IEI	0 Spare	DCNI	NSSCI	octet 1
*/
struct network_slicing_indication_t {
    bit_1 nssci; //
    bit_1 dcni;  //
};

/*
9.11.3.37	NSSAI
8	7	6	5	4	3	2	1
NSSAI IEI	octet 1
Length of NSSAI contents	octet 2
S-NSSAI value 1	octet 3  octet m
S-NSSAI value 2	octet m+1*  octet n*
…	octet n+1*  octet u*
S-NSSAI value n	octet u+1*  octet v*
*/
struct nssai_t {
    std::vector< s_nssai_t > s_nssai; //
};

/*
9.11.3.37A	NSSAI inclusion mode
8	7	6	5	4	3	2	1
NSSAI inclusion mode IEI	0 spare	NSSAI inclusion mode	octet 1
*/
using nssai_includion_mode_t = bit_2;

/*
9.11.3.38	Operator-defined access category definitions
8	7	6	5	4	3	2	1
Operator-defined access category definitions IEI	octet 1
Length of operator-defined access category definitions contents	octet 2 octet 3
Operator-defined access category definition 1	octet 4  octet a
Operator-defined access category definition 2	octet a+1*  octet b*
…	octet b+1*  octet g*
Operator-defined access category definition 1 n	octet g+1*  octet h*

Figure 9.11.3.38.1: Operator-defined access category definitions information element
8	7	6	5	4	3	2	1
Length of operator-defined access category definition contents	octet 4
Precedence value	octet 5
PSAC	0 Spare	Operator-defined access category number	octet 6
Length of criteria	octet 7
Criteria	octet 8  octet a-1
0 Spare	Standardized access category	octet a*
*/
struct operator_defined_access_category_definition_t {
    uint8_t        precedence;                   //
    bit_5          number;                       //
    bit_2          spare;                        //
    bit_1          psac;                         //
    octet_t        criteria;                     //
    opt_t< bit_5 > standardized_access_category; //
};

/*
9.11.3.39	Payload container
8	7	6	5	4	3	2	1
Payload container IEI	octet 1
Length of payload container contents

octet 4
*/
using payload_container_t = octet_t;

struct payload_container_multiple_t {
    using optional_ie_t = octet_t;
    struct entry_t {
        bit_4 type; //
        // bit_4                       optional_ie_number;
        std::vector< optional_ie_t > optional_ies; //
        octet_t                      content;      //
    };

    // uint8_t number;
    std::vector< entry_t > entries; //
};

/*
Figure 9.11.3.39.1: Payload container information element
8	7	6	5	4	3	2	1
Number of entries	octet 4
Payload container entry 1	octet 5  octet x2
Payload container entry 2	octet x2+1  octet x3
……	…
Payload container entry i	octet xi +1  octet n

Figure 9.11.3.39.2: Payload container contents with Payload container type "Multiple
payloads" 8	7	6	5	4	3	2	1 Length of Payload container entry	octet xi +1 octet
xi +2 Number of optional IEs	Payload container type	octet xi +3 Optional IE 1	octet
xi +4  octet y2 Optional IE 2	octet y2+1  octet y3 … Optional IE j	octet yj+1  octet
z Payload container entry contents	octet z+1  octet n

Figure 9.11.3.39.3: Payload container entry
8	7	6	5	4	3	2	1
Type of optional IE	octet xi +4
Length of optional IE	octet xi +5
Value of optional IE	octet xi +6  octet y2
*/

/*
9.11.3.40	Payload container type
8	7	6	5	4	3	2	1
Payload container type IEI	Payload container type value
*/
using payload_container_type_t = bit_4;

/*
9.11.3.41	PDU session identity 2
8	7	6	5	4	3	2	1
PDU session identity 2 IEI	octet 1
PDU session identity 2 value	octet 2
*/
using pdu_session_identity_2_t = uint8_t;

/*
9.11.3.42	PDU session reactivation result
8	7	6	5	4	3	2	1
PDU session reactivation result IEI	octet 1
Length of PDU session reactivation result	octet 2
PSI (7)	PSI  (6)	PSI  (5)	PSI  (4)	PSI  (3)	PSI  (2)	PSI  (1)	PSI (0)
octet 3 PSI  (15)	PSI  (14)	PSI  (13)	PSI  (12)	PSI  (11)	PSI  (10)	PSI (9)
PSI  (8)	octet 4 octet 5* -34*
*/
struct pdu_session_reactivation_result_t {
    uint8_t psi_a; //
    uint8_t psi_b; //
};

/*
9.11.3.43	PDU session reactivation result error cause
8	7	6	5	4	3	2	1
PDU session reactivation result error cause IEI	octet 1
Length of PDU session reactivation result error cause	octet 2
octet 3
PDU session ID	octet 4
cause value	octet 5
….
PDU session ID	octet 514*
cause value	octet 515*
*/
struct pdu_session_reactivation_result_error_cause_t {
    struct cause_t {
        uint8_t pdu_session_id; //
        uint8_t cause;          //
    };
    std::vector< cause_t > cause; //
};

/*
9.11.3.44	PDU session status
8	7	6	5	4	3	2	1
PDU session status IEI	octet 1
Length of PDU session status contents	octet 2
PSI (7)	PSI (6)	PSI (5)	PSI (4)	PSI (3)	PSI (2)	PSI (1)	PSI (0)	octet 3
PSI (15)	PSI (14)	PSI (13)	PSI (12)	PSI (11)	PSI (10)	PSI (9)	PSI (8)
octet 4 0	octet 5*- spare	34*
*/
struct pdu_session_status_t {
    uint8_t psi_a; //
    uint8_t psi_b; //
};

// 9.11.3.45 PLMN list
// 10.5.1.13 in TS 24.008 g10
struct plmn_list_t {
    std::vector< mcc_mnc_t > plmns; //
};

/*
9.11.3.46	Rejected NSSAI
8	7	6	5	4	3	2	1
Rejected NSSAI IEI	octet 1
Length of Rejected NSSAI contents	octet 2
Rejected S-NSSAI 1	octet 3  octet m
Rejected S-NSSAI 2	octet m+1*  octet n*
…	octet n+1*  octet u*
Rejected S-NSSAI n	octet u+1*  octet v*

Figure 9.11.3.46.1: Rejected NSSAI information element
8	7	6	5	4	3	2	1
Length of rejected S-NSSAI	Cause value	octet 1
SST	octet 2
SD	octet 3*  octet 5*
*/
struct rejected_nssai_t {
    struct nssai_t {
        bit_4            cause = {}; //
        uint8_t          sst   = {}; //
        opt_t< uint8_t > sd    = {}; //
    };
    std::vector< nssai_t > nssai = {}; //
};

/*
9.11.3.47	Request type
8	7	6	5	4	3	2	1
Request type IEI	0 spare	Request type value	octet 1
*/
using request_type_t = bit_3;

// 9.11.3.48 S1 UE network capability
// 9.9.3.34 in TS 24.301 g11
struct s1_ue_network_capability_t {
    uint8_t eea;          //
    uint8_t eia;          //
    uint8_t uea_present;  //
    uint8_t uea;          //
    bit_7   uia;          //
    bit_1   ucs2;         //
    bit_1   nf;           // //
    bit_1   srvcc;        //
    bit_1   lcs;          //
    bit_1   lpp;          //
    bit_1   acc_csfb;     //
    bit_1   h245_ash;     //
    bit_1   prose;        //
    bit_1   prose_dd;     //
    bit_1   prose_dc;     //
    bit_1   prose_relay;  //
    bit_1   cp_ciot;      //
    bit_1   up_ciot;      //
    bit_1   s1u_data;     //
    bit_1   erwo_pdn;     //
    bit_1   hc_cp_ciot;   //
    bit_1   epco;         //
    bit_1   multiple_drb; //
    bit_1   v2x_pc5;      //
    bit_1   restrict_ec;  //
    bit_1   cp_backoff;   //
    bit_1   dcnr;         //
    bit_1   n1mode;       //
    bit_1   sgc;          //
    bit_1   f_bearers;    //
};

// 9.11.3.48a S1 UE security capability
// 9.9.3.36 in TS 24.301 g11

/*
9.11.3.49	Service area list
8	7	6	5	4	3	2	1
Service area list IEI	octet 1
Length of service area list contents	octet 2
Partial service area list 1	octet 3  octet i
Partial service area list 2	octet i+1*  octet l*
…	octet l+1*  octet m*
Partial service area list p	octet m+1*  octet n*

Figure 9.11.3.49.1: Service area list information element
8	7	6	5	4	3	2	1
Allowed type	Type of list	Number of elements	octet 1
MCC digit 2	MCC digit 1	octet 2
MNC digit 3	MCC digit 3	octet 3
MNC digit 2	MNC digit 1	octet 4
TAC 1	octet 5
TAC 1 (continued)	octet 6
TAC 1 (continued)	octet 7
…
TAC k	octet 3k+2*
TAC k (continued)	octet 3k+3*
TAC k (continued)	octet 3k+4*


8	7	6	5	4	3	2	1
Allowed type	Type of list	Number of elements	octet 1
MCC digit 2	MCC digit 1	octet 2
MNC digit 3	MCC digit 3	octet 3
MNC digit 2	MNC digit 1	octet 4
TAC 1	octet 5
TAC 1 (continued)	octet 6
TAC 1 (continued)	octet 7


8	7	6	5	4	3	2	1
Allowed type	Type of list	Number of elements	octet 1
MCC digit 2	MCC digit 1	octet 2
MNC digit 3	MCC digit 3	octet 3
MNC digit 2	MNC digit 1	octet 4
TAC 1	octet 5
TAC 1 (continued)	octet 6
TAC 1 (continued)	octet 7
MCC digit 2	MCC digit 1	octet 8*
MNC digit 3	MCC digit 3	octet 9*
MNC digit 2	MNC digit 1	octet 10*
TAC 2	octet 11*
TAC 2 (continued)	octet 12*
TAC 2 (continued)	octet 13*
…
MCC digit 2	MCC digit 1	octet 6k-4*
MNC digit 3	MCC digit 3	octet 6k-3*
MNC digit 2	MNC digit 1	octet 6k-2*
TAC k	octet 6k*-1
TAC k (continued)	octet 6k*
TAC k (continued)	octet 6k+1*


8	7	6	5	4	3	2	1
Allowed type	Type of list	Number of elements	octet 1
MCC digit 2	MCC digit 1	octet 2
MNC digit 3	MCC digit 3	octet 3
MNC digit 2	MNC digit 1	octet 4
*/
struct service_area_00_t {
    bit_5                  number;       // +1
    bit_2                  type;         //
    bit_1                  allowed_type; //
    mcc_mnc_t              mccmnc;       //
    std::vector< octet_3 > tac;          //
};
struct service_area_01_t {
    bit_5     number;       //
    bit_2     type;         //
    bit_1     allowed_type; //
    mcc_mnc_t mccmnc;       //
    octet_3   tac;          //
};                          //
struct service_area_10_t {
    struct area_t {
        mcc_mnc_t mccmnc; //
        octet_3   tac;    //
    };

    bit_5                 number;       //
    bit_2                 type;         //
    bit_1                 allowed_type; //
    std::vector< area_t > value;        //
};
struct service_area_11_t {
    bit_5     number;       // +1
    bit_2     type;         //
    bit_1     allowed_type; //
    mcc_mnc_t mccmnc;       //
};

struct service_area_t {
    bit_2                                type; //
    std::shared_ptr< service_area_00_t > l_00; //
    std::shared_ptr< service_area_01_t > l_01; //
    std::shared_ptr< service_area_10_t > l_10; //
    std::shared_ptr< service_area_11_t > l_11; //
};
struct service_area_list_t {
    std::vector< service_area_t > partial; //
};

/*
9.11.3.50	Service type
8	7	6	5	4	3	2	1
Service type IEI	Service type value	octet 1
*/
using service_type_t = bit_4;

/*
9.11.3.50A	SMS indication
8	7	6	5	4	3	2	1
SMS indication IEI	0 Spare	SAI	octet 1
*/
using sms_indication_t = bit_1;

/*
9.11.3.51	SOR transparent container
8	7	6	5	4	3	2	1
SOR transparent container IEI	octet 1
Length of SOR transparent container contents	octet 2 octet 3
SOR header	octet 4
SOR-MAC-IAUSF	octet 5-20
CounterSOR	octet 21-22
Secured packet	octet 23* - n*

Figure 9.11.3.51.1: SOR transparent container information element for list type with value
"0" and SOR data type with value "0" 8	7	6	5	4	3	2	1 SOR transparent
container IEI	octet 1 Length of SOR transparent container contents	octet 2 octet 3
SOR header	octet 4
SOR-MAC-IAUSF	octet 5-20
CounterSOR	octet 21-22
PLMN ID and access technology list	octet 23*-102*

Figure 9.11.3.51.3: PLMN ID and access technology list
8	7	6	5	4	3	2	1
SOR transparent container IEI	octet 1
Length of SOR transparent container contents	octet 2 octet 3
SOR header	octet 4
SOR-MAC-IUE	octet 5 - 20

Figure 9.11.3.51.4: SOR transparent container information element for SOR data type with
value "1" 8	7	6	5	4	3	2	1 0 Spare	ACK	List type	List indication	SOR data
type

Figure 9.11.3.51.5: SOR header for SOR data type with value "0"
8	7	6	5	4	3	2	1
0 Spare	SOR data type	octet 4
*/

struct sor_transparent_container_0_t {
    struct plmn_id_t {
        octet_3  id;                   //
        uint16_t access_technology_id; //
    };

    // uint8_t                   header;
    bit_1                                       sor_data_type;     //
    bit_1                                       list_ind;          //
    bit_1                                       list_type;         //
    bit_1                                       ack;               //
    octet_g                                     maci;              //
    uint16_t                                    counter;           //
    std::shared_ptr< octet_t >                  packet;            // plmn-id
    std::shared_ptr< std::vector< plmn_id_t > > access_technology; //
};

struct sor_transparent_container_1_t {
    // uint8_t                                     header;
    bit_1   sor_data_type; //
    octet_g maci;          //
};

// 9.11.3.52 Time zone
// 10.5.3.8 in TS 24.008 g10
using time_zone_t = uint8_t;

// 9.11.3.53 Time zone and time
// 10.5.3.9 in TS 24.008 g10
struct time_zone_time_t {
    uint8_t year;     //
    uint8_t month;    //
    uint8_t day;      //
    uint8_t hour;     //
    uint8_t minute;   //
    uint8_t second;   //
    uint8_t timezone; //
};

/*
9.11.3.53A	UE parameters update transparent container
8	7	6	5	4	3	2	1
UE parameters update transparent container IEI	octet 1
Length of UE parameters update transparent container contents	octet 2 octet 3
UE parameters update header	octet 4
UPU-MAC-IAUSF	octet 5-20
CounterUPU	octet 21-22
UE parameters update list	octet 23* - n*

Figure 9.11.3.53A.1: UE parameters update transparent container information element for UE
parameters update data type with value "0" 8	7	6	5	4	3	2	1 0 Spare	UE
parameters update data set 1 type	octet 23* Length of UE parameters update data set 1
octet 24*- 25* UE parameters update data set 1	octet 26*- x* … 0 Spare	UE parameters
update data set n type	octet y* Length of UE parameters update data set n	octet y+1*-
y+2* UE parameters update data set n	octet y+3*- n*

Figure 9.11.3.53A.2: UE parameters update list
8	7	6	5	4	3	2	1
Secured packet	octet a* - a+z*

Figure 9.11.3.53A.3: UE parameters update data set for UE parameters update data set type
with value "00000001" 8	7	6	5	4	3	2	1 Default configured NSSAI	octet b* -  c*

Figure 9.11.3.53A.5: UE parameters update transparent container information element for UE
parameters update data type with value "1" 8	7	6	5	4	3	2	1 0 Spare	REG
ACK	UPU data type

Figure 9.11.3.53A.6: UE parameters update header for UE parameters update data type with
value "0" 8	7	6	5	4	3	2	1 0 Spare	UPU data type	octet 4
*/
struct ue_parameter_update_container_0_t {
    struct item_t {
        bit_4   type;    //
        octet_t dataset; //
    };

    // uint8_t                   header;
    bit_1                                    upu_data_type;     //
    bit_1                                    reg;               //
    octet_g                                  upu_maci;          //
    uint16_t                                 counter;           //
    std::shared_ptr< std::vector< item_t > > access_technology; //
};
struct ue_parameter_update_container_1_t {
    // uint8_t                                     header;
    bit_1   upu_data_type; //
    octet_g upu_maci;      //
};

/*
9.11.3.54	UE security capability
8	7	6	5	4	3	2	1
UE security capability IEI	octet 1
Length of UE security capability contents	octet 2
5G-EA0	128- 5G-EA1	128- 5G-EA2	128- 5G-EA3	5G-EA4	5G-EA5	5G-EA6	5G-EA7	octet 3
5G-IA0	128- 5G-IA1	128- 5G-IA2	128- 5G-IA3	5G-IA4	5G-IA5	5G-IA6	5G-IA7	octet 4
EEA0	128- EEA1	128- EEA2	128- EEA3	EEA4	EEA5	EEA6	EEA7	octet 5*
EIA0	128- EIA1	128- EIA2	128- EIA3	EIA4	EIA5	EIA6	EIA7	octet 6*
0
Spare	octet 7* -10*
*/
struct ue_security_capability_t {
    uint8_t          nea; //
    uint8_t          nia; //
    opt_t< uint8_t > eea; //
    opt_t< uint8_t > eia; //
};

// 9.11.3.55 UE's usage setting
struct ue_usage_setting_t {
    bit_1 setting; //
};

// 9.11.3.56 UE status
struct ue_status_t {
    bit_1 s1_mode_reg; //
    bit_1 n1_mode_reg; //
};

// 9.11.3.57 Uplink data status
struct uplink_data_status_t {
    uint8_t psi_a; //
    uint8_t psi_b; //
};

// 9.11.3.58 Non-3gpp NW provided policies
// 10.5.5.37 in TS 24.008 g10
struct n3gpp_nw_provided_policies_t {
    bit_1 n3en_ind; //
};

// 9.11.3.59 EPS bearer context status
// 9.9.2.1 in TS 24.301 g11
struct eps_bearer_context_status_t {
    uint8_t ebi_a; //
    uint8_t ebi_b; //
};

// 9.11.3.60 Extended DRX parameters
// 10.5.5.32 in TS 24.008 g10
struct extended_drx_parameters_t {
    bit_4 edrx;               //
    bit_4 paging_time_window; //
};

// 9.11.3.61 Mobile station classmark 2
// 10.5.1.6 in TS 24.008 g10
struct mobile_station_classmark2_t {
    bit_3 rf_power_capability; //
    bit_1 a51;                 //
    bit_1 es_ind;              //
    bit_2 revision_level;      //
    bit_1 spare;               //
    bit_1 fc;                  //
    bit_1 vgcs;                //
    bit_1 vbs;                 //
    bit_1 sm_capability;       //
    bit_2 ss_screen_ind;       //
    bit_1 ps_capability;       //
    bit_1 spare_1;             //
    bit_1 a52;                 //
    bit_1 a53;                 //
    bit_1 cmsp;                //
    bit_1 solsa;               //
    bit_1 ucs2;                //
    bit_1 lcsvacap;            //
    bit_1 spare_2;             //
    bit_1 cm3;                 //
};

// 9.11.3.62 Supported codec list
// 10.5.4.32 in TS 24.008 g10
struct supported_codec_list_t {
    struct codec_t {
        uint8_t  id;     //
        uint16_t bitmap; //
    };
    std::vector< codec_t > codecs; //
};

// 9.11.3.63 MA PDU session information
/*
MA PD>U session information IEI	MA PDU session information value	octet 1
*/

using ma_pdu_session_information_t = bit_4;

/*
  9.11.4.1	5GSM capability
  8	7	6	5	4	3	2	1
  5GSM capability IEI	octet 1
  Length of 5GSM capability contents	octet 2
  0 Spare	MPTCP	ATS-LL	EPT-S1	MH6-PDU	RqoS	octet 3
  0	octet 4* -15*
  Spare	octet 4* -15*
*/
struct nsm_capability_t {
    bit_1 rqos;    //
    bit_1 mh6_pdu; //
    bit_1 ept_s1;  //
    bit_1 ats_ll;  //
    bit_1 mptcp;   //
};

/*
  9.11.4.2	5GSM cause
  8	7	6	5	4	3	2	1
  5GSM cause IEI	octet 1
  Cause value	octet 2
*/
using nsm_cause_t = uint8_t;

/*
  9.11.4.3	Always-on PDU session indication
  8	7	6	5	4	3	2	1
  Always-on PDU session indication IEI	0 Spare	APSI	octet 1
*/
struct always_on_pdu_session_indication_t {
    bit_1 apsi; //
};

/*
  9.11.4.4	Always-on PDU session requested
  8	7	6	5	4	3	2	1
  Always-on PDU session requested IEI	0 Spare	APSR	octet 1
*/
struct always_on_pdu_session_requested_t {
    bit_1 apsr; //
};

/*
  9.11.4.5	Allowed SSC mode
  8	7	6	5	4	3	2	1
  Allowed SSC mode IEI	0 Spare	SSC3	SSC2	SSC1	octet 1
*/
using allowed_ssc_mode_t = bit_3;

// 9.11.4.6 Extended protocol configuration options
// 10.5.6.3A ts24008-16.10
struct extended_pco_t {
    struct option_t {
        uint8_t id;      //
        octet_t content; //
    };

    bit_3                   configuration_protocol; //
    bit_4                   spare;                  //
    bit_1                   ext;                    //
    std::vector< option_t > options;                //
};

/*
  9.11.4.7	Integrity protection maximum data rate
  8	7	6	5	4	3	2	1
  Integrity protection maximum data rate IEI	octet 1
  Maximum data rate per UE for user-plane integrity protection for uplink	octet 2
  Maximum data rate per UE for user-plane integrity protection for downlink	octet 3
*/
struct integrity_protection_maximum_data_rate_t {
    uint8_t uplink;   //
    uint8_t downlink; //
};

// 9.11.4.8 Mapped EPS bearer contexts
struct mapped_eps_bearer_contexts_t {
    struct parameter_t {
        uint8_t id;      //
        octet_t content; //
    };
    struct context_t {
        uint8_t id; //
        // uint8_t length;
        bit_4                  parameters_n;   //
        bit_1                  ebit;           //
        bit_1                  spare;          //
        bit_2                  operation_code; //
        std::vector< octet_t > parameters;     //
    };

    std::vector< context_t > contexts; //
};

/*
  9.11.4.9	Maximum number of supported packet filters
  8	7	6	5	4	3	2
  Maximum number of supported packet filters IEI
  Maximum number of supported packet filters
  Maximum number of supported packet filters (continued)	0 Spare
*/
using bit1_b                                    = uint16_t;
using supported_packet_filters_maximum_number_t = bit_b;

using octet_c = uint8_t[12];
// 9.11.4.10 PDU address
struct pdu_address_t {
    bit_3   type;    //
    octet_c address; //
};

/*
  9.11.4.11	PDU session type
  8	7	6	5	4	3	2	1
  PDU session type IEI	0 Spare	PDU session type value	octet 1
*/
using pdu_session_type_t = bit_3;

/*
  9.11.4.12	QoS flow descriptions
  8	7	6	5	4	3	2	1
  QoS flow descriptions IEI	octet 1
  Length of QoS flow descriptions contents	octet 2  octet 3
  QoS flow description 1	octet 4  octet u
  QoS flow description 2	octet u+1  octet v
  ...	octet v+1  octet w
  QoS flow description n	octet w+1  octet x

  Figure 9.11.4.12.1: QoS flow descriptions information element
  8	7	6	5	4	3	2
  0 Spare	QFI
  Operation code	0 Spare
  0 Spare	E	Number of parameters
  Parameters list

  Figure 9.11.4.12.2: QoS flow description
  8	7	6	5	4	3	2	1
  Parameter 1	octet 7  octet m
  Parameter 2	octet m+1  octet n
  ...	octet n+1  octet o
  Parameter n	octet o+1  octet u

  Figure 9.11.4.12.3: Parameters list
  8	7	6	5	4	3	2	1
  Parameter identifier	octet 7
  Length of parameter contents	octet 8
  Parameter contents	octet 9  octet m
*/
struct qos_flow_descriptions_t {
    struct parameter_t {
        uint8_t id;      //
        octet_t content; //
    };
    struct entry_t {
        bit_6                      qfi;        //
        bit_3                      opcode;     //
        bit_1                      ebit;       //
        std::vector< parameter_t > parameters; //
    };
    std::vector< entry_t > descs; //
};

using qos_flow_description_parameter_t = qos_flow_descriptions_t::parameter_t;
using qos_flow_description_t           = qos_flow_descriptions_t::entry_t;

// 9.11.4.13	QoS rules
struct qos_rule_t {
    struct packet_filter_delete_t {
        bit_4 id;    //
        bit_4 spare; //
    };
    struct packet_filter_add_t {
        bit_4 id;        //
        bit_2 direction; //
        // uint8_t length;
        octet_t content; //
    };
    struct packet_filter_t {
        std::shared_ptr< packet_filter_add_t >    add;  // when rule-op is create / modify
        std::shared_ptr< packet_filter_delete_t > drop; //
    };

    uint8_t                        id;                  //
    uint16_t                       length;              //
    bit_4                          packet_filters_n;    //
    bit_1                          dqr;                 //
    bit_3                          rule_operation_code; //
    std::vector< packet_filter_t > packet_filters;      //
    opt_t< uint8_t >               precedence;          //
    opt_t< bit_6 >                 qos_flow_id;         //
    opt_t< bit_1 >                 segregation;         //
};

using qos_rule_packet_filter_delete_t = qos_rule_t::packet_filter_delete_t;
using qos_rule_packet_filter_add_t    = qos_rule_t::packet_filter_add_t;
using qos_rule_packet_filter_t        = qos_rule_t::packet_filter_t;

struct qos_rules_t {
    std::vector< qos_rule_t > rules; //
};

/*
  9.11.4.14	Session-AMBR
  8	7	6	5	4	3	2	1
  Session-AMBR IEI	octet 1
  Length of Session-AMBR contents	octet 2
  Unit for Session-AMBR for downlink	octet 3
  Session-AMBR for downlink	octet 4-5
  Unit for Session-AMBR for uplink	octet 6
  Session-AMBR for uplink	octet 7-8
*/
struct session_ambr_t {
    uint8_t  downlink_unit; //
    uint16_t downlink;      //
    uint8_t  uplink_unit;   //
    uint16_t uplink;        //
};

/* 9.11.4.15	SM PDU DN request container
  8	7	6	5	4	3	2	1
  SM PDU DN request container information IEI	octet 1
  SM PDU DN request container information length	octet 2
  DN-specific identity	octets 3*-n*
*/
using sm_pdu_dn_request_container_t = octet_t;

/*
  9.11.4.16	SSC mode
  8	7	6	5	4	3	2	1
  SSC mode IEI	0 Spare	SSC mode value	octet 1
*/
using ssc_mode_t = bit_3;

/*
  9.11.4.17	Re-attempt indicator
  8	7	6	5	4	3	2
  Re-attempt indicator IEI
  Length of Re-attempt indicator contents
  0 Spare	EPLMNC	RATC
*/
struct reattempt_indicator_t {
    bit_1 ratc;   //
    bit_1 eplmnc; //
};

/*
  9.11.4.18	5GSM network feature support
  8	7	6	5	4	3	2	1
  5GSM network feature support IEI	octet 1
  Length of 5GSM network feature support contents	octet 2
  0 Spare	EPT-S1	octet 3
  0	octet 4* -15*
  Spare	octet 4* -15*
*/
using nsm_network_feature_support_t = bit_1;

/*
  9.11.4.19	Session-TMBR
  8	7	6	5	4	3	2	1
  Session-TMBR IEI	octet 1
  Length of Session-TMBR contents	octet 2
  Unit for Session-TMBR for downlink	octet 3
  Session-TMBR for downlink	octet 4-5
  Unit for Session-TMBR for uplink	octet 6
  Session-TMBR for uplink	octet 7-8
*/
struct session_tmbr_t {
    uint8_t  downlink_unit; //
    uint16_t downlink;      //
    uint8_t  uplink_unit;   //
    uint16_t uplink;        //
};

// 9.11.4.20	Serving PLMN rate control
// See subclause 9.9.4.28 in 3GPP TS 24.301 [13].
/*
8	7	6	5	4	3	2	1
Serving PLMN rate control IEI	octet 1
Length of serving PLMN rate control contents	octet 2
Serving PLMN rate control value	octet 3
octet 4
*/
using serving_plmn_rate_control_t = uint16_t;

/*
  9.11.4.21	5GSM congestion re-attempt indicator
  8	7	6	5	4	3	2
  5GSM congestion re-attempt indicator IEI
  Length of 5GSM congestion re-attempt indicator contents
  0 Spare	ABO
*/
using nsm_congestion_reattempt_indicator_t = bit_1;

/*
  9.11.4.22	ATSSS container
  8	7	6	5	4	3	2	1
  ATSSS container IEI	octet 1
  Length of ATSSS container contents	octet 2 octet 3
  ATSSS container contents	octet 4  octet x
*/
using atsss_container_t = octet_t;

/*
  9.11.4.23	Control plane only indication
  8	7	6	5	4	3	2	1
  Control plane only indication IEI	0 Spare	CPOI value	octet 1
*/
using control_plane_only_indication_t = bit_1;
