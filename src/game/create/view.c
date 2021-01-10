/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_create_view
*/

#include "internal.h"
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/View.h>

bool game_create_view(sfView **view, const sfRenderWindow *window)
{
    *view = sfView_copy(sfRenderWindow_getDefaultView(window));
    return (*view != NULL);
}
