#include "config.hh"
#include "proto.hh"
#include "field_meta.hh"
#include "tvbuff.hh"
#include "packet_info.hh"

// struct dissector defined in config.hh

void dissector::add_bits(const field_meta* metas[]) {
    for (auto meta = *metas; meta != nullptr; meta++) {
        add_item(1, meta, enc::be);
    }
}
proto_node* dissector::add_item(int len, const field_meta* meta, uint32_t enc) {
    return tree->add_item(pinfo, tvb, offset, len, meta, enc);
}

void dissector::extraneous_data_check(int maxlen) {
    if (length < 0) {
        bug("overflow at %d\n", offset);
    }
    if (length > maxlen) {
        tree->add_expert(pinfo,
                         tvb,
                         offset,
                         length - maxlen,
                         "extraneous data (%d) bytes",
                         (length - maxlen));
    }
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

void dissector::set_private(const char* name, uint64_t v) {
    pinfo->iprivates[string(name)] = v;
}
uint64_t dissector::get_private(const char* name, uint64_t v) {
    auto i = pinfo->iprivates.find(string(name));
    if (i != pinfo->iprivates.end()) return i->second;
    return v;
}
