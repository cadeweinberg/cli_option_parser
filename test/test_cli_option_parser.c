// SPDX-License-Identifier: MIT

#include "cli_option_parser.h"
#include <cmocka.h>

static const CliOption options[] = {
    {
        .name = "help",
        .description = "Show this help message and exit.",
        .environment_variable = NULL,
        .argument_kind = OPTION_ARGUMENT_NONE,
        .short_name = 'h',
    },
    {
        .name = "version",
        .description = "Show version information and exit.",
        .environment_variable = NULL,
        .argument_kind = OPTION_ARGUMENT_NONE,
        .short_name = 'v',
    },
    {
        .name = "output",
        .description = "Specify the output file.",
        .environment_variable = "OUTPUT_FILE",
        .argument_kind = OPTION_ARGUMENT_REQUIRED,
        .short_name = 'o',
    },
    {
        .name = "optimize",
        .description = "Enable optimization.",
        .environment_variable = "OPTIMIZE",
        .argument_kind = OPTION_ARGUMENT_OPTIONAL,
        .short_name = 'O',
    },
    {
        .name = "jflag",
        .description = "An interesting flag.",
        .environment_variable = NULL,
        .argument_kind = OPTION_ARGUMENT_NONE,
        .short_name = 'j',
    },
    {
        .name = "kflag",
        .description = "An interesting flag.",
        .environment_variable = NULL,
        .argument_kind = OPTION_ARGUMENT_NONE,
        .short_name = 'k',
    },
    {
        .name = "lflag",
        .description = "An interesting flag.",
        .environment_variable = NULL,
        .argument_kind = OPTION_ARGUMENT_NONE,
        .short_name = 'l',
    }};

static const size_t options_length = sizeof(options) / sizeof(options[0]);

static void test_cli_option_parser_init(void **state) {
  (void)state; // Unused
  CliOptionParser parser;
  cli_option_parser_init(&parser, options, options_length);
  assert_int_equal(parser.option_index, 1);
  assert_int_equal(parser.suboption_index, 0);
  assert_int_equal(parser.option_count, options_length);
  assert_ptr_equal(parser.options, options);
}

static void
test_cli_option_parser_parse_option_long_argument_none(void **state) {
  (void)state; // Unused
  CliOptionParser parser;
  cli_option_parser_init(&parser, options, options_length);

  int32_t argc = 5;
  char const *argv[] = {"program", "--help", "--version", "--jflag", NULL};

  CliOptionResult result;

  // Parse --help
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'h');
  assert_ptr_equal(result.argument, NULL);

  // Parse --version
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'v');
  assert_ptr_equal(result.argument, NULL);

  // Parse --jflag
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'j');
  assert_ptr_equal(result.argument, NULL);

  // No more options
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_END);
  assert_ptr_equal(result.argument, NULL);
}

static void
test_cli_option_parser_parse_option_long_argument_required(void **state) {
  (void)state; // Unused
  CliOptionParser parser;
  cli_option_parser_init(&parser, options, options_length);

  int32_t argc = 5;
  char const *argv[] = {"program", "--output=output.txt", "--output",
                        "output.txt", NULL};

  CliOptionResult result;

  // Parse --output=output.txt
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'o');
  assert_string_equal(result.argument, "output.txt");

  // Parse --output output.txt
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'o');
  assert_string_equal(result.argument, "output.txt");

  // No more options
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_END);
  assert_ptr_equal(result.argument, NULL);
}

static void test_cli_option_parser_parse_option_long_argument_required_missing(
    void **state) {
  (void)state; // Unused
  CliOptionParser parser;
  cli_option_parser_init(&parser, options, options_length);

  int32_t argc = 3;
  char const *argv[] = {"program", "--output", NULL};

  CliOptionResult result;

  // Parse --output (missing required argument)
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_MISSING_ARGUMENT);
  assert_ptr_equal(result.argument, "output");

  // No more options
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_END);
  assert_ptr_equal(result.argument, NULL);
}

static void
test_cli_option_parser_parse_option_long_argument_optional(void **state) {
  (void)state; // Unused
  CliOptionParser parser;
  cli_option_parser_init(&parser, options, options_length);

  int32_t argc = 4;
  char const *argv[] = {"program", "--optimize=2", "--optimize", NULL};

  CliOptionResult result;

  // Parse --optimize=2
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'O');
  assert_string_equal(result.argument, "2");

  // Parse --optimize (optional argument missing)
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'O');
  assert_ptr_equal(result.argument, NULL);

  // No more options
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_END);
  assert_ptr_equal(result.argument, NULL);
}

static void
test_cli_option_parser_parse_option_long_argument_unrecognized(void **state) {
  (void)state; // Unused
  CliOptionParser parser;
  cli_option_parser_init(&parser, options, options_length);

  int32_t argc = 3;
  char const *argv[] = {"program", "--unknown", NULL};

  CliOptionResult result;

  // Parse --unknown
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_UNRECOGNIZED);
  assert_string_equal(result.argument, "unknown");

  // No more options
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_END);
  assert_ptr_equal(result.argument, NULL);
}

