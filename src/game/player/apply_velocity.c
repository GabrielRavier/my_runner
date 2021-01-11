/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_player_apply_velocity
*/

#include "internal.h"
#include "../is_jumping.h"
#include "../player.h"
#include "../object.h"
#include "../../game.h"
#include "my/features.h"
#include <SFML/Audio/Sound.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/System/Vector2.h>
#include <math.h>

struct collision_handling_state {
    sfVector2f position;
    sfVector2f position_after;
    sfFloatRect rect_after;
    sfFloatRect intersection;
};

static void do_bottom_collision(struct game_player *self,
    MY_ATTR_UNUSED struct game *game)
{
    if (!game_is_jumping())
        self->jump = .0f;
    self->on_floor = true;
}

static void do_left_collision(struct game_player *self, struct game *game)
{
    sfSound_play(game->resources.sounds.wall.sf_sound);
    self->acceleration.x = 0;
    self->velocity.x = 0;
    self->max_velocity.y = 1000;
}

static void handle_collision(struct game_player *self, struct game *game,
    struct collision_handling_state *state, struct game_object *i)
{
    if (self->velocity.y > 0 && state->position.y < i->rect.top) {
        do_bottom_collision(self, game);
        state->position_after.y -= state->intersection.height;
        self->velocity.y = 0;
        return;
    }
    if (self->velocity.x > 0 && state->position.x < i->rect.left) {
        do_left_collision(self, game);
        state->position_after.x -= state->intersection.width + 2.f;
        self->velocity.x = 0;
        return;
    }
    if (self->velocity.y < 0 && (state->position.y +
        state->rect_after.height) > i->rect.top + i->rect.height) {
        state->position_after.y += state->intersection.height;
        self->velocity.y = 0;
        return;
    }
}

void game_player_apply_velocity(struct game_player *self, struct game *game)
{
    struct collision_handling_state state = {
        .position = sfSprite_getPosition(self->sprite),
        .position_after = {state.position.x + self->velocity.x,
            state.position.y + self->velocity.y}
    };
    struct game_object *i;

    sfSprite_setPosition(self->sprite, state.position_after);
    state.rect_after = sfSprite_getGlobalBounds(self->sprite);
    GAME_OBJECT_VECTOR_FOR_EACH(&game->state.play.objects, i)
        if (sfFloatRect_intersects(&i->rect, &state.rect_after,
            &state.intersection))
            handle_collision(self, game, &state, i);
    if (ceilf(state.position_after.y) != ceilf(state.position.y)) {
        state.position_after.y = ceilf(state.position_after.y);
        self->on_floor = false;
    }
    sfSprite_setPosition(self->sprite, state.position_after);
}
