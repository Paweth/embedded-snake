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
    DIRECTION_UP = 0,
    DIRECTION_RIGHT = 1,
    DIRECTION_DOWN = 2,
    DIRECTION_LEFT = 3
};

struct snake_body
{
    enum DIRECTION current_direction;
    enum DIRECTION input_direction;
    struct snake_segment * head;
    struct snake_segment * tip;
};

extern struct vector2 direction_vectors[4];
extern struct snake_body * snake;

void snake_initialize();
void snake_create();
void snake_increment();
enum DIRECTION check_direction(struct vector2 vector);
void snake_update_direction();
struct cell * determine_cell_ahead(struct cell * cell, enum DIRECTION direction);
bool snake_move();