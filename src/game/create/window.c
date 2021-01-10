/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_create_window
*/

#include "internal.h"
#include "../../parse_argv.h"
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Window/VideoMode.h>
#include <SFML/Window/Window.h>

// 480 * 320 with default multiply by 3 -> 1440 * 960
static const int SCREEN_WIDTH = 480;
static const int SCREEN_HEIGHT = 320;

bool game_create_window(sfRenderWindow **window, const struct arguments *args)
{
    *window = sfRenderWindow_create((sfVideoMode){SCREEN_WIDTH, SCREEN_HEIGHT,
        sfVideoMode_getDesktopMode().bitsPerPixel},
        "Canabalt but it's done with CSFML", sfDefaultStyle, NULL);
    if (*window == NULL)
        return (false);
    sfRenderWindow_setSize(*window, (sfVector2u){SCREEN_WIDTH *
        args->resolution_multiplier, SCREEN_HEIGHT *
        args->resolution_multiplier});
    sfRenderWindow_setFramerateLimit(*window, args->framerate);
    sfRenderWindow_setVerticalSyncEnabled(*window, sfTrue);
    return (true);
}
