/*
 * LEDCube.c
 *
 * Created: 2017. 12. 17. 0:03:49
 * Author : zoltan
 */ 

#define F_CPU 1000000UL
#define DELAY 200

#define LED_LOW_DDR DDRA
#define LED_HIGH_DDR DDRC
#define LED_LOW PORTA
#define LED_HIGH PORTC
#define LAYERS PORTD
#define LAYERS_DDR DDRD

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static uint16_t cube[4] = {0x0001, 0x0001, 0x0001, 0x0001};
static uint8_t matrix[4][4][4];

//Beírja a LED-et a cube tömbbe, de nem kapcsolja be
void addLED(uint8_t n) {
	if ( (n % 16) > 7 )
		cube[n/16] |= ( ((n%16)-8) << 2 );
	else
		cube[n/16] |= (n%16);
}

//Törli a LED-et a cube tömbb?l, de nem kapcsolja ki
void removeLED(uint8_t n) {
	if ( (n % 16) > 7 )
		cube[n/16] &= ~( ((n%16)-8) << 2 );
	else
		cube[n/16] &= ~(n%16);
}

//N. LED bekapcsolása
void setLED(uint8_t n) {
	LAYERS = (1 << (n / 16));
	if ( (n % 16) > 7 ) {
		LED_HIGH |=  (1 << ( (n%16) - 8) );
	} else {
		LED_LOW |= (1 << (n%16));
	}
}
//N. LED kikapcsolása
void resetLED(uint8_t n) {
	LAYERS = (1 << (n / 16));
	if ( (n % 16) > 7 ) {
		LED_HIGH &= ~(1 << ( (n%16) - 8) );
	} else {
		LED_LOW &= ~(1 << (n%16));
	}
}
//LED-ek beállítása cube tömb alapján
void showPattern() {
	uint8_t i;
	for (i = 0; i < 4; i++) {
		LAYERS = (1 << i);
		LED_LOW = cube[i] & 0x00FF;
		LED_HIGH = (cube[i] & 0xFF00) >> 8;
		//_delay_ms(4);
	}
}

//

int main(void)
{
	//A, C, D portok --> kimenet
	LED_LOW_DDR = 0xFF;	//LED-ek 0..7
	LED_HIGH_DDR = 0xFF;	//LED-ek 8..15
	LAYERS_DDR = 0x0F;	//Rétegek 0..4
	
	//JTAG kikapcsolva
	MCUCSR |= (1<<JTD);
	
	uint8_t r1, r2;
	time_t t;
	srand((unsigned) time(&t));
    while (1)
    {
		r1 = rand()%63;
		setLED(r1);
		_delay_ms(300);
		
		r2 = rand()%63;
		setLED(r2);
		_delay_ms(300);
		
		resetLED(r1);
		_delay_ms(300);
		
		resetLED(r2);
		_delay_ms(300);
		
	}
}

