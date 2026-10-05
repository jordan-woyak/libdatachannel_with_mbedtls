cmake_minimum_required(VERSION 3.20)
project(libdatachannel_with_mbedtls LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

add_compile_definitions(MBEDTLS_SSL_DTLS_SRTP)

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
#add_library(MbedTLS::MbedTLS INTERFACE IMPORTED)
#add_library(MbedTLS::MBedTLS ALIAS mbedtls)

#add_library(MbedTLS::MbedTLS ALIAS MbedTLS::mbedtls)

if(TARGET mbedtls)
   message(STATUS "got MbedTLS")
else()
   message(STATUS "don't got MbedTLS")
endif()

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

set(MbedTLS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/mbedtls-src/include)

FetchContent_Declare(
  libdatachannel
  GIT_REPOSITORY https://github.com/paullouisageneau/libdatachannel.git
  # v0.24.6
  GIT_TAG 6b1e2e620f1e37f0eafeee702eaea0043cb305fd
  GIT_SHALLOW TRUE
  PATCH_COMMAND
    git apply "${CMAKE_CURRENT_SOURCE_DIR}/srtpCMakeLists.patch"
)
FetchContent_MakeAvailable(libdatachannel)

# target_include_directories(datachannel PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/mbedtls-src/include
# )

#target_link_libraries(datachannel PRIVATE mbedtls)

#target_compile_definitions(libdatachannel PRIVATE MBEDTLS_SSL_DTLS_SRTP)

target_link_libraries(srtp2 PRIVATE MbedTLS::MbedTLS)
#target_link_libraries(srtp2 PRIVATE MbedTLS::mbedx509)
#target_link_libraries(srtp2 PRIVATE MbedTLS::mbedcrypto)
#target_link_libraries(libsrtp2 MbedTLS::MbedTLS)
#target_link_libraries(MbedTLS::MbedCrypto ALIAS mbedcrypto)
#target_link_libraries(MbedTLS::MbedX509 ALIAS mbedx509)

add_executable(libdatachannel_with_mbedtls main.cpp)

#  target_link_libraries(datachannel PRIVATE
#    mbedcrypto
#    mbedtls
#    mbedx509
#  )

target_link_libraries(libdatachannel_with_mbedtls PRIVATE
  LibDataChannel::LibDataChannel
  mbedtls
)
