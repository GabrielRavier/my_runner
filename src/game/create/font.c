/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_create_font
*/

#include "internal.h"
#include <SFML/Graphics/Font.h>

bool game_create_font(sfFont **font, const char *filename)
{
    *font = sfFont_createFromFile(filename);
    return (*font != NULL);
}
