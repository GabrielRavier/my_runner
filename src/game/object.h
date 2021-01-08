/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares game_object
*/

#pragma once

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Types.h>

struct game;
struct game_object;

typedef void (*game_object_update_func_t)(struct game_object *object,
    struct game *game);
typedef void (*game_object_draw_func_t)(struct game_object *object,
    sfRenderWindow *window);
typedef void (*game_object_destroy_func_t)(struct game_object *object);

struct game_object {
    sfFloatRect rect;
    game_object_update_func_t update;
    game_object_draw_func_t draw;
    game_object_destroy_func_t destroy;
    void *private_data;
};
