/*
 * ARBKVS_Aufgabe2.cpp
 *
 * Created: 28.10.2022 11:28:31
 * Author : Ahmed
 */ 

#include <avr/io.h>

#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>										// Um Boolean zunutzen [überprüfung ob LED blinkt]


#define SW1 PIND2											// Auf den Ports PIND2 [INT0] und PIND3 [INT1] liegen die EICRA [Register für externe Interrupts].
#define SW2 PIND3
#define LED0 PINB0
#define LED9 PINB1

volatile int an = LED0;										// volatile -> Sagt dem Compiler das er diese Variable nicht optimieren oder ändern soll.
volatile bool blinkt = true;

void ports_einrichten()
{
	DDRB = 0xff;											// Wir setzten die Ports B0 und B1 als Ausgänge für die LEDs.
	PORTB = 0x00;
	
	DDRD = 0x00;											// Wir setzten das DDRD als Eingang für die Taster.
	PORTD |= (1 << SW1) | (1 << SW2);						// Wir setzen die beiden Taster als Ausgänge, um sie nutzen zu können.
	EICRA |= (1 << ISC11) | (1 << ISC01);					// Wir legen die Bedingung fest, dass bei einer fallenden Flanke ein Interrupt Request generiert wird. [Wird im Interrupt Sense Control gespeichert]
	EIMSK = (1 << INT0) | (1 << INT1);						// Wir setzen die beiden INT-Bits und geben die beiden externen Interrupts frei.
	sei();													// Wir aktivieren die Interrupts, durch das setzten der globalen Interrupt Maske. [standard funktion]
}

ISR(INT0_vect)										// Bei dieser Funktion handelt es sich um die Interrupt Routinen [Was genau getan werden soll, bei einem Request]
{
	if (an == LED0)									// Wenn die LED0 bereits an ist, so wird der Status der LED geändert. [Blinkt -> Leuchten, oder Leuchten -> Blinkt]
	{										
		blinkt = !blinkt;
	} 
	else											// Wenn die LED0 nicht an ist, so ist die LED9 an. Somit schalten wir die LED9 aus und die LED0 an.
	{
		PORTB = (1 << LED0);
	}
	an = LED0;
}

ISR(INT1_vect)
{
	if (an == LED9)									// Wenn die LED9 bereits an ist, so wird der Status der LED geändert. [Blinkt -> Leuchten, oder Leuchten -> Blinkt]
	{
		blinkt = !blinkt;
	} 
	else											// Wenn die LED9 nicht an ist, so ist die LED0 an. Somit schalten wir die LED0 aus und die LED9 an.
	{
		PORTB = (1 << LED9);
	}
	an = LED9;
}


int main(void)
{
	ports_einrichten();								// Wir richten alle PORTS ein, um starten zu können.
	while(1)										// Geschwindigkeit des Blinkens
	{
		if (blinkt)
		{
			PORTB ^= (1 << an);						
		} 
		else
		{
			PORTB = (1 << an);
		}
		_delay_ms(200);
	}
}