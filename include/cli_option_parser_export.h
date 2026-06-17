
#ifndef CLI_OPTION_PARSER_EXPORT_H
#define CLI_OPTION_PARSER_EXPORT_H

#ifdef CLI_OPTION_PARSER_STATIC_DEFINE
#  define CLI_OPTION_PARSER_EXPORT
#  define CLI_OPTION_PARSER_NO_EXPORT
#else
#  ifndef CLI_OPTION_PARSER_EXPORT
#    ifdef cli_option_parser_EXPORTS
        /* We are building this library */
#      define CLI_OPTION_PARSER_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define CLI_OPTION_PARSER_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef CLI_OPTION_PARSER_NO_EXPORT
#    define CLI_OPTION_PARSER_NO_EXPORT 
#  endif
#endif

#ifndef CLI_OPTION_PARSER_DEPRECATED
#  define CLI_OPTION_PARSER_DEPRECATED __declspec(deprecated)
#endif

#ifndef CLI_OPTION_PARSER_DEPRECATED_EXPORT
#  define CLI_OPTION_PARSER_DEPRECATED_EXPORT CLI_OPTION_PARSER_EXPORT CLI_OPTION_PARSER_DEPRECATED
#endif

#ifndef CLI_OPTION_PARSER_DEPRECATED_NO_EXPORT
#  define CLI_OPTION_PARSER_DEPRECATED_NO_EXPORT CLI_OPTION_PARSER_NO_EXPORT CLI_OPTION_PARSER_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CLI_OPTION_PARSER_NO_DEPRECATED
#    define CLI_OPTION_PARSER_NO_DEPRECATED
#  endif
#endif

#endif /* CLI_OPTION_PARSER_EXPORT_H */
