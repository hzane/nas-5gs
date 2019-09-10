#pragma once
#include <cstdint>
#include <optional>
#include <variant>
#include <vector>
#include "config.hh"
#include "field_meta.hh"

template<typename field>
struct field_v{
    const field_meta* meta     = nullptr;
    bool              presence = false;
    int               length   = 0;
    field             field    = {};
};

using additional_info = std::vector< uint8_t >;

using dnn = string;

struct mcc_mnc {
    const v_string mcc;
    const v_string mnc;
};

using eap = string;

struct gprs_timer {
    uint8_t         val;
    v_string        unit;
};

using gprs_timer2 = gprs_timer;
using gprs_timer3 = gprs_timer;

using authentication_code = uint32_t;
using nibble = uint8_t;
using bit3 = uint8_t;
using bit1 = uint8_t;
using bit7 = uint8_t;
using bit2 = uint8_t;

struct intra_n1_mode_container {
    authentication_code auth_code;
    nibble             integrity_protected_algo_type;
    nibble              ciphering_algo_type;
    bit3                ksi;
    bool                tsc;
    bool                kacf;
    uint8_t             sequence_no;
};

// 9.11.2.7 N1 mode to S1 mode NAS transparent container
struct n1_to_s1_container {
    uint8_t sequence_no;
};

using uint24_t = uint32_t;

using std::optional;

// S-NSSAI   9.11.2.8
struct s_nssai{
    uint8_t   slice_service_type;
    optional< uint24_t > slice_differentiator;
    optional< uint8_t > mapped_configured_sst;
    optional< uint8_t > mapped_configured_sd;
};


struct s1_to_n1_container {
    authentication_code auth_code;
    nibble              integrity_protected_algo_type;
    nibble              ciphering_algo_type;
    bit3                ksi;
    bool                tsc;
    bool                ncc;
};

// 9.11.3.2	5GMM cause
using mm_cause = v_string;

struct mm_capability {
    bool             service_gap_control;
    bool             header_compression_for_control_plane;
    bool             n3data;
    bool             control_plane;
    bool             restrict_ec;
    bool             lte_positioning_protocol;
    bool             handover_attach;
    bool             s1_mode;
    optional< bool > sr_vcc;
    optional< bool > user_plane;
};

struct mm_status {
    mm_cause mm_cause;
};

/* * 9.11.3.3 5GS identity type */
using identity_type = v_string;

struct mobile_id_none {
    bool odd_even;
    bit3 type_id; // = 0
};

using imei = std::vector<uint8_t>;

struct mobile_id_imei {
    bool odd_even;
    bit3 type_id;
    imei imei;
};
using mobile_id_imeisv = mobile_id_imei;

using uint48_t = uint64_t;

struct mobile_id_mac {
    bit3 type_id;  // = 6
    uint48_t mac;
};

struct mobile_id_guti{
    bit3     type_id;
    mcc_mnc  mcc_mnc;
    bit10    amf_region_id;
    bit6     amf_pointer;
    uint32_t tmsi;
};

using suci_nai = std::vector<uint8_t>;

using scheme_null = std::vector< uint8_t >;

using scheme_output = std::vector< uint8_t >;

struct supi_format_0 {
    mcc_mnc                                    mcc_mnc;
    uint16_t                                   routing_indication;
    v_string                                   protection_scheme_id;
    uint8_t                                    public_key_identifier;
    std::variant< scheme_null, scheme_output > scheme_output;
};

struct mobile_id_suci {
    bit3     type_id; // = 1
    v_string                supi_format_type;
    optional< supi_format_0 > supi_format_0;
    optional< suci_nai >  suci_nai;
};

using bit6 = uint8_t;
using bit10 = uint16_t;

struct mobile_id_s_tmsi {
    bit3     type_id;    // = 4
    bit10    amf_set_id; //
    bit6     amf_pointer;
    uint32_t tmsi;
};

// 5GS mobile identity - 5G-GUTI

using mobile_id = std::variant< mobile_id_none,
                                mobile_id_suci,
                                mobile_id_guti,
                                mobile_id_imei,
                                mobile_id_s_tmsi,
                                mobile_id_imeisv,
                                mobile_id_mac >;


struct network_feature_support{
    bool mpsi;
    bool ims_iwk;
    bool ims_emf;
    bool ims_emc;
    bool ims_vops;
};
