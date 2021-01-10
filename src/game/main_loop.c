/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_main_loop
*/

#include "main_loop.h"
#include "draw.h"
#include "update.h"
#include "handle/key.h"
#include "set/mode.h"
#include "../game.h"
#include "my/stdio.h"
#include "my/assert.h"
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Window/Event.h>
#include <SFML/System/Clock.h>
#include <unistd.h>
#include <stdint.h>

static void do_events(struct game *self)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(self->window, &event)) {
        if (event.type == sfEvtClosed || (event.type == sfEvtKeyPressed &&
            event.key.code == sfKeyEscape))
            sfRenderWindow_close(self->window);
        if (event.type == sfEvtKeyPressed)
            game_handle_key(self, event.key.code);
    }
}

static void do_updates_until_all_dropped_frames_done(struct game *self,
    sfClock *clock, int64_t *elapsed_time)
{
    static const int64_t one_frame_in_microseconds = 17000;

    *elapsed_time += sfClock_getElapsedTime(clock).microseconds;
    sfClock_restart(clock);
    game_update(self);
    *elapsed_time -= one_frame_in_microseconds;
    while (*elapsed_time > 0) {
        game_update(self);
        *elapsed_time -= one_frame_in_microseconds;
    }
    game_draw(self);
}

void game_main_loop(struct game *self)
{
    sfClock *clock = sfClock_create();
    int64_t elapsed_time = 0;

    MY_ASSERT(clock != NULL);
    game_set_mode(self, GAME_MODE_TITLE);
    while (sfRenderWindow_isOpen(self->window)) {
        do_events(self);
        do_updates_until_all_dropped_frames_done(self, clock, &elapsed_time);
        sfRenderWindow_display(self->window);
    }
    sfClock_destroy(clock);
}
