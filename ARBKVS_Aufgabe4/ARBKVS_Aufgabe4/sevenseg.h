/*
 * sevenseg.h
 *
 * Created: 26.11.2022 13:17:12
 *  Author: Ahmed
 */ 


#ifndef SEVENSEG_H_
#define SEVENSEG_H_


#define F_CPU 16000000
#include <util/delay.h>
#include "avr/io.h"

void anzeigen(int zahl, int zahlen[]);

#endif /* SEVENSEG_H_ */