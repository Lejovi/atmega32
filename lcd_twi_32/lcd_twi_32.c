/*
 * lcd_twi_32test.c
 *
 * Created: 15-10-2012 16:31:14
 *  Author: ljv
 
 lcd zit aan A
 twi en jtag zitten aan C
 led zit aan D7
 OC1A zit aan D5
 IC1 zit aan D6
 but zit aan B4
 */ 

#define PINx	PINB
#define PORTx	PORTD

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/io.h>

#include <avr/interrupt.h>

#include "defines.h"
#include "conf_clock.h"
#include "hd44780.h"
#include "lcd.h"
#include "twi.h"
#include "lcd_twi_32.h"

//=============================================================================
//globale variabelen
extern struct mt_boodschap MT_B;
extern struct resultaten Res;
uint8_t help;
//=============================================================================
//schrijf basiszinnen
void schrijftekst(void)
{
	char* strs = "Na start:";
	char* stra = "Na adres:";
	char* strd = "Na data :";
	char* strD = "Data    :";
	lcd_puts(strs);
	lcd_gotoxy(0,1);
	lcd_puts(stra);
	lcd_gotoxy(0,2);
	lcd_puts(strd);	
	lcd_gotoxy(0,3);
	lcd_puts(strD);
}

//vul het scherm met resultaten
void print_lcd()
{
	lcd_gotoxy(10,0);
	lcd_pint_u16(Res.na_start,16);
	lcd_gotoxy(10,1);
	lcd_pint_u16(Res.na_adres,16);
	lcd_gotoxy(10,2);
	lcd_pint_u16(Res.na_data,16);
	lcd_gotoxy(0,3);
	lcd_puts("Data was: ");
	lcd_pint_u16(MT_B.data[0],16);
	lcd_gotoxy(10,3);
	if (MT_B.fout != 0)
	{
		switch(MT_B.fout)
		{
			case 0x20:
				lcd_gotoxy(0,3);
				lcd_puts("Na adres: NOT ACK");
				break;
			case 0x30:
				lcd_gotoxy(0,3);
				lcd_puts("Na data: NOT ACK");	
				break;
			default: 		
				lcd_gotoxy(0,3);
				lcd_puts("Onbekende fout");				
		}
	}	
	MT_B.klaar = 0;
}	

void onbekende_fout(void)
{
	// meld de fout
	MT_B.fout = 0xFF;
	//stop verzenden
	TWCR = TWI_STOP;
	MT_B.teller = 0;
	MT_B.klaar = 1;
}

void poorten_init(void)
{
	//PORT B: schakelaars inlezen
	DDRB = 0x00;
	PORTB = 0x00;	
	//PORT D: LED's aansturen
	DDRD =0x80;
	PORTD = 0x80;
}
	
