/*
 * ARBKVS_Aufgabe3.c
 *
 * Created: 15.11.2022 14:55:24
 * Author : Ahmed
 */ 

#include <avr/io.h>

#define F_CPU 16000000UL
#include <avr/interrupt.h>

#define LED PIND0

volatile uint32_t systemClk = 0;				// Volatile -> Der Compiler darf keine Optimierung/Veränderung an dieser Variable vornehmen. (Code mit Variable)

void einrichten_Timer0()
{
	TCCR0A = (1 << WGM01);						// Wir aktivieren den CTC Modus (Clear Timer on Compare Match | Setzt Zähler auf 0 zurück) des Timers/des Counter 0 Control Register A.
	TCCR0B |= (1 << CS01) | (1 << CS00);		// Wir setzen den Prescaler auf den Wert 64. Dieser teilt den Systemtakt durch einen festen Wert, weil 16MHz zu schnell für viele Programme.
	OCR0A = 249;								// Wir legen den Wert fest, an dem der Output Comparison Register A für den Timer0 ein Interrupt generieren soll, wenn der Timer Counter und OCR0A gleich sind.
	// CPU Frequenz -> 16000000Hz | 1000Hz (= 1ms Periodendauer) | Prescaler -> 64
	// OCR = F_CLK / (F_TimerInterrupt x Prescaler) - 1
	// OCR = 16000000 / (1000 x 64) - 1 = 249 -> Muss in OCR0A geschrieben werden
	
	TIMSK0 = (1 << OCIE0A);						// Aktivieren den "Timer 1 Output Compare A Match Interrupt". Also den Interrupt bei dem Timer.
}

ISR(TIMER0_COMPA_vect)
{
	systemClk++;								// Wir lassen den Timer/Counter einfach hochzählen.
}

void waitFor(uint32_t ms)
{
	uint32_t currentTime = systemClk + ms;		// Wir berrechnet den Zeitpunkt, auf den wir warten möchten.
	
	if (currentTime < systemClk)				// Abfrage ob ein Overflow passiert ist.
	{
		systemClk = 0;
		while (systemClk < ms)
		{}
	}
		
	while (systemClk < currentTime)				// Wir warten für ms Sekunden. Bis dahin einfach nichts machen.
	{}



	/*if ((systemClk + ms) > OCR0A)
	{
		systemClk = 0;
		while (systemClk < ms)
		{}
	}
	else
	{
		while (systemClk < currentTime)
		{}
	}*/
	
}

void waitUntil(uint32_t ms)
{
	while (systemClk <= ms)						// Warten bis der Timer bei ms Sekunden angekommen ist. Bis dahin einfach nichts machen.
	{

	}
}

int main(void)
{
	/* Replace with your application code */
	
	DDRD = 0xff;								// Wir setzen das Data direction register D als Ausgang.
	PORTD = 0x00;
	einrichten_Timer0();
	sei();										// Wir aktiveren den global Interrupt.
	
	waitUntil(3000);							// Wir warten 3 Sekunden, bevor dir die LED blinken lassen.
	PORTD |= (1 << LED);						// Wir setzen das Bit für die LED.
	while (1)
	{
		waitFor(200);							// Wir warten für ca. 1ms, bevor wir weiter machen.
		PORTD ^= (1 << LED);					// Wir schalten die LED um.
	}
}

/*
a)
Siehe Kommentar oben, Zeile 15.

b)
Der Zähler läuft über bei systemClk = 2^32-1. Weil dieser 32 bit ist.
Also nach ca. 50 Tagen würde man den Overflow erreichen.

c)
Einfach eine Abfrage einfügen, siehe oben Zeile 38.

d)
Eventuell den OCR0A und/oder den Prescaler?
*/