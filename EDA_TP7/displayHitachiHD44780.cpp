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
	if (lcdPointer == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

FT_STATUS 
displayHitachiHD44780::lcdGetError()
{

}

bool
displayHitachiHD44780::lcdClear()
{
	lcdWriteIR(lcdPointer,LCD_CLEAR);
}
bool
displayHitachiHD44780::lcdClearToEOL()
{
	/*Esta funcion basicamente recorre desde donde esta el puntero(cadd-1) hasta el final del display
	poniendo vacios en el data(lo ideal seria un clear de un solo bit, pero no encontre si existe).
	Los limites de navegacion deberian ser defines de las posiciones del lcd.
	El orden seria: 
					En que linea estoy?
					Limpio hasta el final de esa linea de a posicion por posicion
					si era la primera, tambien limpio la segunda, sino ya esta
					
	El tipo pide algun tipo de codigo de error. Solo se me ocurre que podria fallar si cadd-1 no esta en ninguna de las dos lineas.*/
					
}

bool
displayHitachiHD44780::lcdMoveCursorUp()
{
	/*Se fija en que linea esta, si esta en la de arriba, devuelve false.
	Si esta en la de abajo, se fija en que columna esta(distancia de cadd hasta el define del inicio de linea ) y pone cadd a esa misma distancia 
	en la linea de arriba*/
}
bool
displayHitachiHD44780::lcdMoveCursorDown()
{
	//igual que moveup pero con false en la segunda linea
}
bool
displayHitachiHD44780::lcdMoveCursorRight()
{
	/*Si esta en la segunda linea en la ultima columna, devuelve false, caso contrario, hace ++cadd
	Si esta en la primer linea en la ultima columna, apunta a la primera posicion de la segunda linea,
	si no es la ultima posicion, hace ++cadd*/
	
}
bool
displayHitachiHD44780::lcdMoveCursorLeft()
{
	//igual que right pero con los errores en primera linea
}
bool
displayHitachiHD44780::lcdSetCursorPosition(const cursorPosition pos)
{
	// pone cadd-1 donde me pasaron
}
cursorPosition
displayHitachiHD44780::lcdGetCursorPosition()
{
	 // devuelve la posicion de cadd-1
}
