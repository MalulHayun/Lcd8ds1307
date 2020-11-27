#include "compiler_defs.h"
#include "C8051F380_defs.h"
#include "i2c.h"

#define DS1307_address 0x68  // 110_1000

//************* DS1307 ***********

bit write_ds1307(unsigned char add,unsigned char outchar)
{
	bit ask=1;
	Wire_start();
	if(!Wire_write(DS1307_address<<1)) // 11010000
	{
		ask=Wire_write(add);//address
		ask=Wire_write(outchar);
	}
	Wire_stop();
	return ask; //if ask=0 data ok
}


unsigned char read_ds1307(unsigned char add)
{

	unsigned char inchar = 0;
	Wire_start();
	if(!Wire_write(DS1307_address<<1))
	{
		Wire_write(add);

		Wire_stop();
		Wire_start();
		Wire_write((DS1307_address<<1) | 1); // 11010001
		inchar=Wire_read(1);  //1- read byte and finish
	}
	Wire_stop();
	return inchar;	
}

