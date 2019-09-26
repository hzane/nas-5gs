#pragma once
#include <cstdint>
#include <optional>
#include <variant>
#include <vector>

#include "nas.hh"

struct nmm_header_t {
    uint8_t epd;                      // 9.2	Extended protocol discriminator
    uint8_t security_header_type : 4; /*9.3*/
    uint8_t spare : 4;                /*9.5*/
    uint8_t message_type;             /*9.7*/
};

struct nsm_header_t {
    uint8_t epd;            // 9.2	Extended protocol discriminator
    uint8_t pdu_session_id; /*9.4*/
    uint8_t pti;            /*procedure transaction identity 9.6*/
    uint8_t message_type;   /* 9.7*/
};