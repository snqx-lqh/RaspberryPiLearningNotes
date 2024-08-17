#include <wiringPi.h>
#include <stdio.h>
#include <wiringPiI2C.h>
#include "oled.h"
#include <wiringPiSPI.h>

#define LCD_DC  28     // 模式选择 1：写数据 0：写命令
#define LCD_DIN 12     // 串行数据线
#define LCD_CLK 14     // 串行时钟线
#define LCD_RST 29     // 复位信号  低电平有效
#define LCD_CE  10     // 芯片使能  低电平有效

#define SPI_CHANNEL 0

void oled_write_one_byte(uint8_t dat,uint8_t mode)
{ 
    //digitalWrite(LCD_CE,LOW);
    if (mode == OLED_DATA) { // 写数据
        digitalWrite(LCD_DC,HIGH);
    }
    else { // 写命令
        digitalWrite(LCD_DC,LOW);
    }
    //uint8_t *tempData = &dat;
    wiringPiSPIDataRW(SPI_CHANNEL, &dat, 1);
    //digitalWrite (LCD_CE, HIGH);
}

void set_rst_level(uint8_t level)
{
    if(level == 1)
    {
        digitalWrite(LCD_RST,HIGH);
    }else
    {
        digitalWrite(LCD_RST,LOW);
    }
}

void delay_ms(uint8_t ms)
{
    delay(ms);
}

int main(void)
{ 
    if(wiringPiSetup() < 0) //当使用这个函数初始化树莓派引脚时，程序使用的是wiringPi 引脚编号表。
    {
        printf("wiringPiSetup失败\n");
        return 1;
    }   

    pinMode(LCD_DC,OUTPUT);
    pinMode(LCD_RST,OUTPUT);
    //pinMode(LCD_CE,OUTPUT);
    //int isOK =wiringPiSPISetupMode (0, 500000, 0);
    int isOK = wiringPiSPISetup(SPI_CHANNEL, 500000);
    if (isOK == -1) {
        printf("SPI设置失败\n");
    }
    else {
        printf("SPI设置OK == %d\n",isOK);
    }
 
    OLED_Init();
    OLED_Clear();
    OLED_ShowString(0,0,(char*)"HELLO 44444",16,1);
    OLED_Refresh();//更新显示
    
    wiringPiSPIClose(SPI_CHANNEL);
    return 0;
}
 
