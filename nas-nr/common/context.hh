#pragma once
#include <cstdint>
#include <string>
#include <vector>

struct nr_security_context {
    uint8_t activated                   = 0;
    uint8_t security_type               = 0; // 33.401
    uint8_t nas_ksi                     = 0; // NAS key set identifier for E-UTRAN
    int vector_index                    = 0; // pointer of vector, -1 means invalid
    uint8_t          cyphering_key[16]  = {};
    uint8_t          integrity_key[16]  = {};
    uint32_t dl_count_overflow          = 0; // downlink count parameters
    uint32_t dl_count_seq_no            = 0;
    uint32_t ul_count_overflow          = 0;
    uint32_t ul_count_seq_no            = 0;
    struct {
        uint8_t ciphering_nr   = 0; // ciphering algo for nr
        uint8_t integrity_nr   = 0; // integrity algo for nr
        uint8_t ciphering_umts = 0; // algorithm for ciphering
        uint8_t integrity_umts = 0; // algorithm for integrity
        uint8_t ciphering_gprs = 0; // algorithm used for ciphering
        uint8_t integrity_gprs = 0; // unused
        bool    umts_present   = false;
        bool    gprs_present   = false;
    } capability; // UE network capability
    struct {
        uint8_t ciphering_type = 0;
        uint8_t integrity_type = 0; // for integrity protection
    } selected_algorithm;           // AMF selected algorithm
};

struct context : nr_security_context {
    bool                            security_context_available = false;
    uint8_t                         payload_content_type       = 0;
    std::vector< std::string >      paths                      = {};
};
