/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_set_mode
*/

#include "mode.h"
#include "../change_music.h"
#include <SFML/Audio/Music.h>
#include <SFML/Graphics/View.h>

void game_set_mode(struct game *self, enum game_mode mode)
{
    self->state.mode = mode;
    self->state.frames_since_mode_begin = 0;
    if (self->state.mode == GAME_MODE_MENU) {
        game_change_music(&self->state.music, "assets/title.ogg");
        sfMusic_setLoop(self->state.music, sfTrue);
    }
}
