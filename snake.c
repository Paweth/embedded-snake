#include "snake.h"
#include "GUI_Paint.h"
#include "LCD_1in3.h"
#include "drawing.h"
#include "pico/malloc.h"
#include <stdlib.h>
#include "pico/time.h"
#include "world.h"
#include "game.h"
#include "debug.h"

void snake_initialize()
{
    //snake = malloc(sizeof(struct snake_body)); case when snake isn't global
    // log("snake_init: before MALLOC 1");
    snake->head = malloc(sizeof(struct snake_segment));//MALLOC 1
    snake->head->cell = get_cell(CELLS_AMOUNT/2, CELLS_AMOUNT/2);//OLD ERROR: GET_CELL 1
    // log("snake_init: after GET_CELL 1");
    // log("s_init: after get_cell");
    //LCD_1IN3_Clear(RED);
    //snake->head->cell = &cells[CELLS_AMOUNT/2][CELLS_AMOUNT/2];

    snake->head->cell->cell_type = CELL_OBSTACLE;//ERROR!
    
    
    // LCD_1IN3_Clear(YELLOW);
    // log("snake_init: before set_cell_color");
    DEV_Delay_ms(1000);
    set_cell_color(snake->head->cell, BLACK);
    // log("snake_init: after set_cell_color");
    DEV_Delay_ms(1000);
    snake->tip = malloc(sizeof(struct snake_segment));
    snake->tip->cell = &cells[CELLS_AMOUNT/2][CELLS_AMOUNT/2 - 1];
    snake->tip->cell->cell_type = CELL_OBSTACLE;
    snake->tip->previous = NULL;//is necessary?
    snake->tip->next = snake->head;
    // log("snake_init: before set_cell_color()");
    DEV_Delay_ms(1000);
    set_cell_color(snake->tip->cell, BLACK);    
    // log("snake_init: after tip allocation");
    DEV_Delay_ms(1000);
    snake->head->previous = snake->tip;
    snake->head->next = NULL;//?

    snake->current_direction = DIRECTION_RIGHT;

}

//void place_snake_segment()

void update_direction()
{
    switch(snake->current_direction)
    {
        case(DIRECTION_TOP):
        {
            if(snake->current_direction == DIRECTION_RIGHT || snake->current_direction == DIRECTION_LEFT)
            {
                snake->current_direction = DIRECTION_TOP;
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
            if(snake->current_direction == DIRECTION_TOP || snake->current_direction == DIRECTION_DOWN)
            {
                snake->current_direction = DIRECTION_RIGHT;
            }
            break;
        }
        case(DIRECTION_LEFT):
        {
            if(snake->current_direction == DIRECTION_TOP || snake->current_direction == DIRECTION_DOWN)
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
        case(DIRECTION_TOP):
        {
            new_cell_position.y = current_cell->position.y + 1;
            if(new_cell_position.y >= CELLS_AMOUNT)
                return NULL;
            break;
        }
        case(DIRECTION_DOWN):
        {
            new_cell_position.y = current_cell->position.y - 1;
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

    log("snake_move: after declarations");

    update_direction(snake);
    log("snake_move: after update_direction");
    cell_ahead = determine_cell_ahead();
    log("snake_move: after determine_cell_ahead");
    if(cell_ahead == NULL)
    {
        return false;//end of game?
    }

    if(cell_ahead->cell_type == CELL_OBSTACLE)
    {
        return false;//end of game
    }

    //can move ahead/forward
    previous_tip->cell->cell_type = CELL_EMPTY;
    set_cell_color(previous_tip->cell, WHITE);
    snake->tip = snake->tip->next;//new tip
    snake->tip->previous = NULL;
    free(previous_tip);

    snake->head->next = malloc(sizeof(struct snake_segment));
    snake->head = snake->head->next;//new head
    snake->head->previous = previous_head;
    cell_ahead->cell_type = CELL_OBSTACLE;
    snake->head->cell = cell_ahead;
    set_cell_color(cell_ahead, BLACK);
    log("snake_move: after everything");
    return true;
}

