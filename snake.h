#pragma once

#include "pico/types.h"
struct snake_segment
{
    struct cell * cell;
    struct snake_segment * previous;
    struct snake_segment * next;
};

//funkcja move_cell (move_snake(dir)??)która zapali odpowiednią komórkę oraz 

enum DIRECTION
{
    DIRECTION_TOP,
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

extern struct snake_body * snake;
void snake_initialize();
void update_direction();
struct cell * determine_cell_ahead();
bool snake_move();