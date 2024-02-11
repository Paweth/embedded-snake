#include "game.h"

#include <stdbool.h>
#include "stdlib.h"
#include <time.h>
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "LCD_1in3.h"
#include "pico/stdlib.h"
#include "pico/rand.h"

#include "world.h"
#include "snake.h"
#include "debug.h"
#include "settings.h"
#include "input.h"
/*

frames / speed? : events should happen not every frame - last clicked action (button) should be remembered and last should be applied at the beggining of loop

*/
struct settings settings;

int color = GREEN;

void game_initialize()
{
    // unsigned int iseed = (unsigned int)time(NULL);
    log("%u", (unsigned int)get_rand_32());
    DEV_Delay_ms(2000);
    settings.has_border = true;
    settings.speed = 8;
    settings.snake_initial_direction = DIRECTION_RIGHT;
    settings.snake_initial_length = 8;

    world_initialize();
    snake_create();
    place_food();
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
    if(can_move == false)
    {
        log("open menu");
    }
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
    add_repeating_timer_ms(1000/(settings.speed + settings.speed*settings.speed), update_frame, NULL, &timer);

    while(1)//input check
    {
        check_input();
    }
}

