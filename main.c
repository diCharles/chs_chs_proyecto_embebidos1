#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<stdio.h>
#include<stdbool.h>
#include<inttypes.h>
#include "ili9341.h"
#include "ili9341gfx.h"
#define POINTCOLOUR PINK


extern uint16_t vsetx,vsety,vactualx,vactualy,isetx,isety,iactualx,iactualy;
static FILE mydata = FDEV_SETUP_STREAM(ili9341_putchar_printf, NULL, _FDEV_SETUP_WRITE);


int main(void)
{
	stdout = & mydata;
	ili9341_init();//initial driver setup to drive ili9341
	ili9341_clear(BLUE);//fill screen with pink colour
	
	display_init();//display initial data

	while(1)
	{
			
			ili9341_clear(BLACK);//fill screen with pink colour
			
			display_init();//display initial data

	}

}