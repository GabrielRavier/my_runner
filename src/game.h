/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares game
*/

#pragma once

#include "game/state.h"
#include "game/resources.h"
#include "my/my_string.h"
#include <SFML/Graphics/Types.h>

// This is the main struct for the entire game
struct game {
    sfRenderWindow *window;
    struct game_resources resources;
    struct game_state state;
    struct my_string *map;
};
