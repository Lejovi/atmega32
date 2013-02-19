//lcd.h LCD driver routines
//

/*
The LCD Functions are intended for easy interfacing between C programs and
alphanumeric LCD modules built with the Hitachi HD44780 chip or equivalent.
The following LCD formats are supported in lcd.h:
1x8, 2x12, 3x12, 1x16, 2x16, 2x20, 4x20, 2x24 and 2x40 characters.
The LCD module must be connected to the port bits as follows:

	MCU PortX 0	-	RS (LCD pin4)
	MCU PortX 1	-	RD (LCD pin 5)
	MCU PortX 2	-	EN (LCD pin 6)
	MCU PortX 4	-	DB4 (LCD pin 11)
	MCU PortX 5	-	DB5 (LCD pin 12)
	MCU PortX 6	-	DB6 (LCD pin 13)
	MCU PortX 7	-	DB7 (LCD pin 14)
*/

#include <stdint.h>

#ifndef _LCD_H_
#define _LCD_H_


/////////////////////////////////////////////////////////////////////////////
//LCD

#define LCD_CLEAR					0x01	// Clear display
#define LCD_HOME					0x02	// Display and cursor home

#define LCD_ENTRY_CURSOR_INC		0x06	// Cursor move direction increment
#define LCD_ENTRY_CURSOR_DEC		0x04	// Cursor move direction decrement
#define LCD_ENTRY_DISP_SHIFT_ON		0x05	// Display shift on
#define LCD_ENTRY_DISP_SHIFT_OFF	0x04	// Display shift off

#define LCD_DISP_DISP_ON			0x0C	// Display on
#define LCD_DISP_DISP_OFF			0x08	// Display off
#define LCD_DISP_CURSOR_ON			0x0A	// Cursor on
#define LCD_DISP_CURSOR_OFF			0x08	// Cursor off
#define LCD_DISP_BLINK_ON			0x09	// Blinking on
#define LCD_DISP_BLINK_OFF			0x08	// Blinking off

#define LCD_SHIFT_DISP_LEFT			0x18	// Shift display left
#define LCD_SHIFT_DISP_RIGHT		0x1C	// Shift display right
#define LCD_SHIFT_CURSOR_LEFT		0x10	// Shift cursor left
#define LCD_SHIFT_CURSOR_RIGHT		0x14	// Shift cursor right

#define LCD_MODE_BIT_8				0x30	// 8-bit interface data
#define LCD_MODE_BIT_4				0x20	// 4-bit interface data
#define LCD_MODE_LINE_2				0x28	// 2-line display
#define LCD_MODE_LINE_1				0x20	// 1-line display
#define LCD_MODE_FONT_5X10			0x21	// 5 x 10 dot character font
#define LCD_MODE_FONT_5X8			0x20	// 5 x 8 dot character font

#define LCD_SET_ADDR_CGRAM			0x40	// Set CGRAM address
#define LCD_SET_ADDR_DDRAM			0x80	// Set DDRAM address

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _LCD_COUSTOM_CHAR
{
	unsigned char cgram[8];
} LCC;

/* Write a byte \c data to the LCD character generator or display RAM \c addr 
specified by \c section */
void lcd_write_byte(unsigned char addr, unsigned char data, unsigned char section);

/* Read a byte from the LCD character generator or display RAM\c addr 
specified by \c section */
unsigned char lcd_read_byte(unsigned char addr, unsigned char section);

/* Set the current display position at column \c x and row \c y.
The row and column numbering starts from 0. */
void lcd_gotoxy(unsigned char x, unsigned char y);

/* Clear the LCD and set the printing character position at row 0 and column 0. */
void lcd_clear(void);

/* Set cursor and display to the home position. */
void lcd_home(void);

/* Sent the LCD instruction \c command */
void lcd_command(unsigned char command);

/* Set the custom character \c cchr to the CGRAM \c index */
void lcd_set_custom_char(char index, LCC *cchr);

/* Display the character \c c at the current display position. */
void lcd_putchar(char c);

/* Display at the current display position the string \c str, located in RAM. */
void lcd_puts(const char *str);

/* Display at the current display position the string \c prog_str, located in PROGRAM space. */
void lcd_puts_P(const char *prog_str);

/* Initialize the LCD module, clears the display and sets the printing */
void lcd_init(void);

void lcd_pint_u16(uint16_t i, uint8_t n);

#endif
