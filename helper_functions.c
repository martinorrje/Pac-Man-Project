#include "helper_functions.h"  /* Declatations for these labs */

void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

void display_control_init(void) {
  	DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}

void setup_pins(){
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
}

void display_host_init()
{
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
	SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;
}

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));    //The third bit of the status register of SPI corresponds to the SPI transmit buffer status empty bit. This line waits until the transmit buffer is empty 
	SPI2BUF = data;               //Send data from master to slave         
	while(!(SPI2STAT & 1));       //The third bit of status register of SPI is SPI receive buffer full status bit. This line waits until the buffer is full, after which it returns
	return SPI2BUF;				  //Return the byte received from slave
}

/*
From the Basic I/O shield reference manual:

The display memory is organized as four pages of 128 bytes each. Each memory page corresponds to an eight
pixel high stripe across the display. Each byte in the memory page corresponds to an eight pixel high
column on the display. The least significant bit in a display byte is the top most pixel, and the most
significant bit the bottom most pixel. The first byte in the page corresponds to the left most pixels on
the display and the last byte the right most pixels. 
*/

//Displays image on one row only
void display_page(int dataLength, uint8_t x, uint8_t y, const uint8_t *data) {
	int i, j;
	
	DISPLAY_CHANGE_TO_COMMAND_MODE;

	spi_send_recv(0x22);		//Set page command
	spi_send_recv(y);			//Set the page number
	
	spi_send_recv(0x0);		//Set lower nibble of page
	spi_send_recv(0x10);		//Set upper nibble of page

	spi_send_recv(0x21);		//Set column range command
	spi_send_recv(x);
	spi_send_recv((uint8_t)(x+6));
	
	DISPLAY_CHANGE_TO_DATA_MODE;
	
	for(j = 0; j < dataLength; j++)
		spi_send_recv(data[j]);
}



void display_image(int x, const uint8_t* data) {
	int i, j;
	
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);	
		spi_send_recv(i);				//The row/page to display on
		
		spi_send_recv(x & 0xF);		
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 32; j++)
			spi_send_recv(~data[i*32 + j]);
	}
}

void init_buttons(){
	TRISDSET = (0b111 << 5);     //Set bits 5-7 to 1(1 = input), these are btn2, btn3 and btn4
	TRISFSET = 0b10;				//Set bit 1 of port F to input, this is btn1
}

void init_switches(){
	TRISDSET = (0b1111) << 8;		//Set bits 8-11 to 1, these are switches 1-4
}

int getbtns(void){
    int buttons = ((0b111 << 5) & PORTD) >> 5;     //First mask bits 5-7 of PORTD and then shift the resulting integer 5 steps to the right, then mask the least significant 3 bits
	buttons |= (PORTF & 0b10) << 2;	
	return buttons;
 }

int getsw( void ){
	return (0xF00 & PORTD) >> 8;     //First mask bits 8-11 of PORTD and then shift the resulting integer 8 steps to the right, then mask the least significant 4 bits
}