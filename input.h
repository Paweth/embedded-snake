#pragma once

#include "pico/types.h"

enum GPIO_PINS
{
    JOYSTICK_UP_PIN = 2,
    JOYSTICK_DOWN_PIN = 18,
    JOYSTICK_RIGHT_PIN = 20,
    JOYSTICK_LEFT_PIN = 16,
};

void on_joystick_up(uint gpio, uint32_t event_mask);
void on_joystick_down(uint gpio, uint32_t event_mask);
void on_joystick_right(uint gpio, uint32_t event_mask);
void on_joystick_left(uint gpio, uint32_t event_mask);
void check_input();