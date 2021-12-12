#include <pic32mx.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include"helper_functions.h"
#include"game.h"

int main() {

	setup_pins();
	display_host_init();
	display_control_init();

	init_buttons();
	init_switches();

	game_init();

	score = 0;
	game_over = 0;
	restart_game = 0;
	int i;

	for(i = 0; i < 4; i++){
		score_board[i] = 0;
		score_board_names[i][0] = 'A';
		score_board_names[i][1] = 'A';
		score_board_names[i][2] = 'A';
		score_board_names[i][3] = 'A';
		score_board_names[i][4] = '\0';
	}

	currentName[0] = 'A';
	currentName[1] = 'A';
	currentName[2] = 'A';
	currentName[3] = 'A';
	currentName[4] = '\0';

	nameIndex = 0;
	currentChar = 'A';
	
	pacman_anim_state = 0;

	pacmanX = 62;
	pacmanY = 1;
	pacmanDirection = Down;

	//Initialize ghost positions
	Inky.pos.x = 4;
	Inky.pos.y = 18;
	Inky.scatterTarget.x = 4;
	Inky.scatterTarget.y = 18;

	Blinky.pos.x = 120;
	Blinky.pos.y = 18;
	Blinky.scatterTarget.x = 120;
	Blinky.scatterTarget.y = 18;

	Pinky.pos.x = 120;
	Pinky.pos.y = 2;
	Pinky.scatterTarget.x = 120;
	Pinky.scatterTarget.y = 2;

	scatterTimer = 7;
	chaseTimer = 20;
	scatterCount = 4;
	chaseMode = 0;
	frightenedMode = 0;
	timer = 0;			//Incremented every second to keep track of the different modes	

	clear_display_buffer(display_buffer);
	display_map(map, 604, display_buffer);
	display_update(display_buffer);

	while(1){
		check_button_pressed();
		check_switches();
	}

	return 0;
}