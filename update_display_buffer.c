#include"update_displayer_buffer.h"

void display_map(const struct Coord* map_pixels, int map_size, uint8_t display_buffer[4][128]){
    int i, xCoord, yCoord, page;
    for(i = 0; i < map_size; i++){
        xCoord = map_pixels[i].x;
        yCoord = map_pixels[i].y;
        page = yCoord / 8;
        yCoord %= 8;
        display_buffer[page][xCoord] |= ((uint8_t)1 << yCoord);
    }
}

void update_entity(const struct Coord* entity_pixels, int entity_size, int x, int y, uint8_t display_buffer[4][128])
{
    int i, xCoord, yCoord, page;
    for(i = 0; i < entity_size; i++){
        xCoord = entity_pixels[i].x + x;
        yCoord = entity_pixels[i].y + y;

        if(xCoord < 0 || xCoord > 127 || yCoord < 0 || yCoord > 31) continue;

        page = yCoord / 8;
        yCoord %= 8;
        display_buffer[page][xCoord] |= ((uint8_t)1 << yCoord);
    }
}

void clear_entity(const struct Coord* entity_pixels, int entity_size, int x, int y, uint8_t display_buffer[4][128])
{
    int i, xCoord, yCoord, page;
    for(i = 0; i < entity_size; i++){
        xCoord = entity_pixels[i].x + x;
        yCoord = entity_pixels[i].y + y;

        if(xCoord < 0 || xCoord > 127 || yCoord < 0 || yCoord > 31) continue;

        page = yCoord / 8;
        yCoord %= 8;
        display_buffer[page][xCoord] &= ~((uint8_t)1<<yCoord);
    }
}

void clear_buffer(uint8_t display_buffer[4][128]){
    int i, j;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 128; j++){
            display_buffer[i][j] = 0;
        }
    }
}