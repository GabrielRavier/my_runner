/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_create_sprite
*/

#include "internal.h"
#include <SFML/Graphics/Sprite.h>
#include <stddef.h>

bool game_create_sprite(sfSprite **sprite, const sfTexture *texture)
{
    *sprite = sfSprite_create();
    if (*sprite == NULL)
        return (false);
    sfSprite_setTexture(*sprite, texture, sfTrue);
    return (true);
}
