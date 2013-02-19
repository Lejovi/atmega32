//32test2TWI.cpp : source file for the 32test2 Two-wire Serial Interface
//

#include "lcd.h"
#include "TWI.h"
 
#include "lcd_twi_32.h"
 
#include <avr/io.h>
#include <avr/interrupt.h>

//globale variabelen
struct mt_boodschap MT_B;
struct resultaten Res;
/////////////////////////////////////////////////////////////////////////////
//32test2TWI

void twi_init(void)
{
	//{{WIZARD_MAP(TWI)
	// SCL frequency: 444.444 kHz
	//TWBR = 0x0a;
	//TWSR = 0x00;
	//TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1<<TWIE);
	//}}WIZARD_MAP(TWI)
	
		SFIOR &= ~_BV(PUD);
		// SCL = CPU / (16 + 2*TWBR + 4expTWPS)
		//voor TWBR = 0x12 en TWPS = 1 (TWSR = 0x00) levert dit 100kHz op
		TWBR = 0x12; //aanvankelijke tests met 0xFF
		TWSR = 0x00; //aanvankelijke tests met 0x03
		DDRC = 0x00; //pull-up weerstanden uit
		TWAR = 0x03;
		TWCR = 0x85; //TWINT wordt gecleared,TWEN en TWIE geset
		
		
}

//Zend een boodschap naar slave
uint8_t twi_mt_zendboodschap(uint8_t adres,uint8_t aantal, uint8_t* arr)
{
	//bewaar gegevens
	MT_B.adres = adres;
	MT_B.aantal = aantal;
	for (int i=0 ; i<aantal; i++) MT_B.data[i] = arr[i];
	//zet fout op 0
	MT_B.fout = 0;
	//zend start
	sei();
	TWCR = TWI_START;
	//wacht tot overdracht klaar
	while (MT_B.klaar == 0);
	return MT_B.klaar;
}
