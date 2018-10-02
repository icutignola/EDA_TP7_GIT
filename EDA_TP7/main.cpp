#include <iostream>
#include <string>
#include "LCDConnect.h"
#include "displayHitachiHD44780.h"


int main(void)
{
	//displayHitachiHD44780 lcd;
	LCDConnect a;

	FT_HANDLE * hola = a.init_ftdi_lcd(1);
	a.lcdWriteDR(hola, '0');

	//lcd << '0';
	//lcd << (unsigned char*) "hola";
	getchar();
	return 0;

}