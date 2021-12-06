#ifndef DRAW_TO_DISPLAY_H
#define DRAW_TO_DISPLAY_H

#include"pic32mx.h"
#include<stdint.h>
#include"helper_functions.h"

void display_update(uint8_t display_buffer[4][128]);

#endif