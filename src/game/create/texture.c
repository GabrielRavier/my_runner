/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_create_texture
*/

#include "internal.h"
#include <SFML/Graphics/Texture.h>

bool game_create_texture(sfTexture **texture, const char *filename)
{
    *texture = sfTexture_createFromFile(filename, NULL);
    return (*texture != NULL);
}
