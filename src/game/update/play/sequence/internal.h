/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Declares game_update_play_sequence internal methods
*/

#pragma once

#include "../../../state_play_sequence.h"

struct game;
struct game_state_play;
struct game_player;

int game_update_play_sequence_get_hallway_height(
    const struct game_state_play *self);
int game_update_play_sequence_get_gap(const struct game_player *self);
float game_update_play_sequence_get_width(const struct game_player *self,
    int gap);
enum game_sequence_object_type game_update_play_sequence_get_next_object_type(
    size_t current_index, const struct game *game);
enum game_sequence_object_type game_update_play_sequence_get_one_of_first_two(
    struct game_state_play_sequence *self);
