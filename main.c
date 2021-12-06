#include <pic32mx.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include"helper_functions.h"
#include"game.h"

int main() {

	setup_pins();
	display_host_init();
	display_control_init();

	init_buttons();

	game_init();

	pacman_anim_state = 0;

	pacmanX = 10;
	pacmanY = 2;
	pacmanDirection = Down;

	//Initialize ghost positions
	Inky.pos.x = 20;
	Inky.pos.y = 2;

	Blinky.pos.x = 80;
	Blinky.pos.y = 2;

	Pinky.pos.x = 40;
	Pinky.pos.y = 15;

	Clyde.pos.x = 75;
	Clyde.pos.y = 15;

	clear_buffer();
	display_map(map, map_size, display_buffer);
	display_update(display_buffer);

	while(1){
		check_button_pressed();
	}

	return 0;
}