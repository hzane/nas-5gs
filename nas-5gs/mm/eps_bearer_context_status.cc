#include "../dissect_mm_msg.hh"


const true_false_string eps_emm_ebi_vals = {
    "BEARER CONTEXT-ACTIVE",
    "BEARER CONTEXT-INACTIVE",
};

const field_meta hf_eps_emm_ebi7 = {
    "EBI(7)",
    "nas_eps.emm.ebi7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &eps_emm_ebi_vals,
    nullptr,
    0x80,
};
const field_meta hf_eps_emm_ebi6 = {
    "EBI(6)",
    "nas_eps.emm.ebi6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &eps_emm_ebi_vals,
    nullptr,
    0x40,
};
const field_meta hf_eps_emm_ebi5 = {
    "EBI(5)",
    "nas_eps.emm.ebi5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &eps_emm_ebi_vals,
    nullptr,
    0x20,
};
const field_meta hf_eps_emm_ebi4 = {
    "EBI(4)",
    "nas_eps.emm.ebi4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &eps_emm_ebi_vals,
    nullptr,
    0x10,
};
const field_meta hf_eps_emm_ebi3 = {
    "EBI(3)",
    "nas_eps.emm.ebi3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &eps_emm_ebi_vals,
    nullptr,
    0x08,
};
const field_meta hf_eps_emm_ebi2 = {
    "EBI(2)",
    "nas_eps.emm.ebi2",
    ft::ft_boolean,
    8,
    nullptr,
    &eps_emm_ebi_vals,
    nullptr,
    0x04,
};
const field_meta hf_eps_emm_ebi1 = {
    "EBI(1)",
    "nas_eps.emm.ebi1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &eps_emm_ebi_vals,
    nullptr,
    0x02,
};
const field_meta hf_eps_emm_ebi0 = {
    "EBI(0) spare",
    "nas_eps.emm.ebi0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x01,
};

const field_meta hf_eps_emm_ebi15 = {
    "EBI(15)",
    "nas_eps.emm.ebi15",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &eps_emm_ebi_vals,
    nullptr,
    0x80,
};
const field_meta hf_eps_emm_ebi14 = {
    "EBI(14)",
    "nas_eps.emm.ebi14",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &eps_emm_ebi_vals,
    nullptr,
    0x40,
};
const field_meta hf_eps_emm_ebi13 = {
    "EBI(13)",
    "nas_eps.emm.ebi13",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &eps_emm_ebi_vals,
    nullptr,
    0x20,
};
const field_meta hf_eps_emm_ebi12 = {
    "EBI(12)",
    "nas_eps.emm.ebi12",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &eps_emm_ebi_vals,
    nullptr,
    0x10,
};
const field_meta hf_eps_emm_ebi11 = {
    "EBI(11)",
    "nas_eps.emm.ebi11",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &eps_emm_ebi_vals,
    nullptr,
    0x08,
};
const field_meta hf_eps_emm_ebi10 = {
    "EBI(10)",
    "nas_eps.emm.ebi10",
    ft::ft_boolean,
    8,
    nullptr,
    &eps_emm_ebi_vals,
    nullptr,
    0x04,
};
const field_meta hf_eps_emm_ebi9 = {
    "EBI(9)",
    "nas_eps.emm.ebi9",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &eps_emm_ebi_vals,
    nullptr,
    0x02,
};
const field_meta hf_eps_emm_ebi8 = {
    "EBI(8)",
    "nas_eps.emm.ebi8",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &eps_emm_ebi_vals,
    nullptr,
    0x01,
};

/*  9.11.3.59  EPS bearer context status
 * See subclause 9.9.2.1 in 3GPP TS 24.301 [15]. */
int mm::dissect_eps_bearer_context_status(dissector d, context* ctx) {
    const use_context uc(ctx, "eps-bearer-context-status", d, 0);

    const field_meta* flags[] = {
        &hf_eps_emm_ebi7,
        &hf_eps_emm_ebi6,
        &hf_eps_emm_ebi5,
        &hf_eps_emm_ebi4,
        &hf_eps_emm_ebi3,
        &hf_eps_emm_ebi2,
        &hf_eps_emm_ebi1,
        &hf_eps_emm_ebi0,
        nullptr,
    };
    const field_meta* flags2[] = {
        &hf_eps_emm_ebi15,
        &hf_eps_emm_ebi14,
        &hf_eps_emm_ebi13,
        &hf_eps_emm_ebi12,
        &hf_eps_emm_ebi11,
        &hf_eps_emm_ebi10,
        &hf_eps_emm_ebi9,
        &hf_eps_emm_ebi8,
        nullptr,
    };
    /* EBI(7)  EBI(6)  EBI(5)  EBI(4)  EBI(3)  EBI(2)  EBI(1) EBI(0) octet 3 */
    /* EBI(0): Bit 1 of octet 3 is spare and shall be coded as zero. */
    d.add_bits(flags);
    d.step(1);

    /* EBI(15) EBI(14) EBI(13) EBI(12) EBI(11) EBI(10) EBI(9) EBI(8) octet 4 */
    d.add_bits(flags2);
    d.step(1);

    return 2;
}
