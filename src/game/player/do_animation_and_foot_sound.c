/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_player_do_animation_and_foot_sound
*/

#include "internal.h"
#include "../player.h"
#include "../../game.h"
#include "../../random.h"
#include "my/cpp-like/algorithm.h"
#include <SFML/Audio/Sound.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Rect.h>

static void do_jump_animation(struct game_player *self, struct game *game)
{
    sfIntRect player_rect = sfSprite_getTextureRect(self->sprite);
    int real_offset = (player_rect.left + ((player_rect.top / 30) * 570)) + 30;

    if (game->state.frames_since_mode_begin % 5 || real_offset == 486 + 120)
        return;
    player_rect.left = real_offset % 570;
    player_rect.top = (real_offset / 570) * 30 + 6;
    if (MY_CLAMP(real_offset, 486 + 30, 607) != real_offset)
        player_rect = (sfIntRect){486, 6, 503 - 487, 29 - 6};
    sfSprite_setTextureRect(self->sprite, player_rect);
}

static void do_run_animation(struct game_player *self, struct game *game)
{
    sfIntRect player_rect = sfSprite_getTextureRect(self->sprite);
    int real_offset = (player_rect.left + ((player_rect.top / 30) * 570)) + 30;

    real_offset += (self->velocity.x >= 5.5f) * 30;
    if (game->state.frames_since_mode_begin % (self->velocity.x < 1.5f ? 8 :
        self->velocity.x < 3.f ? 4 : self->velocity.x < 5.5f ? 2 : 4))
        return;
    player_rect.left = real_offset % 570;
    player_rect.top = (real_offset / 570) * 30 + 6;
    if (MY_CLAMP(real_offset, 6 + 30, 495) != real_offset)
        player_rect = (sfIntRect){7, 6, 24 - 7, 29 - 6};
    sfSprite_setTextureRect(self->sprite, player_rect);
}

static void do_fall_animation(struct game_player *self, struct game *game)
{
    sfIntRect player_rect = sfSprite_getTextureRect(self->sprite);
    int real_offset = (player_rect.left + ((player_rect.top / 30) * 570)) + 30;

    if (game->state.frames_since_mode_begin % 4)
        return;
    player_rect.left = real_offset % 570;
    player_rect.top = (real_offset / 570) * 30 + 6;
    if (MY_CLAMP(real_offset, 570 + 35, 570 + 225) != real_offset)
        player_rect = (sfIntRect){36, 36, 54 - 36, 60 - 36};
    sfSprite_setTextureRect(self->sprite, player_rect);
}

static void start_foot_sound(struct game *game)
{
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

void game_player_do_animation_and_foot_sound(struct game_player *self,
    struct game *game)
{
    if (self->on_floor) {
        self->ft = MY_MAX((1 - self->velocity.x / self->max_velocity.x) *
            .35f, .15f);
        self->fc += 1.f / 60.f;
        if (self->fc > self->ft) {
            self->fc = 0;
            start_foot_sound(game);
        }
        do_run_animation(self, game);
    } else if (self->velocity.y < -1.4f)
        do_jump_animation(self, game);
    else
        do_fall_animation(self, game);
}
