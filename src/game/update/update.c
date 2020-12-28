/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_update
*/

#include "../update.h"
#include "my/macros.h"
#include <SFML/Graphics/View.h>
#include <math.h>

// The camera panning stops after ~100 frames
static void game_update_menu(struct game *self)
{
    sfVector2f camera_center = {480 / 2, (320 / 2) - 10};

    camera_center.y += (100000.f /
        (powf(self->state.frames_since_mode_begin + 10, 2)));
    camera_center.y = MY_MAX(camera_center.y, (320 / 2));
    sfView_setCenter(self->state.camera, camera_center);
}

void game_update(struct game *self)
{
    ++self->state.frames_since_mode_begin;
    if (self->state.mode == GAME_MODE_MENU)
        game_update_menu(self);
}
