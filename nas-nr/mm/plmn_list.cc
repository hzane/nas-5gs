#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/*  [3] 10.5.1.13 PLMN list GSM-A */
/*4A    Equivalent PLMNs    PLMN list     9.11.3.45    O    TLV    5-47*/
result_t die_plmn_list(dissector d, context* ctx, plmn_list_t* ret) {
    const use_context uc(&d, ctx, "plmn-list", 0);
    while (d.length > 0) {
        mcc_mnc_t mm = {};
        die_mcc_mnc(d, ctx, &mm).step(d);
        ret->plmns.push_back(mm);
    }
    return {uc.length};
}
