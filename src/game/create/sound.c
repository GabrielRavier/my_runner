/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_create_sound
*/

#include "internal.h"
#include "../sound_with_buffer.h"
#include <SFML/Audio/Sound.h>
#include <SFML/Audio/SoundBuffer.h>

bool game_create_sound(struct sound_with_buffer *sound,
    const char *filename)
{
    sound->buffer = sfSoundBuffer_createFromFile(filename);
    if (sound->buffer == NULL)
        return (false);
    sound->sf_sound = sfSound_create();
    if (sound->sf_sound == NULL)
        return (false);
    sfSound_setBuffer(sound->sf_sound, sound->buffer);
    return (true);
}
