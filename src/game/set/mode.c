/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_set_mode
*/

#include "mode.h"
#include "../change_music.h"
#include "../object/player.h"
#include <SFML/Audio/Music.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/View.h>

static void game_set_mode_init_play(struct game *self)
{
    self->state.play.player = game_object_player_create(&self->resources);
    sfSprite_setTextureRect(self->state.play.player.sprite, (sfIntRect){0});
    game_object_vector_clear(&self->state.play.objects);
}

void game_set_mode(struct game *self, enum game_mode mode)
{
    self->state.mode = mode;
    self->state.frames_since_mode_begin = 0;
    game_change_music(&self->state.music, mode == GAME_MODE_TITLE ?
        "assets/title.ogg" : "assets/play.ogg");
    if (mode == GAME_MODE_PLAY)
        game_set_mode_init_play(self);
}
