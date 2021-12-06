#ifndef GAME_H
#define GAME_H

#include<stdint.h>
#include"draw_to_display.h"
#include"structs.h"
#include"math.h"

#define map_size 426

//pacman_anim_state will be either 0 or 1, and depending on its value, pacman will have an open or closed mouth
int pacman_anim_state;

int pacmanX;

int pacmanY;

struct Ghost Inky;
struct Ghost Blinky;
struct Ghost Pinky;
struct Ghost Clyde;

uint8_t display_buffer[4][128];

enum Direction pacmanDirection;

void pacman_animation();

void update_pacman();

void update_ghost();

void game_init();

void user_isr( void ); 

void enable_interrupt(void);

extern const struct Coord const pacmanOpen[4][8];
extern const struct Coord const pacmanClosed[12];
extern const int mapPoints[32][128];
extern const struct Coord const ghostPixels[14];

extern const struct Coord const map[map_size];

void draw_pacman(int x, int y);

void remove_pacman();

void draw_map();

void check_button_pressed();

#endif