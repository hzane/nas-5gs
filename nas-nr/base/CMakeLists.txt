set(BASE_SRCS base.cc
        nas-nr-compiler-detection.hh
        common.hh
        config.hh
        core.cc
        core.hh        ber.cc
        ber.hh
        charsets.cc
        dissector.cc
        e212.cc
        field_meta.cc
        field_meta.hh
        formats.cc
        packet.hh
        proto.cc
        proto.hh
        r_string.hh
        tree_meta.hh
        bufview.hh
        v_string.hh)

add_library(nas-nr-base ${BASE_SRCS})