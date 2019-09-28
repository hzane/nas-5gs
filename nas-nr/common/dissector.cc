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

void dissector::add_bits(const bool_field* metas[], bool step)  {
    for (const bool_field** meta = metas; *meta != nullptr; ) {
        (void) add_item(*meta); // NOLINT
        ++meta;
    }
    if (step) this->step(1);
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

const uint8_t* dissector::ptr() const {
    if (tvb->length < 0 || offset >= tvb->length) return nullptr;
    return tvb->data + offset;
}

int dissector::safe_length(int len) const {
    if (length < 0) return 0;
    if (len < 0) len = length - offset;
    if (offset + len <= length) return len;
    return 0;
}

uint8_t dissector::uint8(bool step) {
    const auto p = ptr();
    if(step) this->step(1);
    return p ? *p : 0;
}

uint16_t dissector::uint16(bool step)  {
    const auto p = ptr();
    const auto l = safe_length(2);
    if (step) this->step(2);
    return (p && l > 0) ? n2uint16(p) : 0;
}

uint32_t dissector::uint32() const {
    const auto p = ptr();
    const auto l = safe_length(4);
    if (p && l > 0) return n2uint32(p);
    return 0;
}


int     dissector::add_item( const uint8_field* f, bool step)  {
    add_item(1, f->name, istring(umask(uint8(step), f->mask)));

    return 1;
}


int dissector::add_item(const tag_field*f, bool step)  {
    auto tag = vstring(f->tags, umask(uint8(step), f->mask));
    add_item(1, f->name, tag);
    return 1;
}


int dissector::add_item(const bool_field*f, bool step)  {
    auto v = bstring(umask(uint8(step), f->mask), f->values.false_string, f->values.true_string);
    add_item(1, f->name, v);

    return 1;
}


int dissector::add_item(const octet_field*f, int len, bool step)  {
    add_item(len, f->name, hstring(ptr(), safe_length(len)));
    if(step) this->step(len);
    return len;
}
