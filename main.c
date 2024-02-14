#include <stdbool.h>
#include <stdio.h>
#include "hardware/gpio.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "LCD_1in3.h"

#include "input.h"
#include "game.h"
#include "world.h"
#include "debug.h"

UWORD *BlackImage;

int main()
{
    // gpio_init(JOYSTICK_UP_PIN);
    // gpio_init(JOYSTICK_DOWN_PIN);
    // gpio_init(JOYSTICK_RIGHT_PIN);
    // gpio_init(JOYSTICK_LEFT_PIN);
    // gpio_set_dir(JOYSTICK_UP_PIN, GPIO_IN);
    // gpio_set_dir(JOYSTICK_DOWN_PIN, GPIO_IN);
    // gpio_set_dir(JOYSTICK_RIGHT_PIN, GPIO_IN);
    // gpio_set_dir(JOYSTICK_LEFT_PIN, GPIO_IN);

    if(DEV_Module_Init() != 0)
    {
        return -1;
    }
    LCD_1IN3_Init(HORIZONTAL);
    LCD_1IN3_Clear(WHITE);
    gpio_pull_up(JOYSTICK_UP_PIN);
    gpio_pull_up(JOYSTICK_DOWN_PIN);
    gpio_pull_up(JOYSTICK_RIGHT_PIN);
    gpio_pull_up(JOYSTICK_LEFT_PIN);
    gpio_pull_up(USER_KEY_A_PIN);

    gpio_set_irq_enabled_with_callback(JOYSTICK_UP_PIN, GPIO_IRQ_EDGE_FALL, true, check_input);
    gpio_set_irq_enabled_with_callback(JOYSTICK_DOWN_PIN, GPIO_IRQ_EDGE_FALL, true, check_input);
    gpio_set_irq_enabled_with_callback(JOYSTICK_RIGHT_PIN, GPIO_IRQ_EDGE_FALL, true, check_input);
    gpio_set_irq_enabled_with_callback(JOYSTICK_LEFT_PIN, GPIO_IRQ_EDGE_FALL, true, check_input);
    gpio_set_irq_enabled_with_callback(USER_KEY_A_PIN, GPIO_IRQ_EDGE_FALL, true, check_input);

    UDOUBLE Imagesize = LCD_1IN3_HEIGHT*LCD_1IN3_WIDTH*2;
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        LCD_1IN3_Clear(RED);
        while(1);
        // exit(0);
    }
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    
    Paint_NewImage((UBYTE *)BlackImage,LCD_1IN3.WIDTH,LCD_1IN3.HEIGHT, 0, WHITE);
    Paint_SetScale(65);
    Paint_Clear(WHITE);

    game_initialize();//settings

    game_run();

    while (1);
    return 0;
}