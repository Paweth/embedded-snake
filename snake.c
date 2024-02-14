#include "snake.h"

#include <stdlib.h>
#include "DEV_Config.h"
#include "pico/malloc.h"
#include "hardware/gpio.h"
#include "pico/rand.h"
#include "pico/time.h"
#include "GUI_Paint.h"
#include "LCD_1in3.h"

#include "color_palette.h"
#include "drawing.h"
#include "input.h"
#include "vector2.h"
#include "world.h"
#include "game.h"
#include "debug.h"
#include "color_palette.h"
#include "settings.h"

//reverse y direction?
//maps to DIRECTION enum values

struct vector2 direction_vectors[4] = {
    {.x = 0, .y = -1},//up
    {.x = 1, .y = 0},//right
    {.x = 0, .y = 1},//down
    {.x = -1, .y = 0}//left
};
struct snake_body * snake;

void snake_initialize()
{
    snake = malloc(sizeof(struct snake_body));
    snake->head = malloc(sizeof(struct snake_segment));//MALLOC 1
    snake->head->cell = get_cell(CELLS_AMOUNT/2, CELLS_AMOUNT/2);//OLD ERROR: GET_CELL 1

    snake->head->cell->cell_type = CELL_OBSTACLE;//ERROR!

    set_cell_color(snake->head->cell, BLACK);

    snake->tip = malloc(sizeof(struct snake_segment));
    snake->tip->cell = &cells[CELLS_AMOUNT/2][CELLS_AMOUNT/2 - 1];
    snake->tip->cell->cell_type = CELL_OBSTACLE;
    snake->tip->previous = NULL;//is necessary?
    snake->tip->next = snake->head;

    set_cell_color(snake->tip->cell, BLACK);    

    snake->head->previous = snake->tip;
    snake->head->next = NULL;//?

    snake->current_direction = DIRECTION_RIGHT;
}

void snake_create()//alternative snake_initialize
{
    snake = malloc(sizeof(struct snake_body));
    snake->head = malloc(sizeof(struct snake_segment));
    snake->head->cell = get_cell(CELLS_AMOUNT/2, CELLS_AMOUNT/2);
    snake->head->cell->cell_type = CELL_OBSTACLE;
    set_cell_color(snake->head->cell, SNAKE_BODY_COLOR);

    snake->tip = malloc(sizeof(struct snake_segment));
    snake->tip->cell = &cells[CELLS_AMOUNT/2][CELLS_AMOUNT/2 - 1];
    snake->tip->cell->cell_type = CELL_OBSTACLE;
    snake->tip->previous = NULL;//is necessary?
    snake->tip->next = snake->head;
    set_cell_color(snake->tip->cell, SNAKE_BODY_COLOR);    

    snake->head->previous = snake->tip;
    snake->head->next = NULL;//?

    snake->current_direction = settings.snake_initial_direction;
    snake->input_direction = DIRECTION_NONE;

    for(int i = 0; i < settings.snake_initial_length - 2; i++)
    {
        snake_increment();
    }

}

void snake_increment()
{
    //lines 58-60 could be determine_cell_behind method / or make determine_opposite_direction method
    struct vector2 current_direction_vector = direction_vectors[snake->current_direction];
    struct vector2 new_position = vector2_subtract(snake->tip->cell->position, current_direction_vector);
    
    struct cell * new_cell = get_cell(new_position.x, new_position.y);
    snake->tip->previous = malloc(sizeof(struct snake_segment));
    snake->tip->previous->cell = new_cell;
    new_cell->cell_type = CELL_OBSTACLE;
    set_cell_color(new_cell, SNAKE_BODY_COLOR);
    snake->tip->previous->next = snake->tip;
    snake->tip = snake->tip->previous;
    snake->tip->previous = NULL;
}

//void place_snake_segment()
enum DIRECTION check_direction(struct vector2 vector)
{
    for(int i = 0; i < 4; i ++)//loop through all directions
    {
        if(vector2_compare(vector, direction_vectors[i]))
            return i;
    }
    return -1;//DIRECTION_NONE
}

