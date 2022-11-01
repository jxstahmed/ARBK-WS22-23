/*
 * ARBKVS_Aufgabe2.cpp
 *
 * Created: 28.10.2022 11:28:09
 * Author : Ahmed
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdbool.h>									// Um Boolean nutzen zu können.

#define SW1 PINB0
#define SW2 PINB1
#define LED0 PIND0
#define LED9 PIND1

int an = LED0;
int aus = LED9;
bool blinkt = true;

void ports_einrichten()
{
	DDRD = 0xff;										// Wir setzen das DDRD als Ausgang.
	PORTD = 0x00;
	
	DDRB = 0x00;										// Wir setzen das DDRB als Eingang.
	PORTB = 0xff;
}

void taster()
{
	if(!(PINB & (1 << SW1)))						// (PINB & (1 << SW1) -> Check ob High oder Low, das ! sagt somit bei Low
	{
		if(PIND & (1 << LED0))						// Wenn die LED0 an ist
		{
			blinkt ^= 1;							// Wir ändern den Status der LED [Blinken -> Leuchten oder Leuchten -> Blinken]
		}
		else if(PIND & (1 << LED9))					// Wenn die LED9 an ist, schalten wir um auf die LED0.
		{
			aus = LED9;
			an = LED0;
		}
	}
	
	if(!(PINB & (1 << SW2)))
	{
		if(PIND & (1 << LED9))						// Wenn die LED9 an ist
		{
			blinkt ^= (1 << 0);						// Wir ändern den Status der LED [Blinken -> Leuchten oder Leuchten -> Blinken]
		}
		else if((PIND & (1 << LED0)))				// Wenn die LED0 an ist, schalten wir um auf die LED9.
		{
			aus = LED0;
			an = LED9;
		}
	}
}

int main(void)
{
	ports_einrichten();
	while (1)
	{
		taster();
		if (blinkt)
		{
			PORTD &= ~(1UL << aus);						// Ich nutze UL statt int, da bei berechnungen sonst Fehler auftreten. [Manchmal leuchten beide LEDs beim wechseln]
			PORTD ^= (1 << an);
		}
		else
		{
			PORTD &= ~(1UL << aus);
			PORTD |= ( 1 << an);
		}
		_delay_ms(200);
	}
}

/*

^= -> XOR
&= -> AND
|= -> OR
~ -> NOT

*/