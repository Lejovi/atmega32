/*
 * hd44780.c
 *
 * Created: 16-7-2011 22:04:37
 *  Author: ljv
 */ 
//delen van Georg Wuensch gebruikt

#include "hd44780.h"
#include "conf_clock.h"
#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

uint8_t gPositie;

//zend een transportpuls
static inline uint8_t 
hd44780_pulse_e(bool readback) __attribute__((always_inline));
static inline uint8_t
hd44780_pulse_e(bool readback)
{
  HD44780_PORTOUT |=_BV(HD44780_E);
	uint8_t x;
	#if F_CPU > 4000000UL
  		_delay_us(1);
	#else
  		if (readback)
    		__asm__ volatile("nop");
			#if F_CPU > 1000000UL
 				 __asm__ volatile("nop");
				#if F_CPU > 2000000UL
  					__asm__ volatile("nop");
					__asm__ volatile("nop");
				#endif /* F_CPU > 2000000UL */
			#endif /* F_CPU > 1000000UL */
	#endif
	if (readback) x = HD44780_PORTIN & HD44780_DATABITS;
  	else x = 0;
	
	HD44780_PORTOUT &= ~(_BV(HD44780_E));
  	return x;
}

// Zend de lage nibble naar de LCD controller.
void hd44780_outnibble(uint8_t n, uint8_t rs)
{
	//zet RW op 0
	HD44780_PORTOUT &= ~(_BV(HD44780_RW));
	//als rs 1 is moet RS 1 zijn
  	if (rs) HD44780_PORTOUT |= _BV(HD44780_RS);
	//anders 0
	else HD44780_PORTOUT&= ~(_BV(HD44780_RS));
	//zet data bovenin 
	n = (n << HD44780_D4);
	n = (HD44780_PORTOUT & ~HD44780_DATABITS) | 
				(n & HD44780_DATABITS);
	//voer dit uit
	HD44780_PORTOUT  = n;
	//transporteer met e-puls
	(void)hd44780_pulse_e(false);
}

// Stuur een byte naar het lcd-display
void hd44780_outbyte(uint8_t b, uint8_t rs)
{
	uint8_t Gx = (b >> 4);
  	hd44780_outnibble(Gx , rs);
  	Gx = (b & 0xf);
  	hd44780_outnibble(Gx , rs);
	if (rs == 1)  gPositie +=1;
}

// lees een nibble uit het lcd_display
static uint8_t hd44780_innibble(uint8_t rs)
{
 	uint8_t x;
	HD44780_PORTOUT |= _BV(HD44780_RW);
	HD44780_DDR &= ~HD44780_DATABITS;
 	if (rs) HD44780_PORTOUT |= _BV(HD44780_RS);
	else HD44780_PORTOUT &= ~(_BV(HD44780_RS));
	x = hd44780_pulse_e(true);
	HD44780_DDR |= HD44780_DATABITS;
	HD44780_PORTOUT &= ~(_BV(HD44780_RW));
	return (x & HD44780_DATABITS) >> HD44780_D4;
}

// lees twee nibbles uit het display
uint8_t hd44780_inbyte(uint8_t rs)
{
	uint8_t x;
  	x = hd44780_innibble(rs) << 4;
  	x |= hd44780_innibble(rs);

  	return x;
}


// wacht op verdwijnen busyvlag
void hd44780_wait_ready(void)
{
  	//_delay_ms(5); //voor simulatie
	while (hd44780_incmd() & HD44780_BUSYFLAG);
}

// init lcd-diplay
void hd44780_init(void)
{
	//Initieer de te gebruiken poort
	HD44780_DDR = 0xF7;
	HD44780_PORTIN = 0x00;
	HD44780_PORTOUT = 0x00;
	//Suur de initiering naar de HD44780
	_delay_ms(20);
	hd44780_outnibble(0x03,0);
	_delay_ms(10);
	hd44780_outnibble(0x03,0);
	_delay_ms(10);
	hd44780_outnibble(0x03,0);
	_delay_ms(10);
	hd44780_outnibble(0x02,0);
	hd44780_wait_ready();
	hd44780_outbyte(0x28,0);  //function set
	hd44780_wait_ready();
	hd44780_outbyte(0x0C,0);	//display aan
	hd44780_wait_ready();
	hd44780_outbyte(0x01,0);	//display schoon
	hd44780_wait_ready();
	hd44780_outbyte(0x06,0);	//entry mode
}	
                                                                               

