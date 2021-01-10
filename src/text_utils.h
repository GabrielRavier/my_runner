/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares text-related utilities
*/

#pragma once

#include "my/features.h"
#include <SFML/Graphics/Types.h>

MY_ATTR_FORMAT(printf, 2, 3) void text_set_printf(sfText *text, const char *format, ...);
