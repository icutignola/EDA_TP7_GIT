#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <windows.h>
#include <chrono>

//**************  FTD2XX  ***************
#define FTD2XX_EXPORTS 
#include "ftd2xx.h"
//***************************************

//**********  Define Puertos  ***********
#define PORT_P0	0
#define PORT_P1	1
#define PORT_P2	2
#define PORT_P3	3
#define PORT_P4	4
#define PORT_P5	5
#define PORT_P6	6
#define PORT_P7	7
//***************************************

//*************  Define E  **************
#define LCD_E		(1<<PORT_P0)
#define LCD_E_ON	(LCD_E)
#define LCD_E_OFF	(LCD_E ^ LCD_E)
//***************************************

//*************  Define RS  *************
#define LCD_RS		(1<<PORT_P1)
#define LCD_RS_ON	(LCD_RS)
#define LCD_RS_OFF	(LCD_RS ^ LCD_RS)
//***************************************

//*************	Instrucciones del LCD	***********
#define LCD_CLEAR					0x01
#define LCD_RETURN_HOME				0x02
#define LCD_ENTRY_MODE_SET			0x03
#define LCD_DISPLAY_ON_OF_CONTROL	0x04
#define LCD_DISPLAY_SHIFT			0x05
#define LCD_FUNCTION_SET			0x06
#define LCD_SET_CGRAM_ADDRESS		0x07
#define LCD_DDRAM_ADRESS			0x08
#define LCD_READ_BUSY_FLAG_ADDRESS	0x09
//*************************************************

//********************	 LCD  *********************
#define MY_LCD_DESCRIPTION	"EDA LCD "
#define PORT_B				" B"			 
//*************************************************

#define CONNECTING_TIME 5 //in seconds


//************* Funciones de bajo nivel **********

void lcdWriteNibble(FT_HANDLE * ft, unsigned char nibble);

FT_HANDLE * init_ftdi_lcd(int iDevice);					//Funcion que inicializa el FTDI y el LCD

//Escribe un byte al IR
void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor);

//Escribe un byte al DR 
void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor);