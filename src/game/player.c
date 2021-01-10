/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_object_player_create
*/

#include "player.h"
#include "is_jumping.h"
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

static const sfVector2f DEFAULT_MAX_VELOCITY = {.x = 10.f, .y = 4.5f};

static float get_acceleration_x(float velocity_x)
{
    if (velocity_x < 1.5f)
        return (.06f);
    if (velocity_x < 2.5f)
        return (.036f);
    if (velocity_x < 4.f)
        return (.024f);
    if (velocity_x < 6.f)
        return (.012f);
    return (.004f);
}

static void do_jump_animation(struct game_player *player, struct game *game)
{
    sfIntRect player_rect = sfSprite_getTextureRect(player->sprite);
    int real_offset = (player_rect.left + ((player_rect.top / 30) * 570)) + 30;

    if (game->state.frames_since_mode_begin % 5 || real_offset == 486 + 120)
        return;
    player_rect.left = real_offset % 570;
    player_rect.top = (real_offset / 570) * 30 + 6;
    if (MY_CLAMP(real_offset, 486 + 30, 607) != real_offset)
        player_rect = (sfIntRect){486, 6, 503 - 487, 29 - 6};
    sfSprite_setTextureRect(player->sprite, player_rect);
}

static void do_run_animation(struct game_player *player, struct game *game)
{
    sfIntRect player_rect = sfSprite_getTextureRect(player->sprite);
    int real_offset = (player_rect.left + ((player_rect.top / 30) * 570)) + 30;

    real_offset += (player->velocity.x >= 5.5f) * 30;
    if (game->state.frames_since_mode_begin % (player->velocity.x < 1.5f ? 8 :
        player->velocity.x < 3.f ? 4 : player->velocity.x < 5.5f ? 2 : 4))
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

static void do_bottom_collision(struct game_player *player,
    MY_ATTR_UNUSED struct game *game)
{
    if (!game_is_jumping())
        player->jump = .0f;
    player->on_floor = true;
}

static void do_left_collision(struct game_player *player, struct game *game)
{
    sfSound_play(game->resources.sounds.wall.sf_sound);
    player->acceleration.x = 0;
    player->velocity.x = 0;
    player->max_velocity.y = 1000;
}

static void apply_velocity(struct game_player *player, struct game *game)
{
    sfVector2f position = sfSprite_getPosition(player->sprite);
    sfVector2f position_after = {position.x + player->velocity.x,
        position.y + player->velocity.y};
    sfFloatRect rect_after;
    sfFloatRect intersection;
    struct game_object *i;

    sfSprite_setPosition(player->sprite, position_after);
    rect_after = sfSprite_getGlobalBounds(player->sprite);
    GAME_OBJECT_VECTOR_FOR_EACH(&game->state.play.objects, i) {
        if (sfFloatRect_intersects(&i->rect, &rect_after, &intersection)) {
            if (player->velocity.y > 0 && position.y < i->rect.top) {
                do_bottom_collision(player, game);
                position_after.y -= intersection.height;
                player->velocity.y = 0;
            } else if (player->velocity.x > 0 && position.x < i->rect.left) {
                do_left_collision(player, game);
                position_after.x -= intersection.width + 2.f;
                player->velocity.x = 0;
            } else if (player->velocity.y < 0 && (position.y +
                rect_after.height) >
                i->rect.top + i->rect.height) {
                position_after.y += intersection.height;
                player->velocity.y = 0;
            }
        }
    }
    if (ceilf(position_after.y) != ceilf(position.y)) {
        position_after.y = ceilf(position_after.y);
        player->on_floor = false;
    }
    sfSprite_setPosition(player->sprite, position_after);
}

static void apply_acceleration_and_velocity(struct game_player *player,
    struct game *game)
{
    player->velocity.x = MY_CLAMP(player->velocity.x + player->acceleration.x,
        -player->max_velocity.x, player->max_velocity.x);
    player->velocity.y = MY_CLAMP(player->velocity.y + player->acceleration.y,
        -player->max_velocity.y, player->max_velocity.y);
    apply_velocity(player, game);
}

void game_player_update(struct game_player *player, struct game *game)
{
    if (sfSprite_getPosition(player->sprite).y > 484) {
        player->is_dead = true;
        return;
    }
    if (player->velocity.x < 0)
        player->velocity.x = 0;
    else if (player->acceleration.x > 0)
        player->acceleration.x = get_acceleration_x(player->velocity.x);
    player->jump_limit = MY_MIN(player->velocity.x / (player->max_velocity.x *
        2.5f), 0.35f);
    if (player->jump >= 0 && game_is_jumping()) {
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
        player->on_floor = false;
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
                sfSound_play(game->resources.sounds.foot1.sf_sound);
                break;
            case 2:
                sfSound_play(game->resources.sounds.foot2.sf_sound);
                break;
            case 3:
                sfSound_play(game->resources.sounds.foot3.sf_sound);
                break;
            case 4:
                sfSound_play(game->resources.sounds.foot4.sf_sound);
                break;
            }
        }
        do_run_animation(player, game);
    } else if (player->velocity.y < -1.4f)
        do_jump_animation(player, game);
    else
        do_fall_animation(player, game);
    apply_acceleration_and_velocity(player, game);
}

void game_player_create(struct game_player *player)
{
    player->is_dead = false;
    player->acceleration = (sfVector2f){.01f, .25f};
    player->velocity.x = 1.25f;
    player->max_velocity = DEFAULT_MAX_VELOCITY;
    player->on_floor = true;
    player->jump = 0;
    sfSprite_setPosition(player->sprite, (sfVector2f){0, 90 - 16});
    sfSprite_setTextureRect(player->sprite, (sfIntRect){0});
}
