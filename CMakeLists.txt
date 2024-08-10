cmake_minimum_required(VERSION 3.13)

project(rk3588_encode_test VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(rk3588_encode_test main.cpp)

target_include_directories(rk3588_encode_test PRIVATE ${CMAKE_SOURCE_DIR}/include)

set(VENC_LIBRARY ${CMAKE_SOURCE_DIR}/lib/libvenc.a)

add_library(venc STATIC IMPORTED)
set_target_properties(venc PROPERTIES
    IMPORTED_LOCATION ${VENC_LIBRARY}
)



target_link_libraries(rk3588_encode_test PRIVATE venc rockchip_mpp pthread)
