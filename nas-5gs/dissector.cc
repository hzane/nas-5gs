#include "config.hh"
#include "proto.hh"
#include "field_meta.hh"
#include "tvbuff.hh"
#include <cstdarg>

// struct dissector defined in config.hh

void dissector::add_bits(const field_meta* metas[]) const {
    for (auto meta = metas; *meta != nullptr; meta++) {
        (void) add_item(1, *meta, enc::be); // NOLINT        
    }
}
proto_node* dissector::add_item(int len, const field_meta* meta, uint32_t enc) const {
    return tree->add_item(pinfo, tvb, offset, len, meta, enc);
}

proto_node *dissector::add_item(int len, const char*format, ...) const {
    va_list args;
    va_start(args, format);
    const auto txt = vformat(format, args);
    va_end(args);
    return tree->add_subtree(pinfo, tvb, offset, len, txt.c_str());
}

void dissector::extraneous_data_check(int maxlen, context* ctx)const {
    if (maxlen < 0) return;
    if (length < 0) {
        diag("underflow at %s %d:%d\n", paths(ctx).c_str(), offset, length);
    }
    if (length > maxlen) {
        diag("extraneous data (%d) bytes at %s %d\n",
             (length - maxlen),
             paths(ctx).c_str(),
             offset);
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

dissector dissector::use_elem(void* elem)const {
    return dissector{pinfo, tree, tvb, offset, length, elem};
}

uint8_t dissector::uint8() const{
    const auto p = safe_ptr();
    if (p) return *p;
    return 0;
}

uint16_t dissector::ntohs() const {
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
