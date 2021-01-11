/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_update_play
*/

#include "../internal.h"
#include "internal.h"
#include "../../is_jumping.h"
#include "../../object.h"
#include "../../state_play.h"
#include "../../set/mode.h"
#include "../../../game.h"
#include "../../../text_utils.h"
#include "../../../top_score.h"
#include "my/cpp-like/algorithm.h"
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/View.h>

static void game_update_play_background(const struct game_state_play *self)
{
    sfVector2f player_position = sfSprite_getPosition(self->player.sprite);
    sfIntRect background_rect = sfSprite_getTextureRect(self->background);
    sfVector2f background_position = {(float)(((int)player_position.x / (512 *
        3) - 5) * (512 * 3)), 0};

    background_rect.width = 5000;
    sfSprite_setTextureRect(self->background, background_rect);
    sfSprite_setTextureRect(self->midground, background_rect);
    sfSprite_setPosition(self->background, background_position);
    sfSprite_setPosition(self->midground, background_position);
}

static void game_update_play_game_over(struct game_state_play *self,
    struct game *game, long long distance_traveled)
{
    if (!self->player.is_dead)
        return;
    text_set_printf(self->gameover_text,
        "You ran %lldm before falling to your death.", distance_traveled);
    sfText_setPosition(self->gameover_text, (sfVector2f){(float)(int)((
        sfView_getSize(game->state.camera).x / 2) - (
        sfText_getLocalBounds(self->gameover_text).width / 2)), sfView_getSize(
        game->state.camera).y / 2 - (240 - 160)});
    if (get_top_score() < distance_traveled)
        set_top_score(distance_traveled);
    if (game_is_jumping())
        game_set_mode(game, GAME_MODE_PLAY);
}

static void game_update_play_views(struct game_state_play *self,
    struct game *game)
{
    sfVector2f player_position = sfSprite_getPosition(self->player.sprite);

    player_position.x += 200;
    player_position.y = MY_MIN(player_position.y, (float)300);
    sfView_setCenter(game->state.camera, player_position);
    sfView_setCenter(self->background_view, player_position);
    sfView_setCenter(self->midground_view, player_position);
}

void game_update_play(struct game_state_play *self, struct game *game)
{
    struct game_object *i;
    long long distance_traveled;

    game_update_play_sequence(&self->sequence, game);
    GAME_OBJECT_VECTOR_FOR_EACH(&self->objects, i)
        if (i->update != NULL)
            i->update(i, game);
    game_player_update(&self->player, game);
    game_update_play_views(self, game);
    game_update_play_background(&game->state.play);
    distance_traveled =
        (long long)(sfSprite_getPosition(self->player.sprite).x / 10);
    text_set_printf(self->distance_text, "%lldm", distance_traveled);
    sfText_setPosition(self->distance_text, (sfVector2f){sfView_getSize(
        game->state.camera).x -
        sfText_getLocalBounds(self->distance_text).width, 0});
    game_update_play_game_over(self, game, distance_traveled);
}
