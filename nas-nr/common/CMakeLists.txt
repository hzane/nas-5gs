set(COMMON_SRCS additional_information.cc
        common.hh
        config.hh
        core.cc
        core.hh
        description.hh
        dissect_mm_msg.cc
        dissect_mm_msg.hh
        dissect_mm_msg_sup.cc
        dissect_nas5g.cc
        dissect_nas5g.hh
        dissect_nas5g_sup.cc
        dissect_sm_msg.cc
        dissect_sm_msg.hh
        dnn.cc
        e212_mcc_mnc.cc
        eap.cc
        eps.hh
        expert_meta.hh
        gprs_timer.cc
        gprs_timer2.cc
        gprs_timer3.cc
        gsm.cc
        gsm.hh
        intra_n1_mode_nas_container.cc
        mcc_mnc.cc
        n1_mode_s1_mode_nas_container.cc
        nas-nr-compiler-detection.hh
        nas_decrypt.cc
        s1_mode_n1_mode_nas_container.cc
        s_nssai.cc
        )

set(COMMON_HEADERS common.hh
        config.hh
        core.hh
        description.hh
        dissect_mm_msg.hh
        dissect_nas5g.hh
        dissect_sm_msg.hh
        eps.hh
        expert_meta.hh
        gsm.hh
        nas-nr-compiler-detection.hh
        )

add_library(nas-nr-common ${COMMON_SRCS} ${COMMON_HEADERS})
# set_property(TARGET nas-nr-common PROPERTY POSITION_INDEPENDENT_CODE TRUE)