// SPDX-License-Identifier: MIT

#ifndef EXP_SUPPORT_CLI_OPTION_PARSER_H
#define EXP_SUPPORT_CLI_OPTION_PARSER_H

#include <stdint.h>

typedef enum CliOptionArgumentKind {
  OPTION_ARGUMENT_NONE,
  OPTION_ARGUMENT_REQUIRED,
  OPTION_ARGUMENT_OPTIONAL,
} CliOptionArgumentKind;

typedef struct CliOption {
  char const *name;
  char const *description;
  char const *environment_variable;
  CliOptionArgumentKind argument_kind;
  char short_name;
} CliOption;

typedef struct CliOptionParser {
  int32_t option_index;
  int32_t suboption_index;
  int32_t option_count;
  CliOption const *options;
} CliOptionParser;

#define CLI_OPTION_END 0
#define CLI_OPTION_MISSING_ARGUMENT -1
#define CLI_OPTION_UNRECOGNIZED_ARGUMENT_KIND -2
#define CLI_OPTION_UNRECOGNIZED '?'
#define CLI_OPTION_POSITIONAL_ARGUMENT '!'

typedef struct CliOptionResult {
  int32_t option;
  char const *argument;
} CliOptionResult;

void cli_option_parser_init(CliOptionParser *parser, CliOption const *options,
                            int32_t option_count);
CliOptionResult cli_option_parser_parse_option(CliOptionParser *parser,
                                               int32_t argc,
                                               char const *argv[]);
/*
CLIOptionResult cli_option_parser_parse_environment_variable(CliOptionParser
*parser, char const *envp[]);

CliOptionResult cli_option_parser_parse_option_file(CliOptionParser *parser,
FILE *file);
 */

#endif // !EXP_SUPPORT_CLI_OPTION_PARSER_H