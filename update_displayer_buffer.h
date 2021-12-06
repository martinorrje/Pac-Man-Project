#ifndef UPDATE_DISPLAY_BUFFER_H
#define UPDATE_DISPLAY_BUFFER_H

#include<stdint.h>
#include"structs.h"

void update_entity(const struct Coord* entity_pixels, int entity_size, int x, int y, uint8_t display_buffer[4][128]);

void clear_entity(const struct Coord* entity_pixels, int entity_size, int x, int y, uint8_t display_buffer[4][128]);

void display_map(const struct Coord* entity_pixels, int mapSize, uint8_t display_buffer[4][128]);

void clear_buffer(uint8_t display_buffer[4][128]);

#endif