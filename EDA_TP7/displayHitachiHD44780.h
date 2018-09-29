#pragma once
#include "basicLCD.h"
#include "LCDconnect.h"

#define LCD_NUMBER	1
#define FIRSTL_FIRSTC	1
#define FIRSTL_LASTC	16
#define SECONDL_FIRSTC	17
#define SECONDL_LASTC	32
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
	LCDConnect lcd;
	FT_HANDLE * lcdPointer;
	cursorPosition cursor;
	int cadd;



};

