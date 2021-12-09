#ifndef GAME_H
#define GAME_H

#include<stdint.h>
#include"draw_to_display.h"
#include"update_display_buffer.h"
#include"structs.h"
#include"helper_functions.h"
#include"math.h"

int game_over;

int scatterTimer;
int chaseTimer;
int scatterCount;
int timer;
int chaseMode;      //1 if the ghosts are in chase mode, 0 if they are in scatter mode
int frightenedMode;         //TODO implement frightened mode

//pacman_anim_state will be either 0 or 1, and depending on its value, pacman will have an open or closed mouth
int pacman_anim_state;

int pacmanX;

int pacmanY;

int score;

struct Ghost Inky;
struct Ghost Blinky;
struct Ghost Pinky;

uint8_t display_buffer[4][128];

enum Direction pacmanDirection;

void eat_food(int x, int y);
void eat_superfood(int x, int y);

void update_pacman();

void update_ghost();

void game_init();

void user_isr( void ); 

void enable_interrupt(void);

void update_pinky_target();
void update_blinky_target();
void update_inky_target();

extern const struct Coord const pacmanOpen[4][8];
extern const struct Coord const pacmanClosed[12];
extern uint8_t mapPoints[23][128];
extern const struct Coord const ghostPixels[14];

extern const struct Coord const map[604];
extern const struct Coord const foods[376];
extern const struct Coord const superFoods[60];

void check_button_pressed();

void update_score();

#endif