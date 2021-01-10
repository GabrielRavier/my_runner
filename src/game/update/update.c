/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_update
*/

#include "../update.h"
#include "internal.h"
#include "my/assert.h"

void game_update(struct game *self)
{
    ++self->state.frames_since_mode_begin;
    switch (self->state.mode) {
    case GAME_MODE_TITLE:
        game_update_title(&self->state);
        break;
    case GAME_MODE_PLAY:
        game_update_play(&self->state.play, self);
        break;
    default:
        MY_ASSERT(false && "Invalid game mode");
    }
}
