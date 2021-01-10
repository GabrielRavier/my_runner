/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares internal game_create methods
*/

#pragma once

#include <SFML/Graphics/Types.h>
#include <stdbool.h>

struct arguments;
struct game;
struct game_state_play;
struct sound_with_buffer;
struct my_string;

bool game_create_window(sfRenderWindow **window, const struct arguments *args);
bool game_create_state_play(struct game_state_play *self,
    const struct game *game);
bool game_create_font(sfFont **font, const char *filename);
bool game_create_view(sfView **view, const sfRenderWindow *window);
bool game_create_text(sfText **text, const struct game *game);
bool game_create_texture(sfTexture **texture, const char *filename);
bool game_create_sprite(sfSprite **sprite, const sfTexture *texture);
bool game_create_sound(struct sound_with_buffer *sound, const char *filename);
bool game_create_map(struct my_string **read_map, const char *map_filename);
