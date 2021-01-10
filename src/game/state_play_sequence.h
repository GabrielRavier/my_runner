/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Declares state_play_sequence
*/

#pragma once

#include <SFML/System/Vector2.h>
#include <stddef.h>

enum sequence_object_type {
    SEQUENCE_OBJECT_TYPE_HALLWAY,
    SEQUENCE_OBJECT_TYPE_ROOF,
    SEQUENCE_OBJECT_TYPE_FIRST = SEQUENCE_OBJECT_TYPE_HALLWAY,
    SEQUENCE_OBJECT_TYPE_LAST = SEQUENCE_OBJECT_TYPE_ROOF,
};

struct game_state_play_sequence {
    size_t current_index;
    size_t next_type;
    sfVector2f position;
    float width;
    float height;
};
