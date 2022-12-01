/*
 * keys.h
 *
 * Created: 26.11.2022 13:17:56
 *  Author: Ahmed
 */ 


#ifndef KEYS_H_
#define KEYS_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define bit_is_clear(sfr, bit) (!(_SFR_BYTE(sfr) & _BV(bit)))		// Wir schauen nach, ob das Bit "bit" im IO Register "sfr" clear ist. Return 0 wenn Bit gesetzt ist und non-zero wenn nicht gesetzt ist.
																	// https://manpages.debian.org/testing/avr-libc/bit_is_clear.3avr.en.html [Hier überprüfung ob ein Switch gedrückt wird oder nicht.]
void start();

#endif /* KEYS_H_ */