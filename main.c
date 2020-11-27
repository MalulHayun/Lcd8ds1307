
#include "initsys.h"
#include "i2c.h"
#include "ds1307.h"

void Init_Device(void);

U8 T_second, T_minute, T_hour, month, year, date, ram;
U8 	second, minute, hour;

void main()
{
	Init_Device();
	initSYS();

	LCD_setTextSize(3);
	LCD_printC(20,40,"Test DS1307 ",3,WHITE);
	LCD_setText2Color(GREEN, BLACK);
	LCD_setTextSize(2);

	/****************** INIT RTC DS1307 ***********************/
	write_ds1307(0x07, 0x10);
	/**************************************************************/
	write_ds1307(0x02, 0x11); // hour
	write_ds1307(0x01, 0x01);  // minute
	write_ds1307(0x00, 0x00);  //sec
	write_ds1307(0x05, 0x02); //month
	write_ds1307(0x04, 0x01);  //date
	write_ds1307(0x06, 0x17);  //year

	while(1)
	{	
		T_hour = read_ds1307(0x02);
		T_minute = read_ds1307(0x01);
		T_second = read_ds1307(0x00);
		month = read_ds1307(0x05);
		date = read_ds1307(0x04);
		year = read_ds1307(0x06);

		LCD_setCursor(0,100);
		printf(" %bx:%bx:%bx  \n", T_hour, T_minute, T_second);
		printf(" %bx/%bx/%bx    ", date, month, year);


		delay_ms(100);	
	}
}
