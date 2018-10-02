#include "displayHitachiHD44780.h"
#include <iostream>
#include <cstdio>


displayHitachiHD44780::displayHitachiHD44780() //Poner en modo 4 bits
{
	lcdPointer = lcd.init_ftdi_lcd(LCD_NUMBER);
	cadd = 1;
	FT_STATUS status = FT_OK;	
}

displayHitachiHD44780::~displayHitachiHD44780()
{
	FT_Close(lcdPointer);
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
	FT_STATUS answer;
	answer = lcd.getStatus();
	return answer;
}

bool
displayHitachiHD44780::lcdClear()
{
	lcd.lcdWriteIR(lcdPointer,LCD_CLEAR);
	return true;
}

bool
displayHitachiHD44780::lcdClearToEOL()
{
	bool answer = false;

	if ((cadd >= FIRSTL_FIRSTC && cadd <= FIRSTL_LASTC) || (cadd >= SECONDL_FIRSTC && cadd <= SECONDL_LASTC))
	{
		displayHitachiHD44780 lcd_aux;
		
		for(int i=1 ; i<=cadd ; i++)
		{
			lcd_aux << ' '; // voy completando con espacios vacios
		}

		answer = true;
	
	}

	return answer;	
}

basicLCD & displayHitachiHD44780::operator<<(const unsigned char c)
{
	FT_HANDLE lcd_aux = *lcdPointer;
	lcd.lcdWriteDR(lcd_aux, c);	// imprimo  el caracter que recibo 
	lcdMoveCursorRight();			// actualizo el cursor a la nueva posicion	 
	return *this;
}

basicLCD & displayHitachiHD44780::operator<<(const unsigned char * c)
{
	int i = 0;
	while( c[i] != '\0') // mientras que no llego al final del string
	{
		lcd.lcdWriteDR(lcdPointer, c[i]); // voy imprimiendo letra por letra del string
		i++; // paso a la letra siguiente
		lcdMoveCursorRight();
	}
	return *this;
}

bool
displayHitachiHD44780::lcdMoveCursorUp()
{
	bool answer = false;

	if (cadd >= SECONDL_FIRSTC && cadd <= SECONDL_LASTC)	//Segunda linea
	{
		cadd -= DISPLAY_OFFSET;					//Muevo el cadd a la primera linea, misma columna
			
		BYTE valor_aux = 0x00;					//Posicion: 00000000 (0x00)
		valor_aux |= (cadd-1);					//Posicion: 0000XXXX (XXXX = cadd) 
		valor_aux |= LCD_WRITE_AC;				//Posicion: 1000XXXX (XXXX = cadd)
		lcd.lcdWriteIR(lcdPointer, valor_aux);	
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
		BYTE valor_aux = 0x40;						//Posicion: 01000000 (0x00)
		valor_aux |= (cadd-1);						//Posicion: 0100XXXX (XXXX = cadd)
		valor_aux |= LCD_WRITE_AC;					//Posicion: 1100XXXX (XXXX = cadd)
		cadd += DISPLAY_OFFSET;						//Muevo el cadd a la segunda linea, misma columna
		lcd.lcdWriteIR(lcdPointer, valor_aux);
		answer = true;
	}

	return answer;
}

bool
displayHitachiHD44780::lcdMoveCursorRight()
{
	bool answer = false;

	if (cadd >= FIRSTL_FIRSTC && cadd < FIRSTL_LASTC)	// 1 <= cad < 16
	{
		cadd++;
		BYTE valor_aux = 0x00;						//Posicion: 01000000 (0x00)
		valor_aux |= (cadd - 1);					//Posicion: 0100XXXX (XXXX = cadd)
		valor_aux |= LCD_WRITE_AC;					//Posicion: 1100XXXX (XXXX = cadd)
		lcd.lcdWriteIR(lcdPointer, valor_aux);
		answer = true;
	}

	else if (cadd == FIRSTL_LASTC)	
	{
		cadd = SECONDL_FIRSTC;						//cadd == 17
		BYTE valor_aux = 0x40;						//Posicion: 01000000 (0x00)
		valor_aux |= (cadd - DISPLAY_OFFSET - 1);	//Posicion: 01000000 (17-1-16 = 0)
		valor_aux |= LCD_WRITE_AC;					//Posicion: 11000000 
		lcd.lcdWriteIR(lcdPointer, valor_aux);
		answer = true;
	}

	else if (cadd >= SECONDL_FIRSTC && cadd <= SECONDL_LASTC)
	{
		cadd++;
		BYTE valor_aux = 0x40;						//Posicion: 01000000 (0x00)
		valor_aux |= (cadd - DISPLAY_OFFSET - 1);	//Posicion: 0000XXXX (XXXX = cadd) 
		valor_aux |= LCD_WRITE_AC;					//Posicion: 1000XXXX (XXXX = cadd)
		lcd.lcdWriteIR(lcdPointer, valor_aux);
		answer = true;
	}

	else if (cadd == SECONDL_LASTC)
	{
		cadd = FIRSTL_FIRSTC;						//cadd == 1
		BYTE valor_aux = 0x00;						//Posicion: 01000000 (0x00)
		valor_aux |= (cadd - 1);					//Posicion: 01000000 (1-1 = 0)
		valor_aux |= LCD_WRITE_AC;					//Posicion: 11000000 
		lcd.lcdWriteIR(lcdPointer, valor_aux);
		answer = true;
	}

	return answer;	
}

