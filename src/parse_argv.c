/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines parse_argv
*/

#include "parse_argv.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/getopt.h"
#include <errno.h>
#include <limits.h>

static bool usage(const char *program_name)
{
    my_printf("Usage: %s [OPTION]... [FILE]\n\n"
        "    -m MULTIPLIER multiplies the screen "
        "width/height by this amount, by default this is 3, with a screen "
        "size (before multiplication) of 480 * 320\n"
        "    -f FRAMERATE  sets the framerate to FRAMERATE fps\n"
        "    -u            enables fullscreen\n"
        "    -h            display this help and exit\n"
        "\n"
        "Implements a small runner game based on Canabalt.\n"
        "Press X or C to jump/begin the game\n"
        "Press Esc to quit\n", program_name);
    return (false);
}

// TODO: Fix this for numbers that fit in long but not in int (not a big problem
// but shortening could lead to somewhat surprising results
static bool do_single_option(int c, const char *argv0, struct arguments *args)
{
    char *num_end;

    switch (c) {
    case 'h':
    default:
        return (usage(argv0));
    case 'u':
        args->is_fullscreen = true;
        break;
    case 'f':
    case 'm':
        errno = 0;
        *(c == 'f' ? &args->framerate :
        &args->resolution_multiplier) = (unsigned)my_strtol(optarg, &num_end,
            0);
        if (errno || num_end == optarg || *num_end != '\0')
            return (usage(argv0));
    }
    return (true);
}

bool parse_argv(int argc, char **argv, struct arguments *args)
{
    int c;

    args->framerate = 60;
    args->resolution_multiplier = 3;
    args->is_fullscreen = false;
    while (true) {
        c = my_getopt(argc, argv, "huf:m:");
        if (c == -1)
            break;
        if (!do_single_option(c, argv[0], args))
            return (false);
    }
    if (argv[optind] == NULL || argv[optind + 1] != NULL)
        return (usage(argv[0]));
    args->map_filename = argv[optind];
    return (true);
}
