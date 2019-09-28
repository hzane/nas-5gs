#include <cstdarg>

#include "buff_view.hh"
#include "config.hh"
#include "field_meta.hh"
#include "proto.hh"
#include "dissector.hh"


void dissector::step(int consumed) {
    offset += consumed;
    length -= consumed;
}

void dissector::add_bits(const field_meta* metas[]) const {
    for (const field_meta** meta = metas; *meta != nullptr; meta++) {
        (void) add_item(1, *meta); // NOLINT
    }
}

node_t dissector::add_item(int len, const field_meta* meta) const {
    return tree->add_item(offset, len, meta);
}

node_t dissector::add_item(int len, const string& name, const string& val) const {
    return tree->add_item(offset, len, name, val);
}
node_t dissector::set_item(int len, const string& val) const {
    tree->set_item(offset, len, val);
    return tree;
}

node_t dissector::add_expert(int len, const string&txt) const {
    return tree->add_item(offset, len, txt);
}

dissector dissector::slice(int len) const {
    auto ret   = *this;
    ret.length = len;
    return ret;
}

const uint8_t* dissector::safe_ptr() const {
    if (tvb->length < 0 || offset >= tvb->length) return nullptr;
    return tvb->data + offset;
}

int dissector::safe_length(int len) const {
    if (length < 0) return 0;
    if (len < 0) len = length - offset;
    if (offset + len <= length) return len;
    return 0;
}

uint8_t dissector::uint8() const{
    const auto p = safe_ptr();
    if (p) return *p;
    return 0;
}

uint16_t dissector::uint16() const {
    const auto p = safe_ptr();
    const auto l = safe_length(2);
    if (p && l > 0) return n2uint16(p);
    return 0;
}

uint32_t dissector::uint32() const {
    const auto p = safe_ptr();
    const auto l = safe_length(4);
    if (p && l > 0) return n2uint32(p);
    return 0;
}
