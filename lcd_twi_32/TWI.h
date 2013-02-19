//TWI.h : header file for the Two-wire Serial Interface
//

#ifndef _32TEST2TWI_H_
#define _32TEST2TWI_H_

#define TWI_START	0xA5;
#define TWI_STOP	0x94;
#define TWI_ADR_W	0x85;
#define TWI_DATA	0x85;
/////////////////////////////////////////////////////////////////////////////
//TWI
//definitie van een struct voor verzenden
struct mt_boodschap
{
	uint8_t adres;
	uint8_t data[10];
	uint8_t aantal;
	uint8_t fout;
	uint8_t klaar;
	uint8_t teller;
};

//definitie van een struct voor de resultaten
struct resultaten
{
	uint8_t na_start;
	uint8_t na_adres;
	uint8_t na_data;
	uint16_t data;
};

//de functies
void twi_init(void);
uint8_t twi_mt_zendboodschap(uint8_t adres,uint8_t aantal, uint8_t* arr);

#endif // _32TEST2TWI_H_
