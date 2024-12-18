#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <bcm2835.h>
#include "oled.h"

#define I2C_ADDR_OLED 0x3C
 
void oled_write_one_byte(uint8_t dat,uint8_t mode)
{
    char WriteBuf[2] = {mode,dat};
    bcm2835_i2c_write(WriteBuf,2);
}

int main(int argc, char **argv)
{
	if (!bcm2835_init())  
		return 1;  
 
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(I2C_ADDR_OLED);
    bcm2835_i2c_set_baudrate(100000); /* 100 KHz */

    OLED_Init();
    OLED_Clear();
    OLED_ShowString(0,0,(char*)"HELLO3",16,1);
    OLED_Refresh();//更新显示
 
    bcm2835_i2c_end();   
    bcm2835_close();
 
    return 0;
}



  