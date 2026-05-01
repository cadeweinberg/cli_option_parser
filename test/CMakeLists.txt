# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.10)

add_executable(cli_option_parser_tests)
target_sources(cli_option_parser_tests
  PRIVATE
    ${COP_TEST_DIR}/test_cli_option_parser.c
)
target_link_libraries(cli_option_parser_tests
  PRIVATE
    cli_option_parser
    cmocka
)

add_test(NAME cli_option_parser_tests
         COMMAND cli_option_parser_tests)