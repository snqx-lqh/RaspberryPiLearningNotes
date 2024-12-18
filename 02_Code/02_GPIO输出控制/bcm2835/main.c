#include <bcm2835.h>

#define PIN 18

int main(int argc,char **argv)
{
    if(!bcm2835_init()) //初始化BCM相关的
        return 1;

    bcm2835_gpio_fsel(PIN,BCM2835_GPIO_FSEL_OUTP); //设置为输出模式
    
    while(1)
    {
        bcm2835_gpio_write(PIN,HIGH); 
        bcm2835_delay(500);
        bcm2835_gpio_write(PIN,LOW);
        bcm2835_delay(500);
    }
    
    bcm2835_close();
    return 0;
}