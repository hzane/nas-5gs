#include "../common/definitions.hh"
#include "../common/dissector.hh"
#include "../common/use_context.hh"
#include "../nas-nr.hh"

/* 9.11.3.33    NAS message container */
result_t dissect_nas_message_container(dissector            d,
                                       context*             ctx,
                                       nas_message_plain_t* ret) {
    /* The purpose of the NAS message container IE is to
     * encapsulate a plain 5GS NAS message. */
    /* a NAS message without NAS security header */
    return de_nas_plain(d, ctx, ret);
}
