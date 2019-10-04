#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <utility>
#include <variant>
#include <vector>
#include "definitions.hh"


struct protocol_t {
    const char* name;
    const char* full_name;
};

inline const protocol_t nas_nr = {
    "NAS-5GS",
    "Non-Access-Stratum 5GS (NAS)PDU, References: 3GPP TS 24.501 15.1.0",
};
