#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <bcm2835.h>
#include "oled.h"

#define LCD_DC  20     // 模式选择 1：写数据 0：写命令
#define LCD_DIN 10     // 串行数据线
#define LCD_CLK 11     // 串行时钟线
#define LCD_RST 21     // 复位信号  低电平有效
#define LCD_CE  8     // 芯片使能  低电平有效

void oled_write_one_byte(uint8_t dat,uint8_t mode)
{ 
    if (mode == OLED_DATA) { // 写数据
        bcm2835_gpio_write(LCD_DC,HIGH);
    }
    else { // 写命令
        bcm2835_gpio_write(LCD_DC,LOW);
    }
    bcm2835_spi_transfer(dat);
}

void set_rst_level(uint8_t level)
{
    if(level == 1)
    {
        bcm2835_gpio_write(LCD_RST,HIGH);
    }else
    {
        bcm2835_gpio_write(LCD_RST,LOW);
    }
}

void delay_ms(uint8_t ms)
{
    bcm2835_delay(ms);
}

int main(int argc, char **argv)
{
	if (!bcm2835_init())//所有外围io引脚初始化，之前已经分析过了
    {
        printf("bcm2835_init failed. Are you running as root??\n");
        return 1;
    }

    bcm2835_gpio_fsel(LCD_DC, BCM2835_GPIO_FSEL_OUTP); //设置为输出模式
    bcm2835_gpio_fsel(LCD_RST,BCM2835_GPIO_FSEL_OUTP); //设置为输出模式

    if (!bcm2835_spi_begin())    {
        printf("bcm2835_spi_begin failed. Are you running as root??\n");
        return 1;
    }

    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);  
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0); 
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_32);  
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW); 

    OLED_Init();
    OLED_Clear();
    OLED_ShowString(0,0,(char*)"HELLO3 world",16,1);
    OLED_Refresh();//更新显示
    
     
    bcm2835_spi_end();  
    bcm2835_close();
 
    return 0;
}



  