#include "../common/ber.hh"
#include "../common/definitions.hh"
#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 9.11.3.24    EPS NAS message container */
result_t dissect_eps_nas_msg_container(dissector d, context* ctx, eps_nas_message_t* ret) {
    return de_octet(d, ctx, ret);
}
