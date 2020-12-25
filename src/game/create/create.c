/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_create
*/

#include "../create.h"
#include "internal.h"

bool game_create(struct game *self, const struct arguments *args)
{
    if (!game_create_window(&self->window, args))
        return (false);
    return (true);
}
