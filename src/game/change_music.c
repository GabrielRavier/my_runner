/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_change_music
*/

#include "change_music.h"
#include "my/assert.h"
#include <SFML/Audio/Music.h>

void game_change_music(sfMusic **self, const char *music_name)
{
    sfMusic_destroy(*self);
    *self = sfMusic_createFromFile(music_name);
    MY_ASSERT(*self != NULL);
    sfMusic_play(*self);
    sfMusic_setLoop(*self, sfTrue);
}
