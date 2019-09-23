set(COMMON_SRCS additional_information.cc
        ber.cc
        charsets.cc
        core.cc
        dissect_mm_msg.cc
        dissect_mm_msg_sup.cc
        dissect_nas5g.cc
        dissect_nas5g_sup.cc
        dissector.cc
        dissect_sm_msg.cc
        dnn.cc
        e212.cc
        e212_mcc_mnc.cc
        eap.cc
        field_meta.cc
        formats.cc
        gprs_timer2.cc
        gprs_timer3.cc
        gprs_timer.cc
        gsm.cc
        intra_n1_mode_nas_container.cc
        mcc_mnc.cc
        n1_mode_s1_mode_nas_container.cc
        nas_decrypt.cc
        proto.cc
        s1_mode_n1_mode_nas_container.cc
        s_nssai.cc)

set(COMMON_HEADERS ber.hh
        common.hh
        config.hh
        core.hh
        description.hh
        dissect_mm_msg.hh
        dissect_nas5g.hh
        dissect_sm_msg.hh
        eps.hh
        expert_meta.hh
        field_meta.hh
        gsm.hh
        nas-nr-compiler-detection.hh
        packet_info.hh
        proto.hh
        range_string.hh
        tree_meta.hh
        tvbuff.hh
        val_string.hh
        )

add_library(nas-nr-common ${COMMON_SRCS} ${COMMON_HEADERS})
# set_property(TARGET nas-nr-common PROPERTY POSITION_INDEPENDENT_CODE TRUE)