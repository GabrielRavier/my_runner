/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares game_object_player
*/

#pragma once

#include <stdbool.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Vector2.h>

struct game;
struct game_resources;

struct game_player {
    sfSprite *sprite;
    float jump;
    float jump_limit;
    int finished_stumbling;
    float ft;
    float fc;
    bool is_dead;
    bool on_floor;
    sfVector2f acceleration;
    sfVector2f velocity;
    sfVector2f max_velocity;
};

void game_player_update(struct game_player *player, struct game *game);
void game_player_create(struct game_player *player);
