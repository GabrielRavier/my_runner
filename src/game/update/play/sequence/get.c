/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_update_play_sequence_get methods
*/

#include "internal.h"
#include "../../../state_play.h"
#include "../../../../game.h"
#include "../../../../random.h"
#include "my/assert.h"
#include "my/ctype.h"
#include "my/cpp-like/algorithm.h"
#include "my/my_string.h"
#include <math.h>

int game_update_play_sequence_get_hallway_height(
    const struct game_state_play *self)
{
    float velocity_x = self->player.velocity.x;

    if (velocity_x > 8.4f)
        return (7);
    if (velocity_x > 6.8f)
        return (6);
    if (velocity_x > 4.2f)
        return (5);
    if (self->sequence.current_index > 0)
        return (4);
    return (3);
}

int game_update_play_sequence_get_gap(const struct game_player *self)
{
    float max_gap = ((self->velocity.x * 65.f) / 20.f) * .75f;

    return ((int)random_float_between(MY_MAX(max_gap * .4f, 4.f),
        MY_MAX(max_gap, 4.f)));
}

float game_update_play_sequence_get_width(const struct game_player *self,
    int gap)
{
    float min_width = (ceilf(480.f / 16.f) + 2) - (float)gap;
    float max_width;

    if ((min_width < 15) && self->velocity.x < self->max_velocity.x * .8f)
        min_width = 15;
    min_width = MY_MAX(min_width, 6.f);
    max_width = min_width * 2;
    return (floorf(min_width + random_float_between(.0f, 1.f) * max_width) *
        16);
}

enum game_sequence_object_type game_update_play_sequence_get_next_object_type(
    size_t current_index, const struct game *game)
{
    char map_character;

    if (current_index < 2)
        return (SEQUENCE_OBJECT_TYPE_FIRST);
    if ((current_index - 2) < game->map->length) {
        map_character = (char)my_tolower(game->map->string[current_index - 2]);
        if (map_character == 'r')
            return (SEQUENCE_OBJECT_TYPE_ROOF);
        if (map_character == 'h')
            return (SEQUENCE_OBJECT_TYPE_HALLWAY);
    }
    return ((enum game_sequence_object_type)random_int_between(
        SEQUENCE_OBJECT_TYPE_FIRST, SEQUENCE_OBJECT_TYPE_LAST));
}

enum game_sequence_object_type game_update_play_sequence_get_one_of_first_two(
    struct game_state_play_sequence *self)
{
    if (self->current_index == 0) {
        self->position.x = -100000;
        self->position.y = 90;
        self->width = 840 - self->position.x;
        self->height = 480 - 90;
        return (SEQUENCE_OBJECT_TYPE_HALLWAY);
    }
    if (self->current_index == 1) {
        self->position.x += self->width + 160;
        self->position.y = 240;
        self->width = 42 * 16;
        self->height = 480 - 240;
        return (SEQUENCE_OBJECT_TYPE_ROOF);
    }
    MY_ASSERT(false && "Called get_one_of_first_two with invalid index");
}