static void
test_cli_option_parser_parse_option_short_argument_none(void **state) {
  (void)state; // Unused
  CliOptionParser parser;
  cli_option_parser_init(&parser, options, options_length);

  int32_t argc = 4;
  char const *argv[] = {"program", "-h", "-v", NULL};

  CliOptionResult result;

  // Parse -h
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'h');
  assert_ptr_equal(result.argument, NULL);

  // Parse -v
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'v');
  assert_ptr_equal(result.argument, NULL);

  // No more options
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_END);
  assert_ptr_equal(result.argument, NULL);
}

static void
test_cli_option_parser_parse_option_short_argument_none_combined(void **state) {
  (void)state; // Unused
  CliOptionParser parser;
  cli_option_parser_init(&parser, options, options_length);

  int32_t argc = 4;
  char const *argv[] = {"program", "-hjkl", "-kljh", NULL};

  CliOptionResult result;

  // Parse -h
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'h');
  assert_ptr_equal(result.argument, NULL);

  // Parse -j
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'j');
  assert_ptr_equal(result.argument, NULL);

  // Parse -k
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'k');
  assert_ptr_equal(result.argument, NULL);

  // Parse -l
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'l');
  assert_ptr_equal(result.argument, NULL);

  // Parse -k
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'k');
  assert_ptr_equal(result.argument, NULL);

  // Parse -l
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'l');
  assert_ptr_equal(result.argument, NULL);

  // Parse -j
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'j');
  assert_ptr_equal(result.argument, NULL);

  // Parse -h
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'h');
  assert_ptr_equal(result.argument, NULL);

  // No more options
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_END);
  assert_ptr_equal(result.argument, NULL);
}

static void
test_cli_option_parser_parse_option_short_argument_required(void **state) {
  (void)state; // Unused
  CliOptionParser parser;
  cli_option_parser_init(&parser, options, options_length);

  int32_t argc = 4;
  char const *argv[] = {"program", "-ooutput.txt", "-o", "output.txt", NULL};

  CliOptionResult result;

  // Parse -ooutput.txt
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'o');
  assert_string_equal(result.argument, "output.txt");

  // Parse -o output.txt
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, 'o');
  assert_string_equal(result.argument, "output.txt");

  // No more options
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_END);
  assert_ptr_equal(result.argument, NULL);
}

static void test_cli_option_parser_parse_option_short_argument_required_missing(
    void **state) {
  (void)state; // Unused
  CliOptionParser parser;
  cli_option_parser_init(&parser, options, options_length);

  int32_t argc = 3;
  char const *argv[] = {"program", "-o", NULL};

  CliOptionResult result;

  // Parse -o (missing required argument)
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_MISSING_ARGUMENT);
  assert_ptr_equal(result.argument, "output");

  // No more options
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_END);
  assert_ptr_equal(result.argument, NULL);
}

static void
test_cli_option_parser_parse_option_short_argument_unrecognized(void **state) {
  (void)state; // Unused
  CliOptionParser parser;
  cli_option_parser_init(&parser, options, options_length);

  int32_t argc = 3;
  char const *argv[] = {"program", "-u", NULL};

  CliOptionResult result;

  // Parse -u (unrecognized option)
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_UNRECOGNIZED);
  assert_string_equal(result.argument, "u");

  // No more options
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_END);
  assert_ptr_equal(result.argument, NULL);
}

static void test_cli_option_parser_parse_option_positional(void **state) {
  (void)state; // Unused
  CliOptionParser parser;
  cli_option_parser_init(&parser, options, options_length);

  int32_t argc = 3;
  char const *argv[] = {"program", "positional_arg", NULL};

  CliOptionResult result;

  // Parse positional argument
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_POSITIONAL_ARGUMENT);
  assert_string_equal(result.argument, "positional_arg");

  // No more options
  result = cli_option_parser_parse_option(&parser, argc, argv);
  assert_int_equal(result.option, CLI_OPTION_END);
  assert_ptr_equal(result.argument, NULL);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_cli_option_parser_init),
      cmocka_unit_test(test_cli_option_parser_parse_option_long_argument_none),
      cmocka_unit_test(
          test_cli_option_parser_parse_option_long_argument_required),
      cmocka_unit_test(
          test_cli_option_parser_parse_option_long_argument_required_missing),
      cmocka_unit_test(
          test_cli_option_parser_parse_option_long_argument_optional),
      cmocka_unit_test(
          test_cli_option_parser_parse_option_long_argument_unrecognized),
      cmocka_unit_test(test_cli_option_parser_parse_option_short_argument_none),
      cmocka_unit_test(
          test_cli_option_parser_parse_option_short_argument_none_combined),
      cmocka_unit_test(
          test_cli_option_parser_parse_option_short_argument_required),
      cmocka_unit_test(
          test_cli_option_parser_parse_option_short_argument_required_missing),
      cmocka_unit_test(
          test_cli_option_parser_parse_option_short_argument_unrecognized),
      cmocka_unit_test(test_cli_option_parser_parse_option_positional),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
