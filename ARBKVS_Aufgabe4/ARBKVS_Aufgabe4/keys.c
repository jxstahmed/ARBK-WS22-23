/*
 * keys.c
 *
 * Created: 26.11.2022 13:16:40
 *  Author: Ahmed
 */ 

#include "keys.h"

void start()
{
	DDRD = 0xff;										// Wir setzen die Ports D0 bis D6 als Input f�r die Segmente a bis g.
	PORTD = (1 << PIND0);								// Setzen das Bit f�r den 7-Segment
	
	DDRB = 0x01;										// Wir setzen den Port B0 als Ausgang f�r das Umschalten der Zehner stellen. Port B1 und B2 als Eingang f�r die Switches.
	PORTB |= (1 << PINB1) | (1 << PINB2);				// Setzen die Bits f�r die beiden Switches SW1 und SW2.
	
	cli();												// Wir deaktivieren erst die Interrupts.
	PCICR |= 0x01;										// Wir legen im Pin Change Interrupt Control Register fest das der PortB aktivert werden soll. Hei�t der PortB l�sst die Interrupts zu.
	PCMSK0 |= (1 << PINB1) | (1 << PINB2);				// Legen fest, dass ein Interrupt stattfinden soll, wenn PB1 und PB2 Zustand sich �ndern.
	sei();												// Aktivieren die Interrupts nach dem einrichten wieder.
}