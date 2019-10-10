#include "core.hh"

#include <sstream>

#include "context.hh"
#include "dissector.hh"
#include "protocol.hh"

inline int ws_ctz32(uint32_t x) {
    /* From http://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup */
    static const uint8_t table[32] = {
        0,  1,  28, 2,  29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4,  8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6,  11, 5,  10, 9,
    };

    return table[((uint32_t)((x & (uint32_t)(0u - x)) * 0x077CB531U)) >> 27u];
}
uint8_t ws_ctz8(uint8_t x){
    return static_cast<uint8_t>(ws_ctz32(x));
}
unsigned int ws_ctz(uint64_t x) {
    auto hi = uint32_t(x >> 32u);
    auto lo = (uint32_t) x;

    if (lo == 0)
        return 32 + ws_ctz32(hi);
    else
        return ws_ctz32(lo);
}

uint8_t mask_u8(uint8_t v, uint8_t mask){
    if (mask == 0) return v;
    return (v & mask) >> ws_ctz8(mask);
}

uint16_t mask_u16(uint16_t v, uint16_t mask){
    if (mask == 0) return v;
    return (v & mask) >> ws_ctz(mask);
}

uint8_t umask(uint8_t v, uint8_t mask) { return mask_u8(v, mask); }
uint16_t umask(uint16_t v, uint16_t mask) { return mask_u16(v, mask); }

std::string join(const std::vector< std::string >& strings, const char* sep){
    if (sep == nullptr) sep = "";
    std::ostringstream oss;
    if(strings.empty()) return "";
    oss<<strings.front();
    auto i = strings.begin();
    for(++i; i!=strings.end(); ++i){
        oss<<sep<<*i;
    }
    return oss.str();
}
