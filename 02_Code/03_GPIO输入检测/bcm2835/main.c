#include <bcm2835.h>

#define LED 18
#define KEY 17

int main(int argc,char **argv)
{
    uint8_t keyValue = 0;
    if(!bcm2835_init()) //初始化BCM相关的
        return 1;

    //  设置KEY输入模式
    bcm2835_gpio_fsel(KEY, BCM2835_GPIO_FSEL_INPT);
    //  设置KEY上拉模式
    bcm2835_gpio_set_pud(KEY, BCM2835_GPIO_PUD_UP);
    //  设置LED输出模式
    bcm2835_gpio_fsel(LED,BCM2835_GPIO_FSEL_OUTP); 
    
    while(1)
    {
        keyValue = bcm2835_gpio_lev(KEY);
        if(keyValue == 0)
        {
            bcm2835_gpio_write(LED,LOW);      //设置引脚电平为0
        }else
        { 
            bcm2835_gpio_write(LED,HIGH);      //设置引脚电平为1
        }  
    }
    
    bcm2835_close();
    return 0;
}
