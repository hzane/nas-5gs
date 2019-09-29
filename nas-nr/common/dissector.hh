#pragma once
#include <memory>
#include <string>

#include "formats.hh"

struct packet;
struct node;
struct buff_view;
struct field_meta;
struct context;
using string = std::string;
using node_t = std::shared_ptr< node >;

struct v_string;
struct tf_string;

struct uint8_field {
    const char* name = nullptr;
    uint8_t     mask = 0;
};
struct tag_field {
    const char*     name = nullptr;
    uint8_t         mask = 0;
    const v_string* tags = nullptr;
};
struct bool_field {
    const char* name   = nullptr;
    uint8_t     mask   = 0;
    tf_string   values = {};
};
struct octet_field {
    const char* name = nullptr;
    const char* sep = nullptr;
    const char* lf = nullptr;
};

using uint24_t = uint32_t;

struct uint24_field {
    const char* name = nullptr;
    uint24_t    mask = 0;
};

struct uint16_field {
    const char* name = nullptr;
    uint16_t mask = 0;
};

struct ipv4_field{
    const char* name = nullptr;
};

struct mac_field{
    const char*name = nullptr;
};

struct ipv6_field{
    const char*name = nullptr;
};

struct string_field{
    const char*name = nullptr;
};

struct imei_field{
    const char*name = nullptr;
};

struct sms_field{
    const char* name = nullptr;
};

struct bcd_field{
    const char* name = nullptr;
};

struct mccmnc_field{
    const char* name = nullptr;
};

struct psi_field{
    const char* name=nullptr;
    uint8_t mask = 0;
    uint8_t offset = 0;
    const char* not_avail = nullptr;
    const char* avail = nullptr;
};
struct ambr_field{
    const char* name=nullptr;
};
struct timezone_field{
    const char* name = nullptr;
};
struct utc_field{
    const char* name = nullptr;
};

struct element_field {
    const char*   name    = nullptr;
    uint8_field*  u8      = nullptr;
    uint24_field* u24     = nullptr;
    tag_field*    tag     = nullptr;
    bool_field*   boolean = nullptr;
    octet_field*  octet   = nullptr;
};

struct dissector {
    inline static string none = string();

    packet*    packet = nullptr;
    node_t     tree   = nullptr;
    buff_view* tvb    = nullptr;
    int        offset = 0;
    int        length = 0;
    void*      data   = nullptr;

    void   step(int consumed);
    node_t add_item(const uint8_field* fm, bool step = false);
    node_t add_item(const tag_field* fm, bool step = false);
    node_t add_item(const octet_field* fm, int len, bool step = false);
    node_t add_item(const bool_field* fm, bool step = false);
    node_t add_item(const uint24_field* fm, bool step = false);
    node_t add_item(const uint16_field* fm, bool step = false);
    node_t add_item(const ipv4_field* fm, bool step = false);
    node_t add_item(const mac_field* fm, bool step = false);
    node_t add_item(const ipv6_field* fm, int len, bool step = false);
    node_t add_item(const imei_field* fm, int len, bool step = false);
    node_t add_item(const string_field* fm, int len, bool step = false);
    node_t add_item(const sms_field* fm, int len, bool step = false);
    node_t add_item(const element_field* fm, int len, bool step = false);
    node_t add_item(const bcd_field* fm, int len, bool step = false);
    node_t add_item(const psi_field* fm, bool step = false);
    node_t add_item(const timezone_field* fm, bool step = false);
    node_t add_item(const utc_field* fm, bool step = false);
    node_t add_item(const ambr_field* fm, bool step = false);
    node_t add_item(const mccmnc_field* fm, bool step = false);
    node_t add_item(int len, const string& name, const string& val = none) const;
    node_t set_item(int len, const string& val) const;
    node_t add_expert(int len, const string& name) const;
    void   add_bits(const bool_field* metas[], bool step = false);
    auto   ptr() const -> const uint8_t*;
    auto   safe_length(int len) const -> int;
    auto   slice(int len) const -> dissector;
    auto   uint8(bool step = false) -> uint8_t;
    auto   uint16(bool step = false) -> uint16_t;
    auto   uint24(bool step = false) -> uint24_t;
    auto   uint32() const -> uint32_t;
};
