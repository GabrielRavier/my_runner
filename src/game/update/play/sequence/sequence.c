/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Declares game_update_play_sequence
*/

#include "../internal.h"
#include "internal.h"
#include "../../../object/building_bottom.h"
#include "../../../object/hallway_top.h"
#include "../../../state_play.h"
#include "../../../../game.h"
#include "../../../../random.h"
#include "my/assert.h"
#include "my/ctype.h"
#include "my/macros.h"
#include "my/my_string.h"
#include <SFML/Graphics/View.h>
#include <math.h>

static void do_position_width_height_generation(
    struct game_state_play_sequence *self, const struct game *game,
    int hallway_height, enum game_sequence_object_type type)
{
    int gap = game_update_play_sequence_get_gap(&game->state.play.player);
    float max_j = MY_MIN(self->position.y / 16 - 2 - (float)hallway_height, 6 *
        game->state.play.player.jump_limit / .35f);
    int drop;

    if (max_j > 0)
        max_j = ceilf(max_j - (1 - random_float_between(.0f, 1.f)));
    drop = (int)(random_float_between(.0f, 1.f) *
        MY_MIN(self->height / 16 - 4, 10.f) - max_j);
    if (type == SEQUENCE_OBJECT_TYPE_HALLWAY && gap < 10)
        drop = 0;
    if (drop == 0)
        --drop;
    self->position.x += self->width + (float)gap * 16;
    self->position.y += (float)drop * 16;
    self->position.y = MY_CLAMP(self->position.y, .0f, 480.f);
    self->height = 480 - self->position.y;
    self->width = game_update_play_sequence_get_width(&game->state.play.player,
        gap);
}

static void do_spawn_objects(struct game_state_play_sequence *self,
    struct game *game, enum game_sequence_object_type type, int hallway_height)
{
    struct game_object created_object;

    if (type == SEQUENCE_OBJECT_TYPE_HALLWAY ||
        type == SEQUENCE_OBJECT_TYPE_ROOF) {
        created_object = game_object_create_building_bottom(self);
        game_object_vector_push_back(&game->state.play.objects,
            &created_object);
    }
    if (type == SEQUENCE_OBJECT_TYPE_HALLWAY) {
        created_object = game_object_create_hallway_top(self,
            hallway_height * 16);
        game_object_vector_push_back(&game->state.play.objects,
            &created_object);
    }
}

void game_update_play_sequence(struct game_state_play_sequence *self,
    struct game *game)
{
    enum game_sequence_object_type type;
    int hallway_height = 0;

    while (self->position.x + self->width <=
        sfSprite_getPosition(game->state.play.player.sprite).x +
        sfView_getSize(game->state.camera).x) {
        if (self->current_index < 2)
            type = game_update_play_sequence_get_one_of_first_two(self);
        else
            type = game_update_play_sequence_get_next_object_type(
                self->current_index, game);
        if (type == SEQUENCE_OBJECT_TYPE_HALLWAY)
            hallway_height = game_update_play_sequence_get_hallway_height(
                &game->state.play);
        if (self->current_index >= 2)
            do_position_width_height_generation(self, game, hallway_height,
                type);
        do_spawn_objects(self, game, type, hallway_height);
        ++self->current_index;
    }
}
