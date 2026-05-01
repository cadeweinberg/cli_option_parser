# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.10)

project(cli_option_parser
  LANGUAGES C
  VERSION 0.1.0
  DESCRIPTION "A simple C library for parsing command-line options"
  HOMEPAGE_URL "https://github.com/cade-weinberg/cli_option_parser"
)

set(COP_BASE_DIR    ${CMAKE_CURRENT_SOURCE_DIR})
set(COP_INCLUDE_DIR ${COP_BASE_DIR}/include)
set(COP_SOURCE_DIR  ${COP_BASE_DIR}/src)
set(COP_TEST_DIR    ${COP_BASE_DIR}/test)
set(COP_CMAKE_DIR   ${COP_BASE_DIR}/cmake)

include(CTest)
include(${COP_CMAKE_DIR}/third-party.cmake)

add_library(cli_option_parser)
target_sources(cli_option_parser
  PRIVATE
    ${COP_SOURCE_DIR}/cli_option_parser.c
  PUBLIC
    ${COP_INCLUDE_DIR}/cli_option_parser.h
)
target_include_directories(cli_option_parser
  PUBLIC
    ${COP_INCLUDE_DIR}
)
target_compile_options(cli_option_parser
  PRIVATE
  $<$<C_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -Werror>
)

add_subdirectory(test)