//=============================================================================
//Het hoofdprogramma
int main(void)
{
	//variabelen
	uint8_t blok;
	uint8_t arr[10];
	
	poorten_init();

	
	//init twi
	twi_init();
	
	//init lcd
	lcd_init();
	schrijftekst();
	
	sei();
	arr[0] = 0x00;
	arr[1] = 0x57;
	arr[0] = 0xFF;
	twi_mt_zendboodschap(0x38, 0x03,arr);
		//print resultaten interrupts
		if (MT_B.klaar == 1)
		{
			print_lcd();
		}
	twi_mt_zendboodschap(0x39, 0x03,arr);
		//print resultaten interrupts
		if (MT_B.klaar == 1)
		{
			print_lcd();
		}
	twi_mt_zendboodschap(0x3A, 0x0,arr);
			//print resultaten interrupts
			if (MT_B.klaar == 1)
			{
				print_lcd();
			}
	twi_mt_zendboodschap(0x3B, 0x03,arr);
		//print resultaten interrupts
		if (MT_B.klaar == 1)
		{
			print_lcd();
		}
				
    while(1)
    {
		//print resultaten interrupts
		if (MT_B.klaar == 1)
		{
			print_lcd();
		}
		
		//als knop is ingedrukt : zend boodschap
		if ((bit_is_set(PINB,4)) )		//knop 
		{
			//knop is los
			// schakelen mogelijk
			blok = 0;
			//wacht op denderen
			_delay_ms(D_TIJD);
			//zet led uit
			PORTD |= _BV(7);

		}
		if (!bit_is_set(PINB,4) )
		{
			//knop is ingedrukt
			//blokkeer herhaling
			blok = 1;
			//wacht op denderen
			_delay_ms(D_TIJD);
			//zet led aan
			PORTD &= ~_BV(7);
			//maak vorige resultaten schoon
			lcd_clear();
			lcd_gotoxy(0,0);
			schrijftekst();
			//we zenden een Boodschap
			MT_B.data[0] = 0x00;
			MT_B.data[1] = 0x57;
			MT_B.data[0] = 0x77;
			MT_B.data[1] = 0x77;
			MT_B.data[1] = 0x77;
			MT_B.data[0] = 0x77;									
		//	twi_mt_zendboodschap(0x38, 0x06);
				//knop is ingedrukt
				//blokkeer herhaling
				blok = 1;
				//wacht op denderen
				_delay_ms(D_TIJD);
				//zet led aan
				PORTD &= ~_BV(7);
				//maak vorige resultaten schoon
				lcd_clear();
				lcd_gotoxy(0,0);
				schrijftekst();
				//we zenden een Boodschap
				MT_B.data[0] = 0x00;
				MT_B.data[1] = 0x57;
				MT_B.data[0] = 0x77;
				MT_B.data[1] = 0x77;
				MT_B.data[1] = 0x77;
				MT_B.data[0] = 0x77;
		//		twi_mt_zendboodschap(0x39, 0x06);
					//knop is ingedrukt
					//blokkeer herhaling
					blok = 1;
					//wacht op denderen
					_delay_ms(D_TIJD);
					//zet led aan
					PORTD &= ~_BV(7);
					//maak vorige resultaten schoon
					lcd_clear();
					lcd_gotoxy(0,0);
					schrijftekst();
					//we zenden een Boodschap
					MT_B.data[0] = 0x00;
					MT_B.data[1] = 0x57;
					MT_B.data[0] = 0x77;
					MT_B.data[1] = 0x77;
					MT_B.data[1] = 0x77;
					MT_B.data[0] = 0x77;
	//				twi_mt_zendboodschap(0x3B, 0x06);
		}
    }
}
//De interruptroutine wordt aantal + 1 keer doorlopen.
ISR(TWI_vect)
{
	//behandel de interrupts van TWI
	//eerste interrupt na START

	if (MT_B.teller == 0)
	{
		//lees TWSR_code na start
		Res.na_start = TWSR & 0xf8;
		switch(Res.na_start)
		{
			case 0x08:
			//laad nu SLA+W (Scbuif 1 plaats naar links voor R/W bit)
			TWDR = (MT_B.adres<<1) & 0xFE;
			TWCR = TWI_ADR_W;
			break;
			default:
			onbekende_fout();
		}

	}
	//Tweede interrupt na ADRES+R/W
	if (MT_B.teller == 1)
	{
		//lees status nadat adres + write is verzonden
		Res.na_adres = TWSR & 0xf8;
		switch(Res.na_adres)
		{
			case 0x18: //= Acknowledge na adres
			//laad nu data byte
			TWDR = MT_B.data[0];
			//verzend byte
			TWCR = TWI_DATA;
			break;
			case 0x20: //= No Acknowledge na adres
			// meld de fout
			MT_B.fout = 0x20;
			//stop verzenden
			TWCR = TWI_STOP;
			MT_B.teller = 0;
			MT_B.klaar = 1;
			break;
			default:
			onbekende_fout();
		}
	}
	//alle volgende interrupts na DATA
	if (MT_B.teller >1)
	{
		//lees status na data verzonden
		Res.na_data = TWSR & 0xf8;
		switch(Res.na_data)
		{
			case 0x28: //= Acknowledge na data
			//zijn we klaar?
			if ((MT_B.aantal+ 1) == MT_B.teller)
			{
				//we zijn klaar: stop verzenden
				TWCR = TWI_STOP;
				MT_B.teller = 0;
				MT_B.klaar = 1;
			}
			else
			{
				//laad nu volgende data
				TWDR = MT_B.data[MT_B.teller - 1];
				TWCR = TWI_DATA;
			}
			break;
			case 0x30: //= No Acknowledge na data
			// meld de fout
			MT_B.fout = 0x30;
			//stop verzenden
			TWCR = TWI_STOP;
			MT_B.teller = 0;
			MT_B.klaar = 1;
			break;
			default:
			onbekende_fout();
		}
		
	}
	if (MT_B.klaar == 0)
	{
		MT_B.teller += 1;
	}
}

ISR(INT2_vect)
{
	help = 1;
}