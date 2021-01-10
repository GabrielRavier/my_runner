/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Declares game_player internal methods
*/

#pragma once

struct game;
struct game_player;

void game_player_apply_velocity(struct game_player *player, struct game *game);
void game_player_do_animation_and_foot_sound(struct game_player *self,
    struct game *game);
