#pragma once
#include <cstdint>
#include <vector>

template<typename field>
struct field_v{
    const field_meta* meta     = nullptr;
    bool              presence = false;
    int               length   = 0;
    field             field    = {};
};

using additional_info = vector< uint8_t >;

using dnn = string;

struct mcc_mnc {
    mcc v_string;
    mnc v_string;
};
