#ifndef GAME_H
#define GAME_H

#include<stdint.h>
#include"draw_to_display.h"
#include"update_display_buffer.h"
#include"structs.h"
#include"helper_functions.h"
#include"math.h"

int game_over;
int restart_game;
int view_highscore;
int from_highscore;
int prev_switch;
int score_board[4];
int nameIndex;
char currentName[5];
char score_board_names[4][5];
char currentChar;

int scatterTimer;
int chaseTimer;
int frightenedTimer;
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
void update_ghosts();

void update_ghost_mode();

void game_init();
void game_start();

void user_isr( void ); 

void enable_interrupt(void);

void update_pinky_target();
void update_blinky_target();
void update_inky_target();

extern const struct Coord const pacmanOpen[4][8];
extern const struct Coord const pacmanClosed[12];
extern uint8_t mapPoints[23][128];
extern const uint8_t const mapPoints_copy[23][128];
extern const struct Coord const ghostPixels[14];

extern const struct Coord const map[604];
extern const struct Coord const foods[376];
extern const struct Coord const superFoods[60];

void check_button_pressed();
void check_switches();

void update_score();
void select_highscore_name();
void view_highscore_menu();

#endif