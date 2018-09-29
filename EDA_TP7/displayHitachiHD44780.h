#pragma once
#include "basicLCD.h"
#include "LCDconnect.h"

#define LCD_NUMBER 1
class displayHitachiHD44780 :
	public basicLCD
{
public:
	displayHitachiHD44780();
	~displayHitachiHD44780();
	virtual bool lcdInitOk();
	virtual FT_STATUS lcdGetError();
	virtual bool lcdClear();
	virtual bool lcdClearToEOL();
	virtual basicLCD& operator<<(const unsigned char c);
	virtual basicLCD& operator<<(const unsigned char * c);
	virtual bool lcdMoveCursorUp();
	virtual bool lcdMoveCursorDown();
	virtual bool lcdMoveCursorRight();
	virtual bool lcdMoveCursorLeft();
	virtual bool lcdSetCursorPosition(const cursorPosition pos);
	virtual cursorPosition lcdGetCursorPosition();
	

private:
	FT_HANDLE * lcdPointer;

};

