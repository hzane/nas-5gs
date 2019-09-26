#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <utility>
#include <variant>
#include <vector>
#include "definitions.hh"

struct nas_message_t;
struct nas_message_plain_t;
struct nas_message_protected_t;
struct nsm_message_t;
struct nmm_message_t;


struct nas_message_plain_t {
    std::shared_ptr< nmm_message_t > nmm = {};
    std::shared_ptr< nsm_message_t > nsm = {};
};

struct nas_message_protected_t {
    uint8_t             epd                  = 0;  // 9.2
    uint8_t             security_header_type = 0;  // 9.3
    octet_4             auth_code            = {}; // 9.8
    uint8_t             sequence_no          = 0;  // 9.10	Sequence number
    nas_message_plain_t plain                = {}; // 9.9
};

struct nas_message_t {
    std::shared_ptr< nas_message_plain_t >     plain;
    std::shared_ptr< nas_message_protected_t > sec;
};

struct protocol_t {
    const char* name;
    const char* full_name;
};

inline const protocol_t nas_nr = {
    "NAS-5GS",
    "Non-Access-Stratum 5GS (NAS)PDU, References: 3GPP TS 24.501 15.1.0",
};
