#include <lpc214x.h>
#include "LPC2148_delay.h"
#include "LPC2148_LCD_4_BIT_HEADER_FILE.h"

#define SW 0x80000000

int Count=0;

void divider(int x)
{
	int Temp,Dig1,Dig2;
	
	Temp = x;

	Dig1 = Temp/10;
	Lcd_Data(Dig1+48);

	Dig2 = Temp%10;
	Lcd_Data(Dig2+48);
}

int main()
{
	PINSEL0 = 0x00000000;
	PINSEL1 = 0x00000000;
	IODIR0 = 0x000003F0;

	Lcd_Intialization();
	
	Lcd_Command(0x80);
	Lcd_String("LYCA SOFT");
	
	while(1)
	{
		while((IO0PIN & (1<<31)) ==  0)
		{
			Count++;

			if(Count > 100)
			{
				Count = 0;
			}
			
			Lcd_Command(0xC0);
			divider(Count);

			while((IO0PIN & (1<<31)) ==  0);
		}
	}
}