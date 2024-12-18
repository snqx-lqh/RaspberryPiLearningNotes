#include <wiringPi.h>
#include <stdio.h>

#define LED 1
#define KEY 0

void interruptKeyFunc(void);

int main(void)
{
    if(wiringPiSetup() < 0) //当使用这个函数初始化树莓派引脚时，程序使用的是wiringPi 引脚编号表。
        return 1;
    
    wiringPiISR(KEY,INT_EDGE_FALLING,&interruptKeyFunc);//注册引脚变化的中断服务函数
    pinMode(LED,OUTPUT); //设置引脚为输出模式
    
    while (1)
    {

    }
}
/*
中断服务函数，检测到按键下降沿触发
*/
void interruptKeyFunc(void)
{
    static int led_level;
    if(led_level == 0){
        led_level = 1;
    }else{
        led_level = 0;
    }
    printf("led_level %d",led_level);
    digitalWrite(LED,led_level);
}