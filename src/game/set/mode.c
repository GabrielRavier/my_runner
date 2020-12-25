/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_set_mode
*/

#include "mode.h"

void game_set_mode(struct game *self, enum game_mode mode)
{
    self->state.mode = mode;
}
