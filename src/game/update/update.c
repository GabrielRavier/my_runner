/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_update
*/

#include "../update.h"
#include "../../random.h"
#include "../object/building_bottom.h"
#include "my/assert.h"
#include "my/macros.h"
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/View.h>
#include <math.h>
#include <limits.h>
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
    set_sprite_alpha(self->state.title.title_text_sprite, title_alpha);
    set_text_alpha(self->state.title.proud_to_present_text, title_alpha);
    set_text_alpha(self->state.title.press_to_start_text, press_start_alpha);
}

static void game_update_play_background(struct game *self)
{
    sfVector2f player_position =
        sfSprite_getPosition(self->state.play.player.sprite);
    sfIntRect background_rect =
        sfSprite_getTextureRect(self->state.play.background);
    sfVector2f background_position = {((int)player_position.x / (512 * 3) - 5)
        * (512 * 3), 0};

    background_rect.width = 5000;
    sfSprite_setTextureRect(self->state.play.background, background_rect);
    sfSprite_setTextureRect(self->state.play.midground, background_rect);
    sfSprite_setPosition(self->state.play.background, background_position);
    sfSprite_setPosition(self->state.play.midground, background_position);
}

static int get_hallway_height(struct game *self)
{
    float velocity_x = self->state.play.player.velocity.x;

    if (velocity_x > 6.4f)
        return (7);
    if (velocity_x > 4.8f)
        return (6);
    if (velocity_x > 3.2f)
        return (5);
    if (self->state.play.sequence.current_index > 0)
        return (4);
    return (3);
}

static int get_gap(struct game *self)
{
    float max_gap = ((self->state.play.player.velocity.x * 75.f) / 20.f) * .75f;

    return (random_float_between(MY_MAX(max_gap * .4f, 4.f), MY_MAX(max_gap, 4.f)));
}

static float get_width(struct game *self, float gap)
{
    float min_width = (ceilf(480.f / 16.f) + 2) - gap;
    float max_width;

    if ((min_width < 15) && self->state.play.player.velocity.x <
        self->state.play.player.max_velocity.x * .8f)
        min_width = 15;
    min_width = MY_MAX(min_width, 6);
    max_width = min_width * 2;
    return floorf(min_width + random_float_between(.0f, 1.f) * max_width) * 16;
}

static void game_update_play_sequence(struct game_state_play_sequence *self,
    struct game *game)
{
    enum sequence_object_type type =
        random_int_between(SEQUENCE_OBJECT_TYPE_FIRST,
        SEQUENCE_OBJECT_TYPE_LAST);
    float gap;
    float drop;
    float max_j;
    int hallway_height = 0;

    if (self->position.x + self->width >
        sfSprite_getPosition(game->state.play.player.sprite).x + 480)
        return;
    if (self->current_index == 0) {
        self->position.x = -60;
        self->position.y = 90;
        self->width = 900;
        self->height = 480 - 90;
        type = SEQUENCE_OBJECT_TYPE_HALLWAY;
    }
    if (self->current_index == 1) {
        self->position.x += self->width + 160;
        self->position.y = 240;
        self->width = 42 * 16;
        self->height = 480 - 240;
        type = SEQUENCE_OBJECT_TYPE_ROOF;
    }
    if (type == SEQUENCE_OBJECT_TYPE_HALLWAY)
        hallway_height = get_hallway_height(game);
    if (self->current_index > 1) {
        gap = get_gap(game);
        max_j = MY_MIN(self->position.y / 16 - 2 - hallway_height, 6 *
            game->state.play.player.jump_limit / .35f);
        if (max_j > 0)
            max_j = ceilf(max_j - (1 - random_float_between(.0f, 1.f)));
        drop = (int)(random_float_between(.0f, 1.f) * MY_MIN(
            self->height / 16 - 4, 10) - max_j);
        if (type == SEQUENCE_OBJECT_TYPE_HALLWAY && gap > 10)
            drop = 0;
        if (drop == 0)
            --drop;
        self->position.x += self->width + gap * 16;
        self->position.y += drop * 16;
        self->position.y = MY_CLAMP(self->position.y, 0, 480);
        self->height = 480 - self->position.y;
        self->width = get_width(game, gap);
    }
    if (type == SEQUENCE_OBJECT_TYPE_HALLWAY ||
        type == SEQUENCE_OBJECT_TYPE_ROOF) {
        __auto_type building_bottom = game_object_create_building_bottom(self);
        game_object_vector_push_back(&game->state.play.objects, &building_bottom);
    }
    ++self->current_index;
}

static void game_update_play(struct game *self)
{
    struct game_object *i;
    sfVector2f player_position;

    game_update_play_sequence(&self->state.play.sequence, self);
    GAME_OBJECT_VECTOR_FOR_EACH(&self->state.play.objects, i)
        if (i->update != NULL)
            i->update(i, self);
    game_player_update(&self->state.play.player, self);
    player_position = sfSprite_getPosition(self->state.play.player.sprite);
    player_position.x += 200;
    player_position.y = MY_MIN(player_position.y, 300);
    sfView_setCenter(self->state.camera, player_position);
    sfView_setCenter(self->state.play.background_view, player_position);
    sfView_setCenter(self->state.play.midground_view, player_position);
    game_update_play_background(self);
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
