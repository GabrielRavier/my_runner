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
#include <SFML/Graphics/Types.h>

struct game_state_play {
    struct game_state_play_sequence sequence;
    struct game_object_vector objects;
    struct game_player player;
    sfSprite *midground;
    sfView *midground_view;
    sfSprite *background;
    sfView *background_view;
    sfText *distance_text;
    sfView *distance_text_view;
    sfSprite *gameover;
    sfRectangleShape *gameover_text_rect;
    sfText *gameover_text;
    sfRectangleShape *gameover_bottom_rect;
    sfText *jump_to_retry_text;
};
