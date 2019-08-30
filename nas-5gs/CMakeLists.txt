cmake_minimum_required(VERSION 3.14)
project(nas-5gs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS  "-fms-extensions -Wno-extern-initializer")
set(CMAKE_C_FLAGS "-fms-extensions")

aux_source_directory(. NAS_5GS_SRCS)
aux_source_directory(./mm NAS_5GS_MM_SRCS)
aux_source_directory(./sm NAS_5GS_SM_SRCS)
set(HEADERS val_string.hh tree_meta.hh range_string.hh expert_meta.hh gsm.hh eps.hh)
add_executable(nas-5gs ${NAS_5GS_SRCS} ${NAS_5GS_MM_SRCS} ${NAS_5GS_SM_SRCS} ${HEADERS})