#include "../dissect_mm_msg.hh"


/* 9.11.3.15	Authentication parameter AUTN
 * [9] 10.5.3.1.1 Authentication Parameter AUTN (UMTS and EPS authentication challenge) */
int mm::dissect_auth_parameter_autn(dissector d, context* ctx) {
    const use_context uc(ctx, "auth-param-autn", d, 0);

    // See subclause 10.5.3.1 in 3GPP TS 24.008 [12].    
    NASNR_AUTO(proto_node*) subtree = d.add_item(d.length, &hf_dtap_autn, enc::na);
    use_tree   ut(d, subtree);

    (void) d.add_item(6, &hf_dtap_autn_sqn, enc::be);
    d.step(6);

    (void) d.add_item(2, &hf_dtap_autn_amf, enc::be);
    d.step(2);

    (void) d.add_item(8, &hf_dtap_autn_mac, enc::be);
    d.step(8);

    return uc.length;
}
