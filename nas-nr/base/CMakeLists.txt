set(BASE_SRCS base.cc
        ber.cc
        ber.hh
        charsets.cc
        dissector.cc
        e212.cc
        field_meta.cc
        field_meta.hh
        formats.cc
        packet_info.hh
        proto.cc
        proto.hh
        r_string.hh
        tree_meta.hh
        bufview.hh
        v_string.hh)

add_library(nas-nr-base ${BASE_SRCS})