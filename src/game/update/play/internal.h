/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Declares game_update_play internal methods
*/

#pragma once

struct game;
struct game_state_play_sequence;

void game_update_play_sequence(struct game_state_play_sequence *self,
    struct game *game);
