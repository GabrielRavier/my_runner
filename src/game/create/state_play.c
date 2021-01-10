/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_create_state_play
*/

#include "internal.h"
#include "../../game.h"
#include "../state_play.h"
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/View.h>

static bool game_create_rectangle_shape(sfRectangleShape **rect)
{
    *rect = sfRectangleShape_create();
    return (*rect != NULL);
}

static bool game_create_state_play_rects(struct game_state_play *self)
{
    if (!game_create_rectangle_shape(&self->gameover_text_rect))
        return (false);
    sfRectangleShape_setPosition(self->gameover_text_rect,
        (sfVector2f){0, 140});
    sfRectangleShape_setSize(self->gameover_text_rect, (sfVector2f){
        1000, 40});
    sfRectangleShape_setFillColor(self->gameover_text_rect,
        sfColor_fromRGB(53, 53, 61));
    self->gameover_bottom_rect =
        sfRectangleShape_copy(self->gameover_text_rect);
    if (!self->gameover_bottom_rect)
        return (false);
    sfRectangleShape_setPosition(self->gameover_bottom_rect, (sfVector2f){
        0, 302});
    return (true);
}

static bool game_create_state_play_sprites(struct game_state_play *self,
    const struct game *game)
{
    if (!game_create_sprite(&self->background, game->resources.background) ||
        !game_create_sprite(&self->midground, game->resources.midground) ||
        !game_create_sprite(&self->gameover, game->resources.gameover) ||
        !game_create_sprite(&self->player.sprite, game->resources.player))
        return (false);
    sfSprite_setScale(self->background, (sfVector2f){3, 3});
    sfSprite_setScale(self->midground, (sfVector2f){3, 3});
    sfSprite_setPosition(self->gameover, (sfVector2f){50, 110});
    return (true);
}

bool game_create_state_play(struct game_state_play *self,
    const struct game *game)
{
    if (!game_create_view(&self->midground_view, game->window) ||
        !game_create_view(&self->background_view, game->window) ||
        !game_create_view(&self->distance_text_view, game->window) ||
        !game_create_text(&self->distance_text, game) ||
        !game_create_state_play_sprites(self, game) ||
        !game_create_state_play_rects(self) ||
        !game_create_text(&self->gameover_text, game) ||
        !game_create_text(&self->jump_to_retry_text, game))
        return (false);
    game_object_vector_construct(&self->objects);
    sfView_setSize(self->background_view, (sfVector2f){1000.f, 1000.f});
    sfView_setSize(self->midground_view, (sfVector2f){500.f, 500.f});
    sfText_setString(self->jump_to_retry_text,
        "Jump to retry your daring escape.");
    sfText_setPosition(self->jump_to_retry_text, (sfVector2f){275, 305});
    sfText_setFillColor(self->gameover_text, sfColor_fromRGB(255, 255, 255));
    sfText_setFillColor(self->distance_text, sfColor_fromRGB(255, 255, 255));
    return (true);
}
