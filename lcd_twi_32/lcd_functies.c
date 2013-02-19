//lcd_functies.c
//Ir L.J. Visser
//1 juni 2011
//////////////////////////////////////////////////////////////////////////////

#include  "hd44780.h"
#include <util\delay.h>
#include <string.h>
#include <stdlib.h>

uint8_t gPositie; 	//globale var die onthoudt waar de
					//cursor zich bevindt

//ga naar positie 0,0
void lcd_home()
{
	hd44780_outcmd(HD44780_HOME);
}

//init de controller
void lcd_init()
{
	hd44780_init();
	_delay_ms(10);
}

//druk een karakter af
void lcd_putchar(char c)
{
	_delay_ms(10); //hd44780_wait_ready();
	hd44780_outdata(c);
}

//ga naat positie x,y
void lcd_gotoxy(uint8_t x, uint8_t y)
{
	uint8_t p = 0;
	if ((x < 20) && (y < 4))
	{
		if (y == 0) p = x;
		if (y == 1) p = x + 0x40;
		if (y == 2) p = x + 0x14;
		if (y == 3) p = x + 0x54;
		hd44780_wait_ready();
		hd44780_outcmd(HD44780_DDADDR(p));
		gPositie -= 1;
	}
}

//druk een string af
void lcd_puts(const char *s)
{
	for (uint8_t i = 0; i < strlen(s); i++)
	{
		lcd_putchar(s[i]);
	}
}

//maak het ndisplay schoon
void lcd_clear(void)
{	
	hd44780_outcmd(HD44780_CLR);
}

//druk een integer af rechts uitgelijnd in 5 posities
void lcd_pint_u16(uint16_t i, uint8_t n) 
{
	//lokale variabelen
	char s[10] = "     ";
	char sh[10];	
	uint8_t L = 0, V = 5, J, K = 0;
	//zet getal om in ascii;
	itoa(i, sh, n);
	//lijn uit naar rechts
	L = strlen(sh);
	V -= L;
	for (J = V; J <= 5; J++)
	{
		s[J] = sh[K++];
	}
	//druk getal af
	lcd_puts(s);
}
