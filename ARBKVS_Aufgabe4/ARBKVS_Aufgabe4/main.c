/*
 * ARBKVS_Aufgabe4.c
 *
 * Created: 26.11.2022 13:16:01
 * Author : Ahmed
 */ 

#include "keys.h"
#include "sevenseg.h"

/*
Logische 0: an
Logische 1: aus

	gfe dcba
0:  100 0000	= 64
1:  111 1001	= 121
2:  010 0100	= 36
3:	011 0000	= 48
4:  001 1001	= 25
5:  001 0010	= 18
6:  000 0010	= 2
7:  111 1000	= 120
8:  000 0000	= 0
9:  001 0000	= 16
*/

int zahlen[10] = { 64, 121, 36, 48, 25, 18, 2, 120, 0, 16 };		// Integer Zahlen welche die Binär Zahlen darstellen von 0 bis 9. [Bsp.: Um eine 0 Anzeigen zu lassen, brauchen wir alles außer die Anzeige g. Deshalb ist diese aus.)
volatile uint32_t zaehler = 0;

ISR(PCINT0_vect)
{
	if (bit_is_clear(PINB, PINB1))									// Abfrage ob der SW1 gedrückt ist.
	{								
		if (zaehler == 0)
		{
			zaehler = 100;											// Wenn wir aktuell bei 0 sind und runterzählen wollen, so setzen wir count = 100 und zählen dann ganz normal runter um 99 anzeigen zu lassen.
		}
		zaehler--;
	}		
	if (bit_is_clear(PINB, PINB2))									// Abfrage ob der SW1 gedrückt ist.
	{								
		if (zaehler == 99)
		{
			zaehler = -1;											// Wenn wir aktuell bei 99 sind und hochzählen wollen, so setzen wir count = -1 und zählen dann ganz normal hoch um 0 anzeigen zu lassen.
		}
		zaehler++;
	}
}


int main(void)
{
   start();
   while(1)
   {
	   int rechts = zaehler % 10;									// Berechnen die Zahl die Rechts angezeigt werden soll. [Bsp.: 21 / 10 = 1]
	   int links = (zaehler - rechts) / 10;							// Berechnen die Zahl die Links angezeigt werden soll. [Bsp.: (21 - 1) / 10 = 2] -> Links 2, Rechts 1 = 21
	   
	   anzeigen(rechts, zahlen);
	   anzeigen(links, zahlen);
   }
}

