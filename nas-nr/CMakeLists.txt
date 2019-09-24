
add_subdirectory(common)
add_subdirectory(sm)
add_subdirectory(mm)
add_subdirectory(base)

set(NASNR_SRCS nas-nr.cc nas-nr.hh)

add_library(nas-nr ${NASNR_SRCS})

target_link_libraries(nas-nr nas-nr-base nas-nr-common nas-nr-sm nas-nr-mm)