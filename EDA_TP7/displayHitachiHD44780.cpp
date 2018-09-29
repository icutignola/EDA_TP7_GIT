#include "displayHitachiHD44780.h"
#include <iostream>
#include <cstdio>


displayHitachiHD44780::displayHitachiHD44780()
{
	lcdPointer = init_ftdi_lcd(LCD_NUMBER);
		
}


displayHitachiHD44780::~displayHitachiHD44780()
{
}

bool 
displayHitachiHD44780::lcdInitOk()
{
	return(lcdPointer == NULL);
}