/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_destroy
*/

#include "destroy.h"
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/View.h>

void game_destroy(struct game *self)
{
    sfView_destroy(self->state.camera);
    sfFont_destroy(self->resources.nokia_font);
    sfRenderWindow_destroy(self->window);
}
