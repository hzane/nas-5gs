#include <cstring>
#include "dissector.hh"

dissector dissector::slice(int len) const {
    auto ret   = *this;
    ret.length = len;
    return ret;
}

const uint8_t* dissector::safe_ptr(int skip) const {
    if (offset +skip>= view_length) return nullptr;
    if (length - skip <= 0) return nullptr;
    return view + offset + skip;
}

int dissector::safe_length(int len, int skip) const {
    if (length <= skip) return 0;
    if (len < 0) len = length - skip;
    return len <= (length - skip) ? len : 0;
}

uint8_t dissector::uint8(bool step, int skip)  {
    const auto p = safe_ptr(skip);
    if (step) this->step(skip + 1);

    return p ? *p : 0;
}

uint16_t dissector::uint16(bool step, int skip)  {
    const auto p = safe_ptr(skip);
    const auto len = safe_length(2, skip);
    if (step) this->step(skip + 2);
    uint16_t h = p[0];
    uint16_t l = p[1];
    return (p && len > 0) ? ((h << 8u) + l) : 0;
}

int dissector::octet(uint8_t* to, int len, bool step) {
    const auto p = safe_ptr();
    const auto l = safe_length(len);

    if (step) this->step(len);
    std::memcpy(to, p, l);
    return len;
}
