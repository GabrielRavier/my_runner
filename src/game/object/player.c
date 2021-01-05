/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_object_player_create
*/

#include "player.h"
#include "../../game.h"
#include "../../random.h"
#include "my/assert.h"
#include "my/macros.h"
#include <SFML/Audio/Sound.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Window/Keyboard.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>

struct player_data {
    float jump;
    float jump_limit;
    bool stumble;
    int finished_stumbling;
    float my;
    float ft;
    float fc;
    bool is_dead;
    bool crane_feet;
    bool on_floor;
    sfVector2f acceleration;
    sfVector2f velocity;
    sfVector2f max_velocity;
    const char *epitath;
};

static const sfVector2f DEFAULT_MAX_VELOCITY = {.x = 10.f, .y = 3.6f};

static float get_acceleration_x(float velocity_x)
{
    if (velocity_x < 100)
        return (60);
    if (velocity_x < 250)
        return (36);
    if (velocity_x < 400)
        return (24);
    if (velocity_x < 600)
        return (12);
    return (4);
}

static bool is_jumping(void)
{
    return sfKeyboard_isKeyPressed(sfKeyX) || sfKeyboard_isKeyPressed(sfKeyC);
}

static void do_jump_animation(struct game_object *player, struct game *game)
{
    sfIntRect player_rect = sfSprite_getTextureRect(player->sprite);
    int real_offset = (player_rect.left + ((player_rect.top / 30) * 570)) + 30;

    if (game->state.frames_since_mode_begin % 15)
        return;
    player_rect.left = real_offset % 570;
    player_rect.top = (real_offset / 570) * 30 + 6;
    if (MY_CLAMP(real_offset, 486 + 30, 570 + 25) != real_offset &&
        real_offset != 487 + 120)
        player_rect = (sfIntRect){487, 6, 503 - 487, 29 - 6};
    sfSprite_setTextureRect(player->sprite, player_rect);
}

static void do_run_animation(struct game_object *player, struct game *game)
{
    __auto_type data = (struct player_data *)player->private_data;
    sfIntRect player_rect = sfSprite_getTextureRect(player->sprite);
    int real_offset = (player_rect.left + ((player_rect.top / 30) * 570)) + 30;

    real_offset += (data->velocity.x >= 550) * 30;
    if (game->state.frames_since_mode_begin % (data->velocity.x < 150 ? 4 :
        data->velocity.x < 300 ? 2 : data->velocity.x < 550 ? 1 : 2))
        return;
    player_rect.left = real_offset % 570;
    player_rect.top = (real_offset / 570) * 30 + 6;
    if (MY_CLAMP(real_offset, 6 + 30, 495) != real_offset)
        player_rect = (sfIntRect){7, 6, 24 - 7, 29 - 6};
    sfSprite_setTextureRect(player->sprite, player_rect);
}

static void do_fall_animation(struct game_object *player, struct game *game)
{
    sfIntRect player_rect = sfSprite_getTextureRect(player->sprite);
    int real_offset = (player_rect.left + ((player_rect.top / 30) * 570)) + 30;

    if (game->state.frames_since_mode_begin % 4)
        return;
    player_rect.left = real_offset % 570;
    player_rect.top = (real_offset / 570) * 30 + 6;
    if (MY_CLAMP(real_offset, 570 + 35, 570 + 225) != real_offset)
        player_rect = (sfIntRect){36, 36, 54 - 36, 60 - 36};
    sfSprite_setTextureRect(player->sprite, player_rect);
}

// y is the point outside the rectangle, x is the point inside of it
static float get_t(const sfFloatRect *rectangle,
    const sfVector2f *y, const sfVector2f *x)
{
    sfVector2f a = {rectangle->left, rectangle->top + rectangle->height};
    sfVector2f c = {rectangle->left + rectangle->width, rectangle->top};

    if (y->x == x->x)
        return (MY_MAX((a.y - x->y) / (y->y - x->y), (c.y - x->y) / (y->y -
            x->y)));
    if (y->y == x->y)
        return (MY_MAX((a.x - x->x) / (y->x - x->x), (c.x - x->x) / (y->x -
            x->x)));
    if (y->x > x->x) {
        if (y->y > x->y)
            return (MY_MIN((c.x - x->x) / (y->x - x->x), (c.y - x->y) / (y->y -
                x->y)));
        return (MY_MIN((c.x - x->x) / (y->x - x->x), (a.y - x->y) / (y->y -
            x->y)));
    }
    if (y->y > x->y)
        return (MY_MIN((a.x - x->x) / (y->x - x->x), (c.y - x->y) / (y->y -
            x->y)));
    return (MY_MIN((a.x - x->x) / (y->x - x->x), (a.y - x->y) / (y->y - x->y)));
}

static sfVector2f do_intersection_point(const sfFloatRect *rectangle,
    const sfVector2f *pos_outside, const sfVector2f *pos_inside)
{
    float t = get_t(rectangle, pos_outside, pos_inside);

    return (sfVector2f){
        t * pos_outside->x + (1 - t) * pos_inside->x,
        t * pos_outside->y + (1 - t) * pos_inside->y
    };
}

