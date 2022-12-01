/*
 * sevenseg.c
 *
 * Created: 26.11.2022 13:16:58
 *  Author: Ahmed
 */ 

#include "sevenseg.h"

void anzeigen(int zahl, int zahlen[])
{

	PORTD = zahlen[zahl];
	_delay_ms(10);
	PORTB ^= (1 << PINB0);

}
