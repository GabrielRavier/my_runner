/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares game_object
*/

#pragma once

#include <SFML/Graphics/Types.h>

struct game;
struct game_object;

typedef void (*update_func_t)(struct game_object *object, struct game *game);

struct game_object {
    update_func_t update;
    sfSprite *sprite;
    void *private_data;
};
