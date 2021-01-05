/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_draw
*/

#include "../draw.h"
#include "my/assert.h"
#include <SFML/Graphics/RenderWindow.h>
#include <stdbool.h>

static void game_draw_title(struct game *self)
{
    sfRenderWindow_clear(self->window, sfColor_fromRGB(53, 53, 61));
    sfRenderWindow_drawSprite(self->window, self->state.title.title_background,
        NULL);
    sfRenderWindow_drawSprite(self->window, self->state.title.title_text_sprite,
        NULL);
    sfRenderWindow_drawText(self->window,
        self->state.title.proud_to_present_text, NULL);
    sfRenderWindow_drawText(self->window, self->state.title.press_to_start_text,
        NULL);
}

static void game_draw_play(struct game *self)
{
    struct game_object *i;

    sfRenderWindow_clear(self->window, sfColor_fromRGB(176, 176, 191));
    sfRenderWindow_setView(self->window, self->state.play.background_view);
    sfRenderWindow_drawSprite(self->window, self->state.play.background, NULL);
    sfRenderWindow_setView(self->window, self->state.play.midground_view);
    sfRenderWindow_drawSprite(self->window, self->state.play.midground, NULL);
    sfRenderWindow_setView(self->window, self->state.camera);
    GAME_OBJECT_VECTOR_FOR_EACH(&self->state.play.objects, i)
        sfRenderWindow_drawSprite(self->window, i->sprite, NULL);
    sfRenderWindow_drawSprite(self->window, self->state.play.player.sprite, NULL);
}

void game_draw(struct game *self)
{
    sfRenderWindow_clear(self->window, sfBlack);
    sfRenderWindow_setView(self->window, self->state.camera);
    switch (self->state.mode) {
    case GAME_MODE_TITLE:
        game_draw_title(self);
        break;
    case GAME_MODE_PLAY:
        game_draw_play(self);
        break;
    default:
        MY_ASSERT(false && "Invalid game mode");
    }
}
