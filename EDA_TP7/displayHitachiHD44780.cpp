#include "displayHitachiHD44780.h"
#include <iostream>
#include <cstdio>


displayHitachiHD44780::displayHitachiHD44780()
{
	lcdPointer = lcd.init_ftdi_lcd(LCD_NUMBER);
	cadd = 1;
}

displayHitachiHD44780::~displayHitachiHD44780()
{
}

bool 
displayHitachiHD44780::lcdInitOk()
{
	bool answer;
	if (lcdPointer == NULL)
	{
		answer = false;
	}
	else
	{
		answer = true;
	}
	return answer;
}

FT_STATUS 
displayHitachiHD44780::lcdGetError()
{

}

bool
displayHitachiHD44780::lcdClear()
{
	lcd.lcdWriteIR(lcdPointer,LCD_CLEAR);
}
bool
displayHitachiHD44780::lcdClearToEOL()
{
	if ((cadd >= FIRSTL_FIRSTC && cadd <= FIRSTL_LASTC) || (cadd >= SECONDL_FIRSTC && cadd <= SECONDL_LASTC))
	{

	}
	else
	{
		//error
	}
		
	/*Esta funcion basicamente recorre desde donde esta el puntero(cadd-1) hasta el final del display
	poniendo vacios en el data(lo ideal seria un clear de un solo bit, pero no encontre si existe).
	Los limites de navegacion deberian ser defines de las posiciones del lcd.
	El orden seria: 
					En que linea estoy?
					Limpio hasta el final de esa linea de a posicion por posicion
					si era la primera, tambien limpio la segunda, sino ya esta
					
	El tipo pide algun tipo de codigo de error. Solo se me ocurre que podria fallar si cadd-1 no esta en ninguna de las dos lineas.*/
					
}

basicLCD & displayHitachiHD44780::operator<<(const unsigned char c)
{
	// TODO: insertar una instrucción return aquí
}

basicLCD & displayHitachiHD44780::operator<<(const unsigned char * c)
{
	// TODO: insertar una instrucción return aquí
}

bool
displayHitachiHD44780::lcdMoveCursorUp()
{
	bool answer = false;

	if (cadd >= SECONDL_FIRSTC && cadd <= SECONDL_LASTC)	//Segunda linea
	{
		cadd -= 16;
		answer = true;
	}
	
	return answer;
}

bool
displayHitachiHD44780::lcdMoveCursorDown()
{
	bool answer = false;

	if ((cadd >= FIRSTL_FIRSTC && cadd <= FIRSTL_LASTC))	//Segunda linea
	{
		cadd += 16;
		answer = true;
	}

	return answer;
}

bool
displayHitachiHD44780::lcdMoveCursorRight()
{
	bool answer = false;

	if ((cadd >= FIRSTL_FIRSTC && cadd <= FIRSTL_LASTC) || (cadd >= SECONDL_FIRSTC && cadd <= SECONDL_LASTC))
	{
		if (cadd == SECONDL_LASTC)
		{
			cadd = FIRSTL_FIRSTC;
			answer = true;
		}
		else
		{
			cadd++;
			answer = true;
		}
	}

	return answer;	
}

bool
displayHitachiHD44780::lcdMoveCursorLeft()
{
	bool answer = false;

	if ((cadd >= FIRSTL_FIRSTC && cadd <= FIRSTL_LASTC) || (cadd >= SECONDL_FIRSTC && cadd <= SECONDL_LASTC))
	{
		if (cadd == FIRSTL_FIRSTC)
		{
			cadd = SECONDL_LASTC;
			answer = true;
		}
		else
		{
			cadd--;
			answer = true;
		}
	}

	return answer;
}

bool
displayHitachiHD44780::lcdSetCursorPosition(const cursorPosition pos)
{
	BYTE valor;
	BYTE row = ((pos.row * 4) << 4) & 0xF0;
	BYTE column = (pos.column - 1) & 0x0F;
	valor = row | column | LCD_WRITE_AC;
	lcd.lcdWriteIR(lcdPointer, valor);
}
cursorPosition
displayHitachiHD44780::lcdGetCursorPosition()
{
	cursorPosition posAnswer;
	if ((cadd >= FIRSTL_FIRSTC && cadd <= FIRSTL_LASTC))	//Primera linea
	{
		posAnswer.row = 0;
		posAnswer.column = cadd;
	}

	else if (cadd >= SECONDL_FIRSTC && cadd <= SECONDL_LASTC)	//Segunda linea
	{
		posAnswer.row = 1;
		posAnswer.column = (cadd - 16);
	}

	else //Error
	{
		posAnswer.row = (-1);
		posAnswer.column = (-1);
	}
	
	return posAnswer;
}
