/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Declare game_update internal methods
*/

#pragma once

struct game;
struct game_state;
struct game_state_play;

void game_update_title(struct game_state *self);
void game_update_play(struct game_state_play *self, struct game *game);
