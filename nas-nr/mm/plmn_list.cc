#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  [3] 10.5.1.13 PLMN list GSM-A */
/*4A    Equivalent PLMNs    PLMN list     9.11.3.45    O    TLV    5-47*/
int dissect_plmn_list(dissector d, context* ctx) {
    const use_context uc(ctx, "plmn-list", d, 0);
    return d.offset - uc.offset;
}