static void do_bottom_collision(struct game_object *player,
    MY_ATTR_UNUSED struct game *game)
{
    __auto_type data = (struct player_data *)player->private_data;

    if (data->my > .16f)
        data->stumble = true;
    if (!is_jumping())
        data->jump = .0f;
    data->my = .0f;
}

static void do_left_collision(struct game_object *player, struct game *game)
{
    __auto_type data = (struct player_data *)player->private_data;

    sfSound_play(game->resources.sounds.wall.sf_sound);
    data->acceleration.x = 0;
    data->velocity.x = 0;
    data->max_velocity.y = 1000;
    data->epitath = "hit";
}

static void apply_velocity(struct game_object *player, struct game *game)
{
    __auto_type data = (struct player_data *)player->private_data;
    sfVector2f position = sfSprite_getPosition(player->sprite);
    sfVector2f position_after = {position.x + data->velocity.x,
        position.y + data->velocity.y};
    struct game_object *i;
    sfFloatRect i_rect;

    GAME_OBJECT_VECTOR_FOR_EACH(&game->state.play.objects, i)
        if (i != player) {
            i_rect = sfSprite_getGlobalBounds(i->sprite);
            if (sfFloatRect_contains(&i_rect, position_after.x,
                position_after.y)) {
                position_after = do_intersection_point(&i_rect, &position,
                    &position_after);
                (position_after.y == i_rect.top ? &do_bottom_collision :
                    &do_left_collision)(player, game);
            }
        }
    sfSprite_setPosition(player->sprite, position_after);
}

static void do_update(struct game_object *player, struct game *game)
{
    __auto_type data = (struct player_data *)player->private_data;

    if (sfSprite_getPosition(player->sprite).y > 484) {
        data->is_dead = true;
        return;
    }
    if (data->acceleration.x <= .0f)
        return;
    if (data->velocity.x < 0)
        data->velocity.x = 0;
    else
        data->acceleration.x = get_acceleration_x(data->velocity.x);
    data->jump_limit = MY_MIN(data->velocity.x / (data->max_velocity.x * 2.5f),
        0.35f);
    if (data->jump >= 0 && is_jumping()) {
        if (data->jump == 0) {
            switch (random_int_between(1, 4)) {
            case 1:
                sfSound_play(game->resources.sounds.jump1.sf_sound);
                break;
            case 2:
                sfSound_play(game->resources.sounds.jump2.sf_sound);
                break;
            case 3:
                sfSound_play(game->resources.sounds.jump3.sf_sound);
                break;
            }
        }
        data->jump += 1.f / 60.f;
        if (data->jump > data->jump_limit)
            data->jump = -1;
    } else
        data->jump = -1;
    if (data->jump > 0) {
        data->crane_feet = false;
        data->velocity.y = (data->jump < .08f) ? -data->max_velocity.y * .65f :
            -data->max_velocity.y;
    }
    if (data->on_floor) {
        data->ft = MY_MAX((1 - data->velocity.x / data->max_velocity.x) * .35f,
            .15f);
        data->fc += 1.f / 60.f;
        if (data->fc > data->ft) {
            data->fc = 0;
            switch (random_int_between(1, 5)) {
            case 1:
                sfSound_play(data->crane_feet ?
                    game->resources.sounds.footc1.sf_sound :
                    game->resources.sounds.foot1.sf_sound);
                break;
            case 2:
                sfSound_play(data->crane_feet ?
                    game->resources.sounds.footc2.sf_sound :
                    game->resources.sounds.foot2.sf_sound);
                break;
            case 3:
                sfSound_play(data->crane_feet ?
                    game->resources.sounds.footc3.sf_sound :
                    game->resources.sounds.foot3.sf_sound);
                break;
            case 4:
                sfSound_play(data->crane_feet ?
                    game->resources.sounds.footc4.sf_sound :
                    game->resources.sounds.foot4.sf_sound);
                break;
            }
        }
        if (data->stumble && data->finished_stumbling)
            data->stumble = false;
        if (!data->stumble)
            do_run_animation(player, game);
    } else if (data->velocity.y < -140)
        do_jump_animation(player, game);
    else {
        do_fall_animation(player, game);
        data->stumble = false;
    }
    if (data->velocity.y == data->max_velocity.y)
        data->my += 1.f / 60.f;
    data->velocity.x = MY_CLAMP(data->velocity.x + data->acceleration.x,
        -data->max_velocity.x, data->max_velocity.x);
    data->velocity.y = MY_CLAMP(data->velocity.y + data->acceleration.y,
        -data->max_velocity.y, data->max_velocity.y);
    apply_velocity(player, game);
}

struct game_object game_object_player_create(struct game_resources *resources)
{
    struct game_object result;
    __auto_type data = (struct player_data *)malloc(sizeof(struct player_data));

    *data = (struct player_data){0};
    data->acceleration = (sfVector2f){.01f, 12.f};
    data->velocity.x = 1.25f;
    data->max_velocity = DEFAULT_MAX_VELOCITY;
    result.private_data = data;
    result.update = &do_update;
    result.sprite = sfSprite_create();
    MY_ASSERT(result.sprite != NULL);
    sfSprite_setTexture(result.sprite, resources->player, sfFalse);
    return (result);
}
