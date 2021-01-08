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
    bool stumble;
    int finished_stumbling;
    float my;
    float ft;
    float fc;
    bool is_dead;
    bool crane_feet;
    bool on_floor;
    sfVector2f acceleration;
    sfVector2f velocity;
    sfVector2f max_velocity;
    const char *epitath;
};

void game_player_update(struct game_player *player, struct game *game);
struct game_player game_player_create(struct game_resources *resources);
