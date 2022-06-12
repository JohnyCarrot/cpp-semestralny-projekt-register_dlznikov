cmake_minimum_required(VERSION 3.6.2)
project(evidencia)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads)

set(SOURCE_FILES
        evidencia.cpp
        main.cpp

        #Pre umoznenie testov treba odkomentovat od tadeto po posledny include (vratane)
#        testy.cpp
#
#
#        GoogleTest/gtest-death-test.cc
#        GoogleTest/gtest-filepath.cc
#        GoogleTest/gtest-port.cc
#        GoogleTest/gtest-printers.cc
#        GoogleTest/gtest-test-part.cc
#        GoogleTest/gtest-typed-test.cc
#        GoogleTest/gtest.cc
#        GoogleTest/gtest_main.cc)
#
#include_directories(GoogleTest
        )
add_executable(evidencia ${SOURCE_FILES})
#target_link_libraries(evidencia ${CMAKE_THREAD_LIBS_INIT})
add_custom_command(TARGET evidencia PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        ${SOURCE_FILES}/evidencia.txt
        $<TARGET_FILE_DIR:evidencia>
        VERBATIM)

