cmake_minimum_required(VERSION 3.14)
project(security C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_library(security
        kdf.c
        key_nas_deriver.c
        key_nas_encryption.c
        nas_stream_nea1.c
        nas_stream_nea2.c
        rijndael.c
        rijndael.h
        secu_defs.h
        security_types.h
        snow3g.c
        snow3g.h
        zuc.c
        zuc.h)
