/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines main
*/

#include "game.h"
#include "game/create.h"
#include "game/destroy.h"
#include "game/main_loop.h"
#include "my/stdio.h"
#include "my/string.h"
#include "parse_argv.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static const int ERROR_RETURN_VALUE = 84;

int main(int argc, char **argv)
{
    struct game game;
    struct arguments args;

    srand(time(NULL));
    if (!parse_argv(argc, argv, &args))
        return (0);
    if (!game_create(&game, &args)) {
        my_dputs("Failed to initialize game\n", STDERR_FILENO);
        return (ERROR_RETURN_VALUE);
    }
    game_main_loop(&game);
    game_destroy(&game);
}
