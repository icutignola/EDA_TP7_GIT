#include <iostream>
#include <string>
#include "displayHitachiHD44780.h"


int main(void)
{
	displayHitachiHD44780 lcd;
	
	lcd << 'h';
	lcd << (unsigned char*) "hola";

	return 0;

}