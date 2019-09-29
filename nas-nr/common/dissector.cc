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

uint24_t dissector::uint24(bool step){
    const auto p = ptr();
    const auto l = safe_length(3);
    if (step) this->step(3);
    return (p && l>0) ? n2uint24(p) : 0;
}

uint32_t dissector::uint32() const {
    const auto p = ptr();
    const auto l = safe_length(4);
    if (p && l > 0) return n2uint32(p);
    return 0;
}


node_t     dissector::add_item( const uint8_field* f, bool step)  {
    return add_item(1, f->name, istring(umask(uint8(step), f->mask)));
}

node_t dissector::add_item(const uint24_field*f, bool step){
    return add_item(3, f->name, i24string(u24mask(uint24(step), f->mask)));
}


node_t dissector::add_item(const tag_field*f, bool step)  {
    auto tag = vstring(f->tags, umask(uint8(step), f->mask));
    return add_item(1, f->name, tag);
}


node_t dissector::add_item(const bool_field*f, bool step)  {
    auto v = bstring(umask(uint8(step), f->mask), f->values.false_string, f->values.true_string);
    return add_item(1, f->name, v);
}


node_t dissector::add_item(const octet_field*f, int len, bool step)  {
    auto ret = add_item(len, f->name, hstring(ptr(), safe_length(len)));
    if(step) this->step(len);
    return ret;
}

node_t dissector::add_item(const element_field*f, int len, bool step){
    auto ret= add_item(len, f->name);
    if (len>=0 && step) this->step(len);
}
node_t dissector::add_item(const uint16_field* fm, bool step) {
    return add_item(2, fm->name, istring(u16mask(uint16(step), fm->mask)));
}
node_t dissector::add_item(const ipv4_field*f, bool step){
    auto p = ptr();
    auto l = safe_length(4);

    auto v = (p && l>0) ? formats("%u.%u.%u.%u", p[0], p[1], p[2], p[3]) : string();

    auto ret= add_item(4, f->name, v);
    if (step) this->step(4);

    return ret;
}
node_t dissector::add_item(const mac_field* fm, bool step) {
    auto v = hstring(ptr(), safe_length(6), ":");
    auto ret = add_item(6, fm->name, v);

    if (step) this->step(6);

    return ret;
}
node_t dissector::add_item(const ipv6_field* fm, int len, bool step) {
    auto v = hstring(ptr(), safe_length(len), ":");
    auto ret = add_item(len, fm->name, v);

    if (step) this->step(len);

    return ret;
}
node_t dissector::add_item(const string_field* fm, int len, bool step) {
    auto v = std::string((const char*)ptr(), safe_length(len));
    auto ret = add_item(len, fm->name, v);

    if(step) this->step(len);
    return ret;
}
node_t dissector::add_item(const imei_field* fm, int len, bool step) {
    auto v = imei_string(ptr(), safe_length(len));
    auto ret = add_item(len, fm->name, v);

    if(step) this->step(len);

    return ret;
}
node_t dissector::add_item(const psi_field* fm, bool step) {
    auto v = uint8(step);
    auto mask = fm->mask ? fm->mask : 0xffu;
    for(uint8_t i = 0; i<8;){
        if (mask&(1u<<i)){
            auto txt =  v&(1u<<i) ? fm->avail : fm->not_avail;
            auto name = formats("%s(%d)", fm->name, i+fm->offset);
            (void) add_item(1, name, txt);
        }
        ++i;
    }
    return tree;
}

node_t dissector::add_item(const bcd_field*f, int len, bool step){
    auto v = bcd_string(ptr(), safe_length(len));
    auto ret = add_item(len, f->name, v);
    if (step) this->step(len);
    return ret;
}
node_t dissector::add_item(const sms_field* fm, int len, bool step) {
    auto v = sms_string(ptr(), safe_length(len));
    auto ret = add_item(len, fm->name, v);

    if(step) this->step(len);
    return ret;
}
node_t dissector::add_item(const mccmnc_field* fm, bool step) {
    auto mcc = mcc_string(ptr(), safe_length(3));
    add_item(3, "MCC", mcc);

    auto mnc = mnc_string(ptr(), safe_length(3));
    add_item(3, "MNC", mnc);

    if (step) this->step(3);

    return tree;
}
node_t dissector::add_item(const timezone_field* fm, bool step) {
    auto v = gmt_string(ptr());
    auto ret = add_item(1, fm->name, v);

    if(step) this->step(1);

    return ret;
}
node_t dissector::add_item(const utc_field* fm, bool step) {
    auto v= utc_string(ptr(), safe_length(7));
    auto ret = add_item(7, fm->name, v);

    if (step) this->step(7);

    return ret;
}
