/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares game_state_play
*/

#pragma once

#include "object_vector.h"
#include "player.h"
#include "state_play_sequence.h"

struct game_state_play {
    struct game_state_play_sequence sequence;
    struct game_object_vector objects;
    struct game_player player;
    sfSprite *midground;
    sfView *midground_view;
    sfSprite *background;
    sfView *background_view;
};
