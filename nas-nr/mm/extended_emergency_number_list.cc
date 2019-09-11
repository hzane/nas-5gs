#include "../dissect_mm_msg.hh"

const element_meta mm::ext_emerge_num_list = {
    0x7A,
    "Extended emergency number list",
    dissect_ext_emerge_num_list,
    nullptr,
};

// Extended emergency number list  9.11.3.26
int mm::dissect_ext_emerge_num_list(dissector d, context* ctx) {
    // See subclause 9.9.3.37A in 3GPP TS 24.301 [15].
    const use_context uc(ctx, "extended-emergency-number-list", d, 0);

    auto n = d.add_item(1, &hf_ext_emerge_num_list_eenlv, enc::be);
    d.step(1);

    auto i = 1;
    while (d.length > 0) {
        const auto start   = d.offset;
        auto       subtree = d.add_item(-1, "Extended emergency number #%u", i++);
        use_tree   ut(d, subtree);

        auto length = static_cast< int >(d.uint8());
        n           = d.add_item(1, &hf_ext_emerge_num_len, enc::be);
        d.step(1);

        if (length > 0) {
            n = d.add_item(length, &hf_emerge_num, enc::be);
            d.step(length);
        }

        length = d.uint8();
        n      = d.add_item(1, &hf_ext_emerge_sub_serv_field_len, enc::be);
        d.step(1);

        if (length > 0) {
            n = d.add_item(length, &hf_emm_emerg_num_list_sub_svc_field, enc::be);
            d.step(length);
        }
        subtree->set_length(d.offset - start);
    }

    unused(i);
    return uc.length;
}
