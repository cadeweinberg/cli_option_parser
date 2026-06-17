# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.22)

project(cli_option_parser
  LANGUAGES C
  VERSION 0.1.1
  DESCRIPTION "A simple C library for parsing command-line options"
  HOMEPAGE_URL "https://github.com/cade-weinberg/cli_option_parser"
)

set(COP_BASE_DIR    ${CMAKE_CURRENT_SOURCE_DIR})
set(COP_INCLUDE_DIR ${COP_BASE_DIR}/include)
set(COP_SOURCE_DIR  ${COP_BASE_DIR}/src)
set(COP_TEST_DIR    ${COP_BASE_DIR}/test)
set(COP_CMAKE_DIR   ${COP_BASE_DIR}/cmake)
set(COP_BINARY_DIR  ${CMAKE_CURRENT_BINARY_DIR})

include(CTest)
include(GenerateExportHeader)
include(${COP_CMAKE_DIR}/third-party.cmake)

add_library(cli_option_parser)
target_sources(cli_option_parser
  PRIVATE
    ${COP_SOURCE_DIR}/cli_option_parser.c
  PUBLIC
    ${COP_INCLUDE_DIR}/cli_option_parser.h
    ${COP_INCLUDE_DIR}/cli_option_parser_export.h
)
target_include_directories(cli_option_parser
  PUBLIC
    ${COP_INCLUDE_DIR}
)
target_compile_options(cli_option_parser
  PRIVATE
  # NOTE: cmocka (the testing library) has a few integer narrowing 
  # warnings which the msvc compiler rightfully notifies us of.
  # however it causes CI/CD to fail, and its an error in an upstream 
  # dependency. Which may be fixed in a future release. Or we could 
  # fix it ourselves. So, as a quick patch, we will turn off /WX
  #$<$<C_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<C_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -Werror>
)
generate_export_header(
    cli_option_parser
    EXPORT_FILE_NAME "../../include/cli_option_parser_export.h"
)

add_subdirectory(test)
