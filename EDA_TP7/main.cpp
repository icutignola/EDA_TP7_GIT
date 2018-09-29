#include <iostream>
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
#define MY_LCD_DESCRIPTION "EDA LCD 6" 
//*************************************************

#define CONNECTING_TIME 5 //in seconds

using namespace std;


//************* Funciones de bajo nivel **********

void lcdWriteNibble(FT_HANDLE * ft, unsigned char nibble);

FT_HANDLE * init_ftdi_lcd(int iDevice);					//Funcion que inicializa el FTDI y el LCD

//Escribe un byte al IR
void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor);	

//Escribe un byte al DR 
void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor);




void lcdWriteNibble(FT_HANDLE * ft, unsigned char nibble)
{
	unsigned char temp = nibble & 0xfe;
	FT_Write(ft, temp, 1, &bytesSent);
	Sleep(1);
	temp = nibble | 0x01;
	FT_Write(ft, temp, 1, &byteSent);
	Sleep(3);
	temp = nibble & 0xfe;
	FT_Write(ft, temp, 1, byteSent);
	Sleep(1);
}

FT_HANDLE * init_ftdi_lcd(int iDevice)
{
	FT_STATUS statusOpen = !FT_OK;
	FT_STATUS statusSet = !FT_OK;
	FT_HANDLE lcdHandle = NULL;
	DWORD sizeSent = 0;

	chrono::seconds MaxTime(CONNECTING_TIME);	// Determino un tiempo maximo para intentar conectarse 

	chrono::time_point<chrono::system_clock> start = chrono::system_clock::now(); //Dermino el tiempo actual
	chrono::time_point<chrono::system_clock> current = start;

	cout << "Conectando el LCD..." << endl;

	while (statusOpen != FT_OK && ((current - start) < MaxTime))
	{
		statusOpen = FT_OpenEx((void *)MY_LCD_DESCRIPTION, FT_OPEN_BY_DESCRIPTION, &lcdHandle);

		if (statusOpen == FT_OK)
		{
			cout << "Se ha podidio conectar el LCD" << endl;
			UCHAR Mask = 0xFF;	//Selects all FTDI pins.
			UCHAR Mode = 1; 	// Set asynchronous bit-bang mode
			statusSet = FT_SetBitMode(lcdHandle, Mask, Mode);
			if (statusSet == FT_OK)
			{
				cout << "Se configuro el LCD de forma correcta" << endl;
			}
			else
			{
				cout << "Error al configurar el LCD" << endl;
			}
		}
		else
		{
			cout << "Error al conectar con el LCD" << endl;
		}
		current = std::chrono::system_clock::now();
	}

	return lcdHandle;
}

void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor)
{
	
}

void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor)
{
	unsigned char temp = valor & 0xF0;
	temp = temp | 0x02;
	lcdWriteNibble(deviceHandler, temp);
	temp = ((valor & 0x0F) << 4) & 0x0F;
	temp = temp | 0x02;
	lcdWriteNibble(deviceHandler, temp);
}