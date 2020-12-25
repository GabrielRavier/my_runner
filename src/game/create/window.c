/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_create_window
*/

#include "internal.h"
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Window/VideoMode.h>
#include <SFML/Window/Window.h>

// 960 x 315 -> 1920 * 630
static const int SCREEN_WIDTH = 960;
static const int SCREEN_HEIGHT = 315;

bool game_create_window(sfRenderWindow **window, const struct arguments *args)
{
    *window = sfRenderWindow_create((sfVideoMode){SCREEN_WIDTH *
        args->resolution_multiplier, SCREEN_HEIGHT *
        args->resolution_multiplier, sfVideoMode_getDesktopMode().bitsPerPixel},
        "Canabalt but it's done with CSFML", sfDefaultStyle, NULL);
    if (*window == NULL)
        return (false);
    sfRenderWindow_setFramerateLimit(*window, args->framerate);
    sfRenderWindow_setVerticalSyncEnabled(*window, sfTrue);
    return (true);
}
