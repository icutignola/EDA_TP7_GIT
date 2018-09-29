#include "LCDConnect.h"
using namespace std;

void lcdWriteNibble(FT_HANDLE * ft, unsigned char nibble)
{
	unsigned char temp = nibble & 0xfe;
	DWORD byteSent = 0;
	FT_Write(ft, &temp, 1, &byteSent);
	Sleep(1);
	temp = nibble | 0x01;
	FT_Write(ft, &temp, 1, &byteSent);
	Sleep(3);
	temp = nibble & 0xfe;
	FT_Write(ft, &temp, 1, &byteSent);
	Sleep(1);
}

FT_HANDLE * init_ftdi_lcd(int iDevice)
{
	FT_STATUS statusOpen = !FT_OK;
	FT_STATUS statusSet = !FT_OK;
	FT_HANDLE lcdHandle = NULL;
	DWORD sizeSent = 0;
	string lcdDescriptionS = string(MY_LCD_DESCRIPTION + iDevice + string(PORT_B);
	char *lcdDescriptionC;
	strcpy(lcdDescriptionC, lcdDescriptionS.c_str());

	chrono::seconds MaxTime(CONNECTING_TIME);	// Determino un tiempo maximo para intentar conectarse 

	chrono::time_point<chrono::system_clock> start = chrono::system_clock::now(); //Dermino el tiempo actual
	chrono::time_point<chrono::system_clock> current = start;

	cout << "Conectando el LCD..." << endl;

	while (statusOpen != FT_OK && ((current - start) < MaxTime))
	{
		statusOpen = FT_OpenEx((void *)lcdDescriptionC, FT_OPEN_BY_DESCRIPTION, &lcdHandle);

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

	return &lcdHandle;
}

void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor)
{
	unsigned char temp = valor & 0xF0;
	temp = temp & 0xB0;
	lcdWriteNibble(deviceHandler, temp);
	temp = ((valor & 0x0F) << 4) & 0xF0;
	temp = temp  0x02;
	lcdWriteNibble(deviceHandler, temp);
}

void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor)
{
	unsigned char temp = valor & 0xF0;
	temp = temp | 0x02;
	lcdWriteNibble(deviceHandler, temp);
	temp = ((valor & 0x0F) << 4) & 0xF0;
	temp = temp | 0x02;
	lcdWriteNibble(deviceHandler, temp);
}

