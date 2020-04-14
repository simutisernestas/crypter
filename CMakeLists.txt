cmake_minimum_required(VERSION 3.15)
project(letscode)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

add_executable(letscode main.cpp src/Crypter.cpp)

target_include_directories(letscode PRIVATE
        ${CMAKE_SOURCE_DIR}/src/include
        ${CMAKE_SOURCE_DIR}/lib/cryptopp
        ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(letscode
        stdc++fs
        ${CMAKE_SOURCE_DIR}/lib/libcryptopp.a
        ${CMAKE_SOURCE_DIR}/lib/test.a
        ${CMAKE_THREAD_LIBS_INIT})