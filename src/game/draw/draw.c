/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_draw
*/

#include "../draw.h"
#include <SFML/Graphics/RenderWindow.h>

void game_draw(struct game *self)
{
    sfRenderWindow_clear(self->window, sfBlack);
}
