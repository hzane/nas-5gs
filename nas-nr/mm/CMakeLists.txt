
set(MM_SRCS  abba.cc
    mm_dissects.hh
    mm_element_meta.hh
    mm_field_meta.hh    )

add_library(nas-nr-mm ${MM_SRCS})
# set_property(TARGET nas-nr-mm PROPERTY POSITION_INDEPENDENT_CODE TRUE)