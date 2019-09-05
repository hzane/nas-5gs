#include "../dissect_sm_msg.hh"

using namespace sm;
using namespace nas;

/* 9.11.4.8 Mapped EPS bearer contexts */
int dissect_eps_param(dissector d, int i, context* ctx) {
    auto     start   = d.offset;
    auto     subtree = d.add_item(-1, "EPS parameter %u", i);
    use_tree ut(d, subtree);

    /* EPS parameter identifier */
    uint32_t param_id = (uint32_t) d.uint8();
    d.add_item(1, &hf_sm_mapd_eps_b_cont_num_eps_param_id, enc::be);
    d.step(1);

    /*length of the EPS parameter contents field */
    int length = (int) d.uint8();
    d.add_item(1, &hf_sm_length, enc::be);
    d.step(1);

    subtree->set_length(length + 2);
    /*length of the EPS parameter contents field */
    switch (param_id) {
    case 1: /* 01H (Mapped EPS QoS parameters) */
    case 2: /* 02H (Mapped extended EPS QoS parameters) */
    case 3: /* 03H (Traffic flow template)*/
    case 4: /* 04H (APN-AMBR) */
    case 5: /* 05H (extended APN-AMBR). */
    default:
        d.add_item(length, &hf_sm_mapd_eps_b_cont_eps_param_cont, enc::be);
        d.step(length);
    }
    return d.offset - start;
}

// Mapped EPS  bearer contexts     9.11.4.8
int sm::dissect_mapped_eps_b_cont(dissector d, context* ctx) {
    const use_context uc(ctx, "mapped-eps-bearer-contexts", d, 0);
    
    static const field_meta* mapd_eps_b_cont_flags[] = {
        &hf_sm_mapd_eps_b_cont_opt_code,
        &hf_spare_b5,
        &hf_sm_mapd_eps_b_cont_e,
        &hf_sm_mapd_eps_b_cont_num_eps_parms,
        nullptr,
    };

    static const field_meta* mapd_eps_b_cont_flags_modify[] = {
        &hf_sm_mapd_eps_b_cont_opt_code,
        &hf_spare_b5,
        &hf_sm_mapd_eps_b_cont_e_mod,
        &hf_sm_mapd_eps_b_cont_num_eps_parms,
        nullptr,
    };
    auto n = 1;
    /* The IE contains a number of Mapped EPS bearer context */
    while (d.length > 0) {
        /* Figure 9.11.4.5.2: Mapped EPS bearer context */
        auto     subtree = d.add_item(-1, "Mapped EPS bearer context %u", n);
        use_tree ut(d, subtree);

        /* EPS bearer identity */
        d.add_item(1, &hf_sm_mapd_eps_b_cont_id, enc::be);
        d.step(1);

        /* Length of Mapped EPS bearer context*/
        int length = (int) d.ntohs();
        d.add_item(2, &hf_sm_length, enc::be);
        d.step(2);

        subtree->set_length(length + 3);
        /*     8   7      6    5   4  3  2  1          */
        /* operation code | spare |  E | number of EPS params     */

        auto nep      = d.tvb->uint8(d.offset);
        auto opt_code = (nep & 0xc0u) >> 6u;
        nep           = nep & 0x0f;

        /* operation code = 3 Modify existing EPS bearer */
        if (opt_code == 3) {
            d.add_bits(mapd_eps_b_cont_flags_modify);
        } else {
            d.add_bits(mapd_eps_b_cont_flags);
        }
        d.step(1);

        /* EPS parameters list */
        auto i = 1;
        while (nep > 0) {
            auto consumed = dissect_eps_param(d, i, ctx);
            d.step(consumed);
            --nep;
            ++i;
        }
        ++n;
    }
    return uc.length;
}
