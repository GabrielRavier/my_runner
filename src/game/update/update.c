/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_update
*/

#include "../update.h"
#include "my/assert.h"
#include "my/macros.h"
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/View.h>
#include <math.h>
#include <stdbool.h>

static void set_sprite_alpha(sfSprite *sprite, sfUint8 alpha)
{
    sfColor sprite_color = sfSprite_getColor(sprite);

    sprite_color.a = alpha;
    sfSprite_setColor(sprite, sprite_color);
}

static void set_text_alpha(sfText *sprite, sfUint8 alpha)
{
    sfColor text_color = sfText_getFillColor(sprite);

    text_color.a = alpha;
    sfText_setFillColor(sprite, text_color);
}

// The camera panning stops after ~100 frames
static void game_update_title(struct game *self)
{
    sfVector2f camera_center = {480 / 2, (320 / 2) - 10};
    uintmax_t title_alpha = MY_CLAMP((intmax_t)(-(100 * 2) +
        self->state.frames_since_mode_begin * 2), (intmax_t)0, (intmax_t)0xFF);
    uintmax_t press_start_alpha = MY_CLAMP((intmax_t)(-(100 * 2) - (0x100 / 2) +
        self->state.frames_since_mode_begin * 2), (intmax_t)0, (intmax_t)0xFF);

    camera_center.y += (100000.f /
        (powf(self->state.frames_since_mode_begin + 10, 2)));
    camera_center.y = MY_MAX(camera_center.y, (320 / 2));
    sfView_setCenter(self->state.camera, camera_center);
    set_sprite_alpha(self->state.menu.title_text_sprite, title_alpha);
    set_text_alpha(self->state.menu.proud_to_present_text, title_alpha);
    set_text_alpha(self->state.menu.press_to_start_text, press_start_alpha);
}

static void game_update_play(struct game *self)
{
    struct game_object *i;
    sfVector2f player_position;

    GAME_OBJECT_VECTOR_FOR_EACH(&self->state.play.objects, i)
        i->update(i, self);
    player_position = sfSprite_getPosition(self->state.play.player_sprite);
    player_position.x += 200;
    sfView_setCenter(self->state.camera, player_position);
}

void game_update(struct game *self)
{
    ++self->state.frames_since_mode_begin;
    switch (self->state.mode) {
    case GAME_MODE_TITLE:
        game_update_title(self);
        break;
    case GAME_MODE_PLAY:
        game_update_play(self);
        break;
    default:
        MY_ASSERT(false && "Invalid game mode");
    }
}
