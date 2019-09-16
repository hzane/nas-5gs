cmake_minimum_required(VERSION 3.14)
project(nas-nr)

include(WriteCompilerDetectionHeader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

# set(CMAKE_CXX_FLAGS  "-fms-extensions -Wno-extern-initializer")
# set(CMAKE_C_FLAGS "-fms-extensions")

#write_compiler_detection_header (
#        FILE nas-nr-compiler-detection.hh
#        PREFIX NASNA
#        COMPILERS GNU MSVC Clang
#        FEATURES cxx_variadic_templates c_restrict cxx_constexpr cxx_final cxx_noexcept cxx_override cxx_extern_templates cxx_deleted_functions cxx_alignas cxx_nullptr cxx_alignof cxx_static_assert cxx_attribute_deprecated cxx_defaulted_functions cxx_auto_type
#)

aux_source_directory(. NAS_5GS_SRCS)
list(REMOVE_ITEM NAS_5GS_SRCS ./pch.h ./nas-nr.cc ./dllmain.cc )
aux_source_directory(./mm NAS_5GS_MM_SRCS)
aux_source_directory(./sm NAS_5GS_SM_SRCS)
aux_source_directory(./common NAS_5GS_COMMON_SRCS)
set(HEADERS val_string.hh tree_meta.hh range_string.hh expert_meta.hh gsm.hh eps.hh )

aux_source_directory(. NASNR_API_SRCS)
list(REMOVE_ITEM NASNR_API_SRCS ./nas-nr-demo.cc ./dllmain.cc)
add_library(nas-nr-ts24501 SHARED ${NASNR_API_SRCS} ${NAS_5GS_MM_SRCS} ${NAS_5GS_SM_SRCS} ${NAS_5GS_COMMON_SRCS} ${HEADERS})
target_compile_definitions(nas-nr-ts24501 PRIVATE NASNRTS24501_EXPORTS)

add_executable(nas-nr-demo ${NAS_5GS_SRCS} ${NAS_5GS_MM_SRCS} ${NAS_5GS_SM_SRCS} ${NAS_5GS_COMMON_SRCS} ${HEADERS})
target_link_libraries(nas-nr-demo PUBLIC stdc++fs)
