cmake_minimum_required(VERSION 3.8.2)
project(assignment2 VERSION 0.1.0 LANGUAGES C CXX)

if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  message(FATAL_ERROR "Out-of-source builds only. Try: cmake -S . -B build-a2")
endif()

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(set_common_warnings tgt)
  if(MSVC)
    target_compile_options(${tgt} PRIVATE /W4)
  else()
    target_compile_options(${tgt} PRIVATE -Wall -Wextra -Wpedantic)
  endif()
endfunction()

add_library(assignment2_core STATIC
  src/matrix.cpp
  src/logger.cpp
)

target_include_directories(assignment2_core
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_common_warnings(assignment2_core)

add_executable(assignment2 src/main.cpp)
target_link_libraries(assignment2 PRIVATE assignment2_core)
set_common_warnings(assignment2)

include(CTest)
enable_testing()

add_library(assignment2_unity STATIC tests/vendor/unity/unity.c)
target_include_directories(assignment2_unity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests/vendor/unity)
set_common_warnings(assignment2_unity)

add_executable(assignment2_tests tests/unit_tests.cpp)
target_link_libraries(assignment2_tests PRIVATE assignment2_core assignment2_unity)
target_include_directories(assignment2_tests PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/tests
)
set_common_warnings(assignment2_tests)

add_test(NAME assignment2_tests COMMAND assignment2_tests)
