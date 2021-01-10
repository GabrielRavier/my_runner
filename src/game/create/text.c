/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Declares game_create_text
*/

#include "internal.h"
#include "../../game.h"
#include <SFML/Graphics/Text.h>

bool game_create_text(sfText **text, const struct game *game)
{
    *text = sfText_create();
    if (*text == NULL)
        return (false);
    sfText_setFont(*text, game->resources.nokia_font);
    sfText_setCharacterSize(*text, 10);
    return (true);
}
