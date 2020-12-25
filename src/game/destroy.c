/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_destroy
*/

#include "destroy.h"
#include <SFML/Graphics/RenderWindow.h>

void game_destroy(struct game *self)
{
    sfRenderWindow_destroy(self->window);
}
