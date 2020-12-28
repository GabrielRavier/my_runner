/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares game_state
*/

#pragma once

#include "mode.h"
#include "state_menu.h"
#include <SFML/Audio/Types.h>
#include <SFML/Graphics/Types.h>
#include <stdint.h>

struct game_state {
    enum game_mode mode;
    uintmax_t frames_since_mode_begin;
    struct game_state_menu menu;
    sfMusic *music;
    sfView *camera;
};
