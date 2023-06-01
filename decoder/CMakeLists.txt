cmake_minimum_required(VERSION 3.16.3)

project(decoder)

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")

include_directories(include)

set(SRCS src/main.c src/lpc.c src/lpc_data.c)
set(LIBS m dl)

add_compile_options(-Wall -fPIC)

add_executable(decoder_test ${SRCS})
target_link_libraries(decoder_test ${LIBS})
