/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_draw
*/

#include "draw.h"
#include "object.h"
#include "../game.h"
#include "../text_utils.h"
#include "my/assert.h"
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/View.h>
#include <stdbool.h>

static void game_draw_title(struct game_state_title *self,
    sfRenderWindow *window)
{
    sfRenderWindow_clear(window, sfColor_fromRGB(53, 53, 61));
    sfRenderWindow_drawSprite(window, self->title_background, NULL);
    sfRenderWindow_drawSprite(window, self->title_text_sprite, NULL);
    sfRenderWindow_drawText(window, self->proud_to_present_text, NULL);
    sfRenderWindow_drawText(window, self->press_to_start_text, NULL);
}

static void game_draw_play_background(struct game_state_play *self,
    sfRenderWindow *window)
{
    sfRenderWindow_clear(window, sfColor_fromRGB(176, 176, 191));
    sfRenderWindow_setView(window, self->background_view);
    sfRenderWindow_drawSprite(window, self->background, NULL);
    sfRenderWindow_setView(window, self->midground_view);
    sfRenderWindow_drawSprite(window, self->midground, NULL);
}

static void game_draw_play(struct game_state_play *self, struct game *game,
    sfRenderWindow *window)
{
    struct game_object *i;

    game_draw_play_background(self, window);
    sfRenderWindow_setView(window, game->state.camera);
    GAME_OBJECT_VECTOR_FOR_EACH(&self->objects, i)
        if (i->draw != NULL)
            i->draw(i, window);
    sfRenderWindow_drawSprite(window, self->player.sprite, NULL);
    sfRenderWindow_setView(window, self->distance_text_view);
    if (!self->player.is_dead)
        sfRenderWindow_drawText(window, self->distance_text, NULL);
    else {
        sfRenderWindow_drawRectangleShape(window, self->gameover_text_rect,
            NULL);
        sfRenderWindow_drawSprite(window, self->gameover, NULL);
        sfRenderWindow_drawRectangleShape(window, self->gameover_bottom_rect,
            NULL);
        sfRenderWindow_drawText(window, self->jump_to_retry_text, NULL);
        sfRenderWindow_drawText(window, self->gameover_text, NULL);
    }
}

void game_draw(struct game *self)
{
    sfRenderWindow_clear(self->window, sfBlack);
    sfRenderWindow_setView(self->window, self->state.camera);
    switch (self->state.mode) {
    case GAME_MODE_TITLE:
        game_draw_title(&self->state.title, self->window);
        break;
    case GAME_MODE_PLAY:
        game_draw_play(&self->state.play, self, self->window);
        break;
    default:
        MY_ASSERT(false && "Invalid game mode");
    }
}