bool
displayHitachiHD44780::lcdMoveCursorLeft()
{
	bool answer = false;

	if (cadd > FIRSTL_FIRSTC && cadd <= FIRSTL_LASTC)	// 1 <= cad < 16
	{
		cadd--;
		BYTE valor_aux = 0x00;						//Posicion: 01000000 (0x00)
		valor_aux |= (cadd - 1);					//Posicion: 0100XXXX (XXXX = cadd)
		valor_aux |= LCD_WRITE_AC;					//Posicion: 1100XXXX (XXXX = cadd)
		lcd.lcdWriteIR(lcdPointer, valor_aux);
		answer = true;
	}

	else if (cadd == FIRSTL_FIRSTC)
	{
		cadd = SECONDL_LASTC;						//cadd == 32
		BYTE valor_aux = 0x40;						//Posicion: 01000000 (0x00)
		valor_aux |= (cadd - DISPLAY_OFFSET - 1);	//Posicion: 01000000 (32-1-16 = 15)
		valor_aux |= LCD_WRITE_AC;					//Posicion: 11001111
		lcd.lcdWriteIR(lcdPointer, valor_aux);
		answer = true;
	}

	else if (cadd > SECONDL_FIRSTC && cadd <= SECONDL_LASTC)
	{
		cadd--;
		BYTE valor_aux = 0x40;						//Posicion: 01000000 (0x00)
		valor_aux |= (cadd - DISPLAY_OFFSET - 1);	//Posicion: 0000XXXX (XXXX = cadd) 
		valor_aux |= LCD_WRITE_AC;					//Posicion: 1000XXXX (XXXX = cadd)
		lcd.lcdWriteIR(lcdPointer, valor_aux);
		answer = true;
	}

	else if (cadd == SECONDL_FIRSTC)
	{
		cadd = FIRSTL_LASTC;						//cadd == 16
		BYTE valor_aux = 0x00;						//Posicion: 01000000 (0x00)
		valor_aux |= (cadd - 1);					//Posicion: 01001111 (16-1 = 15)
		valor_aux |= LCD_WRITE_AC;					//Posicion: 11001111
		lcd.lcdWriteIR(lcdPointer, valor_aux);
		answer = true;
	}

	return answer;
}

bool
displayHitachiHD44780::lcdSetCursorPosition(const cursorPosition pos)
{
	bool answer = false;
	if ((pos.row == FIRST_LINE || pos.row == FIRST_LINE) && (pos.column >= FIRST_COLUMN && pos.column <= LAST_COLUMN))
	{
		BYTE valor;
		BYTE row = ((pos.row * 4) << 4) & 0xF0;
		BYTE column = (pos.column - 1) & 0x0F;
		valor = row | column | LCD_WRITE_AC;
		lcd.lcdWriteIR(lcdPointer, valor);

		//Actualizo el cadd
		if (pos.row == FIRST_LINE)
		{
			cadd = pos.column + 1;
		}
		else if (pos.row == SECOND_LINE)
		{
			cadd = DISPLAY_OFFSET + pos.column + 1;
		}
		answer = true;
	}
	return answer;

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
		posAnswer.column = (cadd - DISPLAY_OFFSET);
	}

	else //Error
	{
		posAnswer.row = (-1);
		posAnswer.column = (-1);
	}
	
	return posAnswer;
}



