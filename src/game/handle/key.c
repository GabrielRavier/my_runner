/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_handle_key
*/

#include "key.h"
#include "../set/mode.h"

void game_handle_key(struct game *self, sfKeyCode key_code)
{
    if (self->state.mode == GAME_MODE_TITLE && (key_code == sfKeyC ||
        key_code == sfKeyX))
        game_set_mode(self, GAME_MODE_PLAY);
}
