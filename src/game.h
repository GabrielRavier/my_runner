/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares game
*/

#pragma once

#include "game/state.h"
#include <SFML/Graphics/Types.h>

// This is the main struct for the entire game
struct game {
    sfRenderWindow *window;
    struct game_state state;
};
