/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares parse_argv
*/

#pragma once

#include <stdbool.h>

struct arguments {
    unsigned framerate;
    unsigned resolution_multiplier;
};

bool parse_argv(int argc, char **argv, struct arguments *args);
