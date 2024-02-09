#include "vector2.h"

struct vector2 vector2_subtract(struct vector2 vec1, struct vector2 vec2)
{
    struct vector2 result = {.x = vec1.x - vec2.x, .y = vec1.y - vec2.y};
    return result;
}

bool vector2_compare(struct vector2 vec1, struct vector2 vec2)
{
    return (vec1.x == vec2.x && vec1.y == vec2.y) ? true: false;
}