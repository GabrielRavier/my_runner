/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines random.h entities
*/

#include "random.h"
#include "my/assert.h"
#include <stdlib.h>

static unsigned rand_at_most(unsigned max)
{
    const unsigned num_bins = max + 1;
    const unsigned num_rand = (unsigned)RAND_MAX + 1;
    const unsigned bin_size = num_rand / num_bins;
    const unsigned defect = num_rand % num_bins;
    unsigned x;

    MY_ASSERT(max < RAND_MAX);
    do {
        x = (unsigned)rand();
    } while (num_rand - defect <= (unsigned)x);
    return (x / bin_size);
}

int random_int_between(int min, int max)
{
    const unsigned range = (unsigned)(max - min);

    MY_ASSERT(min <= max);
    return ((int)rand_at_most(range) + min);
}

float random_float_between(float min, float max)
{
    const float scale = (float)rand() / (float)RAND_MAX;

    MY_ASSERT(min <= max);
    return min + scale * (max - min);
}
