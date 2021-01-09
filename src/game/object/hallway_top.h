/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Declares game_object_hallway_top
*/

#pragma once

#include "../object.h"
#include "../state_play_sequence.h"

struct game_object game_object_create_hallway_top(
    struct game_state_play_sequence *sequence, int hallway_height);
