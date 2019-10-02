#include "../common/dissector.hh"
#include "../common/use_context.hh"

int dissect_pld_container_entry(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "pld-content-entry",-1);

    return 0;
}

/*  9.11.3.39    Payload container */
int dissect_payload_container(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "pld-content", 0);

    return uc.length;
}

/* UPDP */
/* D.6.1 UE policy delivery service message type */
int dissect_ue_policy_delivery_procedure(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "updp", 0);
    return uc.length;
}

int dissect_optional_ie(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "optional-ie", -1);


    return d.offset - uc.offset;
}