void snake_update_direction()
{
    switch(snake->input_direction)
    {
        case DIRECTION_UP:
        {
            if(snake->current_direction == DIRECTION_RIGHT || snake->current_direction == DIRECTION_LEFT)
            {
                snake->current_direction = DIRECTION_UP;
            }
            break;
        }
        case DIRECTION_DOWN:
        {
            if(snake->current_direction == DIRECTION_RIGHT || snake->current_direction == DIRECTION_LEFT)
            {
                snake->current_direction = DIRECTION_DOWN;
            }
            break;
        }
        case DIRECTION_RIGHT:
        {
            if(snake->current_direction == DIRECTION_UP || snake->current_direction == DIRECTION_DOWN)
            {
                snake->current_direction = DIRECTION_RIGHT;
            }
            break;
        }
        case DIRECTION_LEFT:
        {
            if(snake->current_direction == DIRECTION_UP || snake->current_direction == DIRECTION_DOWN)
            {
                snake->current_direction = DIRECTION_LEFT;
            }
            break;
        }
        case DIRECTION_NONE:
        {
            break;
        }
    }
}

struct cell * determine_cell_ahead(struct cell * cell, enum DIRECTION direction)
{
    struct vector2 new_cell_position = {.x = cell->position.x, .y = cell->position.y};
    switch(direction)
    {
        case(DIRECTION_UP):
        {
            new_cell_position.y = cell->position.y - 1;
            if(new_cell_position.y < 0 && settings.has_border == false)
                new_cell_position.y = CELLS_AMOUNT - 1;
            break;
        }
        case(DIRECTION_DOWN):
        {
            new_cell_position.y = cell->position.y + 1;
            if(new_cell_position.y >= CELLS_AMOUNT && settings.has_border == false)
                new_cell_position.y = 0;            
            break;
        }
        case(DIRECTION_RIGHT):
        {
            new_cell_position.x = cell->position.x + 1;
            if(new_cell_position.x >= CELLS_AMOUNT && settings.has_border == false)
                new_cell_position.x = 0;
            break;
        }
        case(DIRECTION_LEFT):
        {
            new_cell_position.x = cell->position.x - 1;
            if(new_cell_position.x < 0 && settings.has_border == false)
                new_cell_position.x = CELLS_AMOUNT - 1;
            break;
        }
        case(DIRECTION_NONE):
            return NULL;
    }
    return get_cell(new_cell_position.x, new_cell_position.y);
}

bool snake_move()
{
    struct snake_segment * previous_tip = snake->tip;
    struct snake_segment * previous_head = snake->head;
    struct cell * cell_ahead;
    enum CELL_TYPE cell_ahead_type = CELL_OBSTACLE;//type to set
    snake_update_direction();
    //check if tip has CELL_TYPE of FOOD
    cell_ahead = determine_cell_ahead(snake->head->cell, snake->current_direction);//TODO: can't enter cell that is currently occupied by snake but in following snake's move would be freed

    if(!cell_ahead)
    {
        log("error: cell is null");
    }

    if(cell_ahead->cell_type == CELL_OBSTACLE)
    {
        return false;//end of game?
    }
    else if(cell_ahead->cell_type == CELL_FOOD)
    {
        cell_ahead_type = CELL_OBSTACLE | CELL_FOOD;
        place_food();
    }

    //can move ahead/forward
    if(previous_tip->cell->cell_type & CELL_FOOD)
    {
        previous_tip->cell->cell_type = CELL_OBSTACLE;
    }
    else
    {
        previous_tip->cell->cell_type = CELL_EMPTY;
        set_cell_color(previous_tip->cell, BACKGROUND_COLOR);
        snake->tip = snake->tip->next;//new tip
        snake->tip->previous = NULL;
        free(previous_tip);
    }

    snake->head->next = malloc(sizeof(struct snake_segment));
    snake->head = snake->head->next;//new head
    snake->head->previous = previous_head;
    snake->head->next = NULL;
    cell_ahead->cell_type = cell_ahead_type;
    snake->head->cell = cell_ahead;
    set_cell_color(cell_ahead, SNAKE_HEAD_COLOR);

    LCD_1IN3_Display(BlackImage);//should be invoked in update_frame? (if true)
    return true;
}

void snake_destroy()
{
    struct snake_segment * current = snake->tip;
    struct snake_segment * next = snake->tip;
    // snake->head = NULL;
    // snake->tip = NULL;
    while(next != NULL)
    {
        current = next;
        next = current->next;
        // log("%p", (void*)current);
        free(current);
    }
    free(snake);
    snake = NULL;
    
}