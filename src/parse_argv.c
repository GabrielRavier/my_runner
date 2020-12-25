/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines parse_argv
*/

#include "parse_argv.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include <getopt.h>
#include <errno.h>
#include <limits.h>

enum {
    OPTION_FRAMERATE = CHAR_MAX + 1,
    OPTION_RESOLUTION_MULTIPLIER
};

static const struct option long_options[] = {
    {"resolution-multiplier", required_argument, NULL, OPTION_RESOLUTION_MULTIPLIER},
    {"framerate", required_argument, NULL, OPTION_FRAMERATE},
    {"help", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0}
};

static bool usage(const char *program_name)
{
    my_printf("Usage: %s [OPTION]...\n\n"
        "    --resolution-multiplier=MULTIPLIER multiplies the screen "
        "width/height by this amount, by default this is 2, with a screen "
        "size (before multiplication) of 960*315\n"
        "    --framerate=FRAMERATE              sets the framerate to "
        "FRAMERATE fps\n"
        "    -h, --help                         display this help and exit\n"
        "\n"
        "Implements a small runner game based on Canabalt.\n"
        "Press X or C to jump/begin the game\n", program_name);
    return (false);
}

static bool do_single_option(int c, const char *argv0, struct arguments *args)
{
    char *num_end;
    
    switch (c) {
    case 'h':
    default:
        return (usage(argv0));
    case OPTION_FRAMERATE:
    case OPTION_RESOLUTION_MULTIPLIER:
        errno = 0;
        *(c == OPTION_FRAMERATE ? &args->framerate :
          &args->resolution_multiplier) = my_strtol(optarg, &num_end, 0);
        if (errno || num_end == optarg || *num_end != '\0')
            return (usage(argv0));
    }
    return (true);
}

bool parse_argv(int argc, char **argv, struct arguments *args)
{
    int c;

    args->framerate = 60;
    args->resolution_multiplier = 2;
    while (true) {
        c = getopt_long(argc, argv, "h", long_options, NULL);
        if (c == -1)
            break;
        if (!do_single_option(c, argv[0], args))
            return (false);
    }
    return (true);
}
