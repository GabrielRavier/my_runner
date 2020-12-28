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
    sfRenderWindow_setView(self->window, self->state.camera);
    if (self->state.mode == GAME_MODE_MENU) {
        sfRenderWindow_clear(self->window, sfColor_fromRGB(53, 53, 61));
        sfRenderWindow_drawSprite(self->window,
            self->state.menu.title_background, NULL);
        sfRenderWindow_drawSprite(self->window,
            self->state.menu.title_text_sprite, NULL);
        sfRenderWindow_drawText(self->window,
            self->state.menu.proud_to_present_text, NULL);
        sfRenderWindow_drawText(self->window,
            self->state.menu.press_to_start_text, NULL);
    }
}
