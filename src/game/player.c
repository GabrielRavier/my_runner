/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_object_player_create
*/

#include "player.h"
#include "../game.h"
#include "../random.h"
#include "my/assert.h"
#include "my/macros.h"
#include <SFML/Audio/Sound.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Window/Keyboard.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>

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

static void do_jump_animation(struct game_player *player, struct game *game)
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

static void do_run_animation(struct game_player *player, struct game *game)
{
    sfIntRect player_rect = sfSprite_getTextureRect(player->sprite);
    int real_offset = (player_rect.left + ((player_rect.top / 30) * 570)) + 30;

    real_offset += (player->velocity.x >= 550) * 30;
    if (game->state.frames_since_mode_begin % (player->velocity.x < 150 ? 4 :
        player->velocity.x < 300 ? 2 : player->velocity.x < 550 ? 1 : 2))
        return;
    player_rect.left = real_offset % 570;
    player_rect.top = (real_offset / 570) * 30 + 6;
    if (MY_CLAMP(real_offset, 6 + 30, 495) != real_offset)
        player_rect = (sfIntRect){7, 6, 24 - 7, 29 - 6};
    sfSprite_setTextureRect(player->sprite, player_rect);
}

static void do_fall_animation(struct game_player *player, struct game *game)
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

static void do_bottom_collision(struct game_player *player,
    MY_ATTR_UNUSED struct game *game)
{
    if (player->my > .16f)
        player->stumble = true;
    if (!is_jumping())
        player->jump = .0f;
    player->my = .0f;
}

static void do_left_collision(struct game_player *player, struct game *game)
{
    sfSound_play(game->resources.sounds.wall.sf_sound);
    player->acceleration.x = 0;
    player->velocity.x = 0;
    player->max_velocity.y = 1000;
    player->epitath = "hit";
}

static void apply_velocity(struct game_player *player, struct game *game)
{
    sfVector2f position = sfSprite_getPosition(player->sprite);
    sfVector2f position_after = {position.x + player->velocity.x,
        position.y + player->velocity.y};
    sfVector2f intersection_point;
    struct game_object *i;

    GAME_OBJECT_VECTOR_FOR_EACH(&game->state.play.objects, i) {
        if (sfFloatRect_contains(&i->rect, position_after.x,
            position_after.y)) {
            intersection_point = do_intersection_point(&i->rect, &position,
                &position_after);
            (intersection_point.y == i->rect.top ? &do_bottom_collision :
                &do_left_collision)(player, game);
            if (intersection_point.y == i->rect.top)
                position_after.y = intersection_point.y;
            else
                position_after.x = intersection_point.x;
        }
    }
    sfSprite_setPosition(player->sprite, position_after);
}

void game_player_update(struct game_player *player, struct game *game)
{
    if (sfSprite_getPosition(player->sprite).y > 484) {
        player->is_dead = true;
        return;
    }
    if (player->acceleration.x <= .0f)
        return;
    if (player->velocity.x < 0)
        player->velocity.x = 0;
    else
        player->acceleration.x = get_acceleration_x(player->velocity.x);
    player->jump_limit = MY_MIN(player->velocity.x / (player->max_velocity.x *
        2.5f), 0.35f);
    if (player->jump >= 0 && is_jumping()) {
        if (player->jump == 0) {
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
        player->jump += 1.f / 60.f;
        if (player->jump > player->jump_limit)
            player->jump = -1;
    } else
        player->jump = -1;
    if (player->jump > 0) {
        player->crane_feet = false;
        player->velocity.y = (player->jump < .08f) ? -player->max_velocity.y *
            .65f : -player->max_velocity.y;
    }
    if (player->on_floor) {
        player->ft = MY_MAX((1 - player->velocity.x / player->max_velocity.x) *
            .35f, .15f);
        player->fc += 1.f / 60.f;
        if (player->fc > player->ft) {
            player->fc = 0;
            switch (random_int_between(1, 5)) {
            case 1:
                sfSound_play(player->crane_feet ?
                    game->resources.sounds.footc1.sf_sound :
                    game->resources.sounds.foot1.sf_sound);
                break;
            case 2:
                sfSound_play(player->crane_feet ?
                    game->resources.sounds.footc2.sf_sound :
                    game->resources.sounds.foot2.sf_sound);
                break;
            case 3:
                sfSound_play(player->crane_feet ?
                    game->resources.sounds.footc3.sf_sound :
                    game->resources.sounds.foot3.sf_sound);
                break;
            case 4:
                sfSound_play(player->crane_feet ?
                    game->resources.sounds.footc4.sf_sound :
                    game->resources.sounds.foot4.sf_sound);
                break;
            }
        }
        if (player->stumble && player->finished_stumbling)
            player->stumble = false;
        if (!player->stumble)
            do_run_animation(player, game);
    } else if (player->velocity.y < -140)
        do_jump_animation(player, game);
    else {
        do_fall_animation(player, game);
        player->stumble = false;
    }
    if (player->velocity.y == player->max_velocity.y)
        player->my += 1.f / 60.f;
    player->velocity.x = MY_CLAMP(player->velocity.x + player->acceleration.x,
        -player->max_velocity.x, player->max_velocity.x);
    player->velocity.y = MY_CLAMP(player->velocity.y + player->acceleration.y,
        -player->max_velocity.y, player->max_velocity.y);
    apply_velocity(player, game);
}

struct game_player game_player_create(struct game_resources *resources)
{
    struct game_player result = {0};

    result.acceleration = (sfVector2f){.01f, 12.f};
    result.velocity.x = 1.25f;
    result.max_velocity = DEFAULT_MAX_VELOCITY;
    result.sprite = sfSprite_create();
    MY_ASSERT(result.sprite != NULL);
    sfSprite_setTexture(result.sprite, resources->player, sfFalse);
    return (result);
}
