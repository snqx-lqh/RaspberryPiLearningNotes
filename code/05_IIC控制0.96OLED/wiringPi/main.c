#include <wiringPi.h>
#include <stdio.h>
#include <wiringPiI2C.h>
#include "oled.h"
 
int fd;

void oled_write_one_byte(uint8_t dat,uint8_t mode)
{
    wiringPiI2CWriteReg8(fd,mode,dat);
}

int main(void)
{ 
    if(wiringPiSetup() < 0) //当使用这个函数初始化树莓派引脚时，程序使用的是wiringPi 引脚编号表。
        return 1;
    fd = wiringPiI2CSetup (SlaveAddress);
    if(fd < 0)
    {
        printf("IIC初始化失败\r\n");
        return fd;
    }

    OLED_Init();
    OLED_Clear();
    OLED_ShowString(0,0,(char*)"HELLO2",16,1);
    OLED_Refresh();//更新显示
 
    return 0;
}
 
