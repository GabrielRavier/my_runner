/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines qsort_r
*/

#include "my/stdlib.h"
#include "my/string.h"
#include "my/cpp-like/algorithm.h"
#include "my/features.h"

MY_ATTR_ACCESS((read_write, 1, 3)) MY_ATTR_ACCESS((read_write, 2, 3))
MY_ATTR_NONNULL((1, 2)) static void swap_elements(char *elem1, char *elem2,
    size_t element_size)
{
    char buffer[1000];
    size_t copy_size;

    while (element_size) {
        copy_size = MY_MIN(sizeof(buffer), element_size);
        my_memcpy(buffer, elem1, copy_size);
        my_memcpy(elem1, elem2, copy_size);
        my_memcpy(elem2, buffer, copy_size);
        elem1 += copy_size;
        elem2 += copy_size;
        element_size -= copy_size;
    }
}

static void qsort_fix(char *base, size_t start, size_t num, size_t element_size,
    int (*comparison_function)(const void *, const void *, void *),
    void *argument)
{
    size_t max;

    while (start * 2 <= num) {
        max = start * 2;
        if (max < num && comparison_function(base + max * element_size,
            base + (max + 1) * element_size, argument) < 0)
            ++max;
        if (max && comparison_function(base + start * element_size,
            base + max * element_size, argument) < 0) {
            swap_elements(base + start * element_size,
                base + max * element_size, element_size);
            start = max;
        } else
            break;
    }
}

void my_qsort_r(void *base, size_t num_elements, size_t element_size,
    int (*comparison_function)(const void *, const void *, void *),
    void *argument)
{
    if (num_elements <= 1)
        return;
    for (size_t i = (num_elements + 1) >> 1; i != 0; --i)
        qsort_fix((char *)base, i - 1, num_elements - 1, element_size,
            comparison_function, argument);
    for (size_t i = num_elements - 1; i != 0; --i) {
        swap_elements((char *)base, (char *)base + i * element_size,
            element_size);
        qsort_fix((char *)base, 0, i - 1, element_size, comparison_function,
            argument);
    }
}
