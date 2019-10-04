set(BASE_SRCS ber.cc
        ber.hh
        context.hh
        core.cc
        core.hh
        definitions.hh
        diag.cc
        dissector.cc
        dissector.hh
        dissects.cc
        dnn.cc
        e212.cc
        eap.cc
        ies.hh
        intra_n1_mode_nas_container.cc
        protocol.hh
        messages.hh
        n1_mode_s1_mode_nas_container.cc
        nas.hh
        packet.hh
        s1_mode_n1_mode_nas_container.cc
        s_nssai.cc
        use_context.cc
        use_context.hh
        )

add_library(nas-nr-common ${BASE_SRCS})