/*
 * hd44780.h
 *
 * Created: 16-7-2011 22:09:45
 * Aangepast aan eigen behoefte 12 augustus 2012. LJV.
 *  Author: ljv
 */ 

#include "defines.h"
#include <stdint.h>

#ifndef _HD44780_H_
#define _HD44780_H_

//De gebruikte chippoort
#define HD44780_PORT GATE
//----------------------------------------------------------------------------
//Gedeelte met Hardware definities
//----------------------------------------------------------------------------
//Aan welke pootjes zit de besturing .
#define HD44780_RS 		PORT0
#define HD44780_RW 		PORT1 
#define HD44780_E 		PORT2

//Aan welke pootjes zitten de databits.
#define HD44780_D4 		PORT4 
#define HD44780_D5 		PORT5
#define HD44780_D6 		PORT6 
#define HD44780_D7 		PORT7
//-----------------------------------------------------------------------------
//Gedeelte met algemene macros
#define GLUE(a, b) 		a##b
#define PORT(x)			GLUE(PORT, x)
#define PIN(x)			GLUE(PIN, x)
#define DDR(x) 			GLUE(DDR, x)
#define HD44780_PORTOUT	PORT(HD44780_PORT)
#define HD44780_PORTIN	PIN(HD44780_PORT)
#define HD44780_DDR		DDR(HD44780_PORT)
#define HD44780_DATABITS \
						(_BV(HD44780_D4)|_BV(HD44780_D5)| \
						_BV(HD44780_D6)|_BV(HD44780_D7))
#define HD44780_BUSYFLAG 0x80

#define HD44780_FNSET(if8bit, twoline, font5x10) \
					(0x20 | \
					((if8bit)? 0x10: 0) | \
					((twoline)? 0x08: 0) | \
					((font5x10)? 0x04: 0))
#define HD44780_DDADDR(addr) (0x80 | ((addr) & 0x7f))

//-----------------------------------------------------------------------------
//de HD44780 functies
//-----------------------------------------------------------------------------
// Send a command to the LCD controller. 
#define hd44780_outcmd(n)	hd44780_outbyte((n), 0)

// Send a data byte to the LCD controller. 
#define hd44780_outdata(n)	hd44780_outbyte((n), 1)

// Read the address counter and busy flag from the LCD. 
#define hd44780_incmd()		hd44780_inbyte(0)

// Read the current data byte from the LCD.
#define hd44780_indata()	hd44780_inbyte(1)


// Clear LCD display command.
#define HD44780_CLR 		0x01

// Home cursor command. 
#define HD44780_HOME 		0x02

//Function set
#define HD44780_FNCSET 		0x28

// Selects disp[lay] on/off, cursor on/off, cursor blink[ing]
// on/off.
//#define HD44780_DISPCTL(disp, cursor, blink) \ 	(0x08 | ((disp)? 0x04: 0) | ((cursor)? 0x02: 0) | ((blink)? 1: 0))
#define HD44780_DISPCTL		0x0C

//  Select the entry mode.  inc determines whether the address counter
//  auto-increments, shift selects an automatic display shift.
//#define HD44780_ENTMODE(inc, shift) (0x04 | ((inc)? 0x02: 0) | ((shift)? 1: 0))
#define HD44780_ENTMODE 	0x06
;
//  Initialize the LCD controller hardware.
void hd44780_init(void);

//  Send byte b to the LCD.  rs is the RS signal (register select),
//  0 selects instruction register, 1 selects the data register.
void hd44780_outbyte(uint8_t b, uint8_t rs);

//  Wait for the busy flag to clear.
void hd44780_wait_ready(void);

// Zend nibble naar lcd
void hd44780_outnibble(uint8_t n, uint8_t rs);


//lcd functies
//-----------------------------------------------------------------------------
void lcd_init(void);
void lcd_putchar(char c);
void lcd_puts(const char *str);
void lcd_clear(void);
void lcd_init(void);
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcd_pint_u16(uint16_t i, uint8_t n); 
void lcd_pint_u8(uint8_t i, uint8_t n); 

#endif /* HD44780_H_ */
