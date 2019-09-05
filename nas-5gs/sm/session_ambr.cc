#include "../dissect_sm_msg.hh"

// 9.11.4.14    Session-AMBR
int sm::dissect_ses_ambr(dissector d, context* ctx) {
    const use_context uc(ctx, "session-ambr", d, 0);
    
    /* Unit for Session-AMBR for downlink */
    auto unit = (int) d.uint8();
    d.add_item(1, &hf_sm_ses_ambr_dl_unit, enc::be);
    d.step(1);

    // const char* unit_str = "";
    /* Session-AMBR for downlink (octets 4 and 5) */
    auto ambr_val = static_cast< uint32_t >(d.ntohs());

    auto item = d.add_item(2, &hf_sm_ses_ambr_dl, enc::none);
    item->set_string(ambr_string(ambr_val, unit));
    d.step(2);

    unit = static_cast< int >(d.uint8());
    item = d.add_item(1, &hf_sm_ses_ambr_ul_unit, enc::be);
    d.step(1);

    ambr_val = static_cast< uint32_t >(d.ntohs());
    item     = d.add_item(2, &hf_sm_ses_ambr_ul, enc::none);
    item->set_string(ambr_string(ambr_val, unit));
    d.step(2);

    return uc.length;
}
