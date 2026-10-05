cmake_minimum_required(VERSION 3.20)
project(libdatachannel_with_mbedtls LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(MBEDTLS_CONFIG_FILE "mbedtls_config.h")

FetchContent_Declare(
  MbedTLS
  GIT_REPOSITORY https://github.com/Mbed-TLS/mbedtls.git
  # v3.6.7
  GIT_TAG 068ff080b369adfac81509f9b57b2afabaf82dc5
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(MbedTLS)

add_library(MbedTLS::MbedTLS INTERFACE IMPORTED)
target_link_libraries(MbedTLS::MbedTLS INTERFACE
    MbedTLS::mbedtls
    MbedTLS::mbedx509
    MbedTLS::mbedcrypto
)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

set(USE_GNUTLS OFF CACHE BOOL "" FORCE)
set(USE_MBEDTLS ON CACHE BOOL "" FORCE)
set(USE_OPENSSL OFF CACHE BOOL "" FORCE)

set(PREFER_SYSTEM_LIB OFF CACHE BOOL "" FORCE)
set(USE_SYSTEM_SRTP OFF CACHE BOOL "" FORCE)
set(USE_SYSTEM_JUICE OFF CACHE BOOL "" FORCE)
set(USE_SYSTEM_USRSCTP OFF CACHE BOOL "" FORCE)
set(USE_SYSTEM_PLOG OFF CACHE BOOL "" FORCE)
set(USE_SYSTEM_JSON OFF CACHE BOOL "" FORCE)

set(NO_WEBSOCKET ON CACHE BOOL "" FORCE)
set(NO_MEDIA OFF CACHE BOOL "" FORCE)
set(NO_EXAMPLES ON CACHE BOOL "" FORCE)
set(NO_TESTS ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  libdatachannel
  GIT_REPOSITORY https://github.com/paullouisageneau/libdatachannel.git
  # v0.24.6
  GIT_TAG 6b1e2e620f1e37f0eafeee702eaea0043cb305fd
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(libdatachannel)

add_executable(h264_server main.cpp)
