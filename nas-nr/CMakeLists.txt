
add_subdirectory(common)
add_subdirectory(sm)
add_subdirectory(mm)

set(NASNR_SRCS nas-nr.cc nas-nr.hh)

add_library(nas-nr SHARED ${NASNR_SRCS})

target_link_libraries(nas-nr nas-nr-common nas-nr-sm nas-nr-mm)