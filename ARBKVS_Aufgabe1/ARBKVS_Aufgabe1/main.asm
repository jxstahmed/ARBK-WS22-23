;
; ARBKVS_Aufgabe1.asm
;
; Created: 09.10.2022 14:54:11
; Author : Ahmed
;

.include "m328pdef.inc"

.org 0x000							; Reset Vector [Interrupt?]
rjmp		start						; Sprung zum Start

start:
	ldi		r16, LOW(RAMEND)			; Wir setzen den Stack-Pointer, da man sonst den Stack nicht nutzen kann. Somit kann man dann Befehle nutzen (rjmp und rcall).
	out		SPL, r16
	ldi		r16, HIGH(RAMEND)
	out		SPH, r16

	ldi		r17, 0b11111111
	out		DDRD, r17				; Die Data direction register D als Ausgang einstellen.
	ldi		r18, 0b00000011
	out		DDRB, r18				; Zusätzlich noch die  Data direction register B0 & B1 als Ausgang, weil D nicht gereicht hat.

	ldi		r17, 0b00000001				; Wir fangen mit der LED D0 ganz links an.

lauf_links:							; Die LED läuft hier nach Links.
	out		PORTD, r17				; Starten mit D0.
	rcall	delay						; Aufruf der Delay Funktion, um das Lauflicht zu  verlangsamen.
	lsl		r17					; Nach Links shiften, damit die nächte LED leuchtet.
	cpi		r17, 0b00000000				; Wir überprüfen ob wir bei den PORTB LEDs angekommen sind.
	brne	lauf_links					; Wenn D7 nicht erreicht ist, schieben wir weiter.

	out		PORTD, r17				; Sobald D7 erreicht wird, schalten wir die Ports-D aus.
	ldi		r18, 0b000000001
	out		PORTB, r18				; Wir schalten nun um auf den B-Port, also D8 leutet
	rcall	delay						; Aufruf der Delay Funktion, um das Lauflicht zu  verlangsamen.
	lsl		r18

weiter_portb:							; LED läuft Richtung ende
	out		PORTB, r18					
	rcall	delay
	lsr		r18					; Ende ist erreicht, somit machen wir einen Richtungswechsel.
	cpi		r18, 0b00000000				; Überprüft ob wir wieder nach Rechts laufen.
	brne	weiter_portb					; Wenn nicht, laufen wir weiter nach links.

	out		PORTB, r18				; D-Ports erreicht, somit alle B-Ports auf 0 setzen.
	ldi		r17, 0b10000000				; Nun sind wir wieder bei den D-Ports. LED ganz links einschalten.

lauf_rechts:							; LED läuft nach Rechts zum Anfang.
	out		PORTD, r17
	rcall	delay
	lsr		r17
	cpi		r17, 0b00000001				; Vergleichen mit der LED ganz rechts.
	brne	lauf_rechts					; Wenn D0 nicht leuchtet, schieben wir weiter nach rechts.
	jmp		lauf_links				; Sollte D0 an sein, so müssen wir wieder nach rechts laufen.

delay:								; Hier startet eine kleiner Delay Loop von ca. 200ms mit 3.200.000 Cycles
    ldi  r19, 17
    ldi  r20, 60
    ldi  r21, 204

L1: dec  r21							; Es werden Werte geladen und dekrementiert um 1.
    brne L1                    
    dec  r20                   
    brne L1                     
    dec  r19                    
    brne L1                     
    ret
