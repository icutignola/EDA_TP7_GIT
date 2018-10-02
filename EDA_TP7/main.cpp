#include <iostream>
#include <string>
#include "displayHitachiHD44780.h"


int main(void)
{
	displayHitachiHD44780 lcd;
	
	lcd << '1';
	//lcd << (unsigned char*) "hola";
	getchar();
	return 0;

}