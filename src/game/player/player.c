/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_object_player_create
*/

#include "../player.h"
#include "internal.h"
#include "../is_jumping.h"
#include "../../game.h"
#include "../../random.h"
#include "my/macros.h"
#include <SFML/Audio/Sound.h>

static const sfVector2f DEFAULT_MAX_VELOCITY = {.x = 10.f, .y = 4.5f};

static float get_acceleration_x(float velocity_x)
{
    if (velocity_x < 1.5f)
        return (.035f);
    if (velocity_x < 2.5f)
        return (.024f);
    if (velocity_x < 4.f)
        return (.015f);
    if (velocity_x < 6.f)
        return (.008f);
    return (.003f);
}

static void handle_jump_input(struct game_player *self, struct game *game)
{
    if (self->jump == 0) {
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
    self->jump += 1.f / 60.f;
    if (self->jump > self->jump_limit)
        self->jump = -1;
}

static void do_jump(struct game_player *self, struct game *game)
{
    if (self->jump >= 0 && game_is_jumping())
        handle_jump_input(self, game);
    else
        self->jump = -1;
    if (self->jump > 0) {
        self->on_floor = false;
        self->velocity.y = (self->jump < .08f) ? -self->max_velocity.y *
            .65f : -self->max_velocity.y;
    }
}

void game_player_update(struct game_player *self, struct game *game)
{
    if (sfSprite_getPosition(self->sprite).y > 484) {
        self->is_dead = true;
        return;
    }
    if (self->velocity.x < 0)
        self->velocity.x = 0;
    else if (self->acceleration.x > 0)
        self->acceleration.x = get_acceleration_x(self->velocity.x);
    self->jump_limit = MY_MIN(self->velocity.x / (self->max_velocity.x *
        2.5f), 0.35f);
    do_jump(self, game);
    game_player_do_animation_and_foot_sound(self, game);
    self->velocity.x = MY_CLAMP(self->velocity.x + self->acceleration.x,
        -self->max_velocity.x, self->max_velocity.x);
    self->velocity.y = MY_CLAMP(self->velocity.y + self->acceleration.y,
        -self->max_velocity.y, self->max_velocity.y);
    game_player_apply_velocity(self, game);
}

void game_player_create(struct game_player *self)
{
    self->is_dead = false;
    self->acceleration = (sfVector2f){.01f, .25f};
    self->velocity.x = 1.25f;
    self->max_velocity = DEFAULT_MAX_VELOCITY;
    self->on_floor = true;
    self->jump = 0;
    sfSprite_setPosition(self->sprite, (sfVector2f){0, 90 - 16});
    sfSprite_setTextureRect(self->sprite, (sfIntRect){0});
}
