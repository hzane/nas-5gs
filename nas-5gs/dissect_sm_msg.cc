#include "dissect_sm_msg.hh"
#include "dissect_nas5g.hh"
#include "ts24007.hh"
#include "common/common.hh"

using namespace cmn;
using namespace nas;
using namespace sm;

/* 8.3 5GS session management messages */



// EAP message 9.11.2.2
int sm::dissect_eap_msg(dissector d, context* ctx) {
    return cmn::dissect_eap_msg(d, ctx);
}





