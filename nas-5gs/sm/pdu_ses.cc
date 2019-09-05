#include "../config.hh"
#include "../dissect_sm_msg.hh"

const true_false_string tfs_abo = {
    "The back-off timer is applied in all PLMNs.",
    "The back-off timer is applied in the registered PLMN.",
};
const field_meta sm::hf_abo = {
    "ABO",
    "",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_abo,
    nullptr,
    0,
};





