#include "game.h"

#include <stdbool.h>
#include <time.h>
#include "GUI_Paint.h"
#include "LCD_1in3.h"
#include "pico/stdlib.h"

#include "world.h"
#include "snake.h"
#include "debug.h"
#include "settings.h"
#include "input.h"
/*

frames / speed? : events should happen not every frame - last clicked action (button) should be remembered and last should be applied at the beggining of loop

*/
struct settings settings;
struct snake_body * snake;
struct cell cells[CELLS_AMOUNT][CELLS_AMOUNT];


int color = GREEN;

void game_initialize()
{
    // unsigned int iseed = (unsigned int)time(NULL);
    // srand (iseed);
    settings.has_border = true;
    settings.speed = 1000;
    settings.snake_initial_direction = DIRECTION_RIGHT;
    settings.snake_initial_length = 8;

    world_initialize();
    snake_create();

}



bool update_frame()
{
    if(color == GREEN)
    {
        color = BLUE;
    }
    else color = GREEN;
    //if(can_move == false) //restart game?
    
    bool can_move = snake_move();
    // LCD_1IN3_Clear(color);
    return can_move;
}

//void game_restart()
//void pause_game //cancel_repeating_timer
//resume_game //add_repeating_timer

struct repeating_timer timer;

//place food (uses draw_food)



void game_run()
{

    add_repeating_timer_ms(settings.speed, update_frame, NULL, &timer);

    while(1)//input check
    {
        check_input();
    }
}

