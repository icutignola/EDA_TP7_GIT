#include <iostream>
#include <string>
#include "displayHitachiHD44780.h"



int main(void)
{
	cursorPosition pos;
	pos.row = FIRST_LINE;
	pos.column = FIRST_COLUMN;
	displayHitachiHD44780 hitachi;

	//Primer imagen
	hitachi << (unsigned char *) "Hola!!!";
	pos.row = SECOND_LINE;
	pos.column = FIRST_COLUMN;
	hitachi.lcdSetCursorPosition(pos);
	hitachi << (unsigned char *) "Presione enter";
	getchar();

	//Segunda imagen
	hitachi.lcdClear();
	pos.row = FIRST_LINE;
	pos.column = FIRST_COLUMN;
	hitachi.lcdSetCursorPosition(pos);
	hitachi << (unsigned char *) "Strings:";
	pos.row = SECOND_LINE;
	pos.column = FIRST_COLUMN;	
	hitachi.lcdSetCursorPosition(pos);
	hitachi << (unsigned char *) "Presione enter";
	getchar();

	//Tercer imagen
	hitachi.lcdClear();
	pos.row = FIRST_LINE;
	pos.column = FIRST_COLUMN;
	hitachi.lcdSetCursorPosition(pos);
	hitachi << (unsigned char *) "Hola";
	Sleep(1000);

	//Tercer imagen
	hitachi.lcdClear();
	pos.row = FIRST_LINE;
	pos.column = FIRST_COLUMN;
	hitachi.lcdSetCursorPosition(pos);
	hitachi << (unsigned char *) "Chau";
	Sleep(1000);

	//Segunda imagen
	hitachi.lcdClear();
	pos.row = FIRST_LINE;
	pos.column = FIRST_COLUMN;
	hitachi.lcdSetCursorPosition(pos);
	hitachi << (unsigned char *) "Carac.:";
	pos.row = SECOND_LINE;
	pos.column = FIRST_COLUMN;
	hitachi.lcdSetCursorPosition(pos);
	hitachi << (unsigned char *) "Presione enter";
	getchar();

	//Cuarta imagen
	hitachi.lcdClear();
	pos.row = FIRST_LINE;
	pos.column = FIRST_COLUMN;
	hitachi.lcdSetCursorPosition(pos);
	hitachi << 'A';
	Sleep(1000);

	//Quinta imagen
	hitachi.lcdClear();
	pos.row = FIRST_LINE;
	pos.column = FIRST_COLUMN;
	hitachi.lcdSetCursorPosition(pos);
	hitachi << 'B';
	Sleep(1000);

	//Sexta imagen
	hitachi.lcdClear();
	pos.row = FIRST_LINE;
	pos.column = FIRST_COLUMN;
	hitachi.lcdSetCursorPosition(pos);
	hitachi << 'C';
	Sleep(1000);

	//Septima imagen
	hitachi.lcdClear();
	pos.row = FIRST_LINE;
	pos.column = FIRST_COLUMN;
	hitachi.lcdSetCursorPosition(pos);
	hitachi << (unsigned char *) "Presione enter";
	getchar();

	//Octava imagen
	hitachi.lcdClear();
	pos.row = FIRST_LINE;
	pos.column = FIRST_COLUMN;
	hitachi.lcdSetCursorPosition(pos);
	hitachi << (unsigned char *) "Saludos";
	Sleep(2000);

	return 0;

}