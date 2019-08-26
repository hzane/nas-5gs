#include "config.hh"
#include "proto.hh"
#include "field_meta.hh"

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
