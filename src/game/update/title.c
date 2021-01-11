/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_update_title
*/

#include "internal.h"
#include "../state.h"
#include "my/cpp-like/algorithm.h"
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/View.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Config.h>
#include <math.h>
#include <stdint.h>

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
void game_update_title(struct game_state *self)
{
    sfVector2f camera_center = {480 / 2, (320 / 2) - 10};
    sfUint8 title_alpha = (sfUint8)MY_CLAMP((intmax_t)((uintmax_t)-(100 * 2) +
        self->frames_since_mode_begin * 2), (intmax_t)0, (intmax_t)0xFF);
    sfUint8 press_start_alpha = (sfUint8)MY_CLAMP((intmax_t)((uintmax_t)-(100 *
        2) - (0x100 / 2) + self->frames_since_mode_begin * 2), (intmax_t)0,
        (intmax_t)0xFF);

    camera_center.y += (100000.f /
        (powf((float)self->frames_since_mode_begin + 10, 2)));
    camera_center.y = MY_MAX(camera_center.y, (float)(320 / 2));
    sfView_setCenter(self->camera, camera_center);
    set_sprite_alpha(self->title.title_text_sprite, title_alpha);
    set_text_alpha(self->title.proud_to_present_text, title_alpha);
    set_text_alpha(self->title.press_to_start_text, press_start_alpha);
}
