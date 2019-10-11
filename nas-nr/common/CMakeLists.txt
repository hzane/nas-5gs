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
    eap.cc
    ies.hh
    protocol.hh
    messages.hh
    nas.hh
    packet.hh
    use_context.cc
    use_context.hh
    ies.cc)

add_library(nas-nr-common ${BASE_SRCS})