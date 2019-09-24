set(BASE_SRCS base.cc
        ber.cc
        ber.hh
        charsets.cc
        dissector.cc
        e212.cc
        e212_mcc_mnc.cc
        field_meta.cc
        field_meta.hh
        formats.cc
        packet_info.hh
        proto.cc
        proto.hh
        range_string.hh
        tree_meta.hh
        tvbuff.hh
        val_string.hh)

add_library(nas-nr-base ${BASE_SRCS})