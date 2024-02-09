#include "snake.h"

#include <stdlib.h>
#include "pico/malloc.h"
#include "hardware/gpio.h"
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

void snake_increase_length()
{
    //if (tip->next - tip: determine direction where to generate cell)
    if(snake->tip == NULL)//has only head
    {
        // if(snake->head->previous == NULL);
        snake->tip = malloc(sizeof(struct snake_segment));
        snake->head->previous = snake->tip;
        snake->tip->next = snake->head;
        struct vector2 new_cell_coords = {
            .x = snake->head->cell->position.x,
            .y = snake->head->cell->position.y};
        // get_cell(int x, int y) 
        // set_cell_color(, SNAKE_BODY_COLOR);
    }
    else //has tip
    {
        
    }
}

void snake_create()//alternative snake_initialize
{
    snake = malloc(sizeof(struct snake_body));
    snake->head = malloc(sizeof(struct snake_segment));
    snake->head->cell = get_cell(CELLS_AMOUNT/2, CELLS_AMOUNT/2);

    snake->head->cell->cell_type = CELL_OBSTACLE;

    set_cell_color(snake->head->cell, SNAKE_BODY_COLOR);

    //loop n-times snake_increase_length()

    snake->tip = malloc(sizeof(struct snake_segment));
    snake->tip->cell = &cells[CELLS_AMOUNT/2][CELLS_AMOUNT/2 - 1];
    snake->tip->cell->cell_type = CELL_OBSTACLE;
    snake->tip->previous = NULL;//is necessary?
    snake->tip->next = snake->head;

    set_cell_color(snake->tip->cell, SNAKE_BODY_COLOR);    

    snake->head->previous = snake->tip;
    snake->head->next = NULL;//?

    snake->current_direction = settings.snake_initial_direction;    
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
void update_direction(int direction)
{
    switch(direction)
    {
        case(DIRECTION_UP):
        {
            if(snake->current_direction == DIRECTION_RIGHT || snake->current_direction == DIRECTION_LEFT)
            {
                snake->current_direction = DIRECTION_UP;
            }
            break;
        }
        case(DIRECTION_DOWN):
        {
            if(snake->current_direction == DIRECTION_RIGHT || snake->current_direction == DIRECTION_LEFT)
            {
                snake->current_direction = DIRECTION_DOWN;
            }
            break;
        }
        case(DIRECTION_RIGHT):
        {
            if(snake->current_direction == DIRECTION_UP || snake->current_direction == DIRECTION_DOWN)
            {
                snake->current_direction = DIRECTION_RIGHT;
            }
            break;
        }
        case(DIRECTION_LEFT):
        {
            if(snake->current_direction == DIRECTION_UP || snake->current_direction == DIRECTION_DOWN)
            {
                snake->current_direction = DIRECTION_LEFT;
            }
            break;
        }
    }
}

struct cell * determine_cell_ahead()
{
    struct cell * current_cell = snake->head->cell;
    struct vector2 new_cell_position = {.x = current_cell->position.x, .y = current_cell->position.y};
    switch(snake->current_direction)
    {
        case(DIRECTION_UP):
        {
            new_cell_position.y = current_cell->position.y - 1;
            if(new_cell_position.y >= CELLS_AMOUNT)
                return NULL;
            break;
        }
        case(DIRECTION_DOWN):
        {
            new_cell_position.y = current_cell->position.y + 1;
            if(new_cell_position.y < 0)
            {
                if(settings.has_border)//impossible situation (border has cells that would cause collision before position.y would be so low)
                {
                    return NULL;
                }
                else //go to the other side of wall (+ invert direction)
                {
                    return NULL;
                }
            }                
            break;
        }
        case(DIRECTION_RIGHT):
        {
            new_cell_position.x = current_cell->position.x + 1;
            if(new_cell_position.x >= CELLS_AMOUNT)
                return NULL;
            break;
        }
        case(DIRECTION_LEFT):
        {
            new_cell_position.x = current_cell->position.x - 1;
            if(new_cell_position.x < 0)
                return NULL;
            break;
        }
    }
    struct cell * new_cell = get_cell(new_cell_position.x, new_cell_position.y);
    return new_cell;
}

bool snake_move()
{
    struct snake_segment * previous_tip = snake->tip;
    struct snake_segment * previous_head = snake->head;
    struct cell * cell_ahead;

    cell_ahead = determine_cell_ahead();

    if(!cell_ahead || cell_ahead->cell_type == CELL_OBSTACLE)
    {
        log("end game");
        while(1);
        return false;//end of game?
    }

    //can move ahead/forward
    previous_tip->cell->cell_type = CELL_EMPTY;
    set_cell_color(previous_tip->cell, BACKGROUND_COLOR);
    snake->tip = snake->tip->next;//new tip
    snake->tip->previous = NULL;
    free(previous_tip);

    snake->head->next = malloc(sizeof(struct snake_segment));
    snake->head = snake->head->next;//new head
    snake->head->previous = previous_head;
    cell_ahead->cell_type = CELL_OBSTACLE;
    snake->head->cell = cell_ahead;
    set_cell_color(cell_ahead, SNAKE_HEAD_COLOR);
    LCD_1IN3_Display(BlackImage);
    return true;
}

