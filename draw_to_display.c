#include"draw_to_display.h"

void display_update(uint8_t display_buffer[4][128]) {
	int i, j, k;
	uint8_t currentCol;
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);
            
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 128; j++) {
			currentCol = display_buffer[i][j];
            spi_send_recv(currentCol);
		}
	}
}