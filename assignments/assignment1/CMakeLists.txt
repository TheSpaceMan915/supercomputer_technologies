cmake_minimum_required(VERSION 3.8.2)
project(assignment1 VERSION 0.1.0 LANGUAGES C CXX)
if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  message(FATAL_ERROR "Out-of-source builds only. Use: cmake -S . -B build-assignment1")
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
add_library(assignment1_core
  src/pi.cpp
  src/logger.cpp
)
target_include_directories(assignment1_core
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
set_common_warnings(assignment1_core)
add_executable(assignment1 src/main.cpp)
target_link_libraries(assignment1 PRIVATE assignment1_core)
set_common_warnings(assignment1)
include(CTest)
if(BUILD_TESTING)
  add_library(unity STATIC tests/vendor/unity/unity.c)
  target_include_directories(unity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests/vendor/unity)
  set_common_warnings(unity)
  add_executable(assignment1_tests tests/unit_tests.cpp)
  target_link_libraries(assignment1_tests PRIVATE assignment1_core unity)
  target_include_directories(assignment1_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
  )
  set_common_warnings(assignment1_tests)
  add_test(NAME assignment1_tests COMMAND assignment1_tests)
endif()
