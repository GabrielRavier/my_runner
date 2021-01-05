/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares game_state_play
*/

#pragma once

#include "object_vector.h"

struct game_state_play {
    struct game_object_vector objects;
    struct game_object player;
    sfSprite *midground;
    sfView *midground_view;
    sfSprite *background;
    sfView *background_view;
};
