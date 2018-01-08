/*
 * LEDCube.c
 *
 * Created: 2017. 12. 17. 0:03:49
 * Author : zoltan
 */ 

#define DELAY 200

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void showFrame(uint16_t l[]) {
	uint8_t i;
	for (i = 0; i < 4; i++) {
		PORTD = (1 << i);
		PORTA = l[i] & 0x00FF;
		PORTC = (l[i] & 0xFF00) >> 8;
		_delay_ms(4);
	}
}

int main(void)
{
    /* Replace with your application code */
	//A, C portok --> kimenet
	DDRA = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	
	MCUCSR |=(1<<JTD);
	MCUCSR |=(1<<JTD);

	uint16_t layer[4] = {0x0001, 0x0001, 0x0001, 0x0001};
	cli();
	
	uint8_t t = 0;
    while (1)
    {
		for (t = 0; t < 63; t++) {		//63*~16 = 1000 msec
			showFrame(layer);
		}
		layer[0] = layer[0] << 1;
		layer[1] = layer[1] << 1;
		layer[2] = layer[2] << 1;
		layer[3] = layer[3] << 1;
	}
}

