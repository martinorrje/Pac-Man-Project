#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

//This function is taken from the Basic I/O Shield Board Reference Manual
void display_host_init();

//These functions are taken from lab 3. The first one initializes the display controller, and the second one delays the program for a specified time
void display_host_init(void);
void quicksleep(int cyc);
uint8_t spi_send_recv(uint8_t data);
uint8_t spi_send_recv_all_cols(uint8_t data);
void display_page(int dataLength, uint8_t x, uint8_t y, const uint8_t* data);
void display_two_pages(int dataLength, int x, int y, const uint8_t **data);
void display_image(int x, const uint8_t* data);
void init_buttons();
int getbtns(void);

//Debug help functions, mostly taken from lab 3
extern char textbuffer[4][16];
extern const uint8_t const font[128*8];
void display_string(int line, char *s, int stringLength, uint8_t display_buffer[4][128]);
void display_string_update(void);
void display_debug( volatile int * const addr );
static void num32asc( char * s, int n );
char * itoaconv( int num );

void setup_pins();

#endif