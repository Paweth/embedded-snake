#pragma once

#include "pico/types.h"

#include "world.h"
#include "vector2.h"

struct snake_segment
{
    struct cell * cell;
    struct snake_segment * previous;
    struct snake_segment * next;
};

//funkcja move_cell (move_snake(dir)??)która zapali odpowiednią komórkę oraz 

enum DIRECTION
{
    DIRECTION_NONE = -1,
    DIRECTION_UP,
    DIRECTION_RIGHT,
    DIRECTION_DOWN,
    DIRECTION_LEFT
};

struct snake_body
{
    enum DIRECTION current_direction;
    struct snake_segment * head;
    struct snake_segment * tip;
};

extern struct vector2 direction_vectors[4];
extern struct snake_body * snake;

void snake_initialize();
enum DIRECTION check_direction(struct vector2 vector);
void update_direction(int direction);
struct cell * determine_cell_ahead();
bool snake_move();