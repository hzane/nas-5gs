#include "dissector.hh"
#include "use_context.hh"

//    9.11.2.8	S-NSSAI
result_t die_s_nssai(dissector d, context* ctx, s_nssai_t* ret) {
    auto              len = d.length;
    const use_context uc(&d, ctx, "s-nssai", 0);

    // SST	octet 3
    de_uint8(d, ctx, &ret->sst).step(d);

    if (len == 0x02) { // sst and mapped hplmn sst
        ret->mapped_hplmn_sst.present = true;
        de_uint8(d, ctx, &ret->mapped_hplmn_sst.v).step(d);
    }
    if (len >= 0x04) { // sst and sd
        ret->sd.present = true;
        de_fixed(d, ctx, ret->sd.v).step(d);
    }
    if (len >= 0x05) { // sst, sd and mapped hplmn sst
        ret->mapped_hplmn_sst.present = true;
        de_uint8(d, ctx, &ret->mapped_hplmn_sst.v).step(d);
    }
    if (len == 0x08) { // sst, sd, mapped hplmn sst and hplmn sd
        ret->mapped_hplmn_sd.present = true;
        de_fixed(d, ctx, ret->mapped_hplmn_sd.v).step(d);
    }
    return {uc.consumed()};
}
