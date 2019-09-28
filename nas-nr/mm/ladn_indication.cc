#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

/*  9.11.3.29    LADN indication  */
int mm::dissect_ladn_indication(dissector d, context* ctx) {
    const use_context uc(ctx, "ladn-indication", d, 0);

    auto i = 1;
    while (d.length > 0) {
        auto     subtree = d.add_item(2, formats("LADN DNN value %u", i++));
        use_tree ut(d, subtree);
        /*LADN DNN value is coded as the length and value part of DNN information element
         * as specified in subclause 9.11.2.1A starting with the second octet*/
        const int length = static_cast< int >(d.uint8());
        d.step(1);

        const auto consumed = cmn::dissect_dnn(d.slice(length), ctx);
        d.step(consumed);
        subtree->set_length(length + 1);
    }
    return uc.length;
}


struct ladn_indication_t {
    std::vector< payload_t > dnn;
};
