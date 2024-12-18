#include <wiringPi.h>

#define LED 1

int main(int argc,char **argv)
{
    if(wiringPiSetup() < 0) //当使用这个函数初始化树莓派引脚时，程序使用的是wiringPi 引脚编号表。
        return 1;
    pinMode(LED,OUTPUT); //设置引脚为输出模式
    while (1)
    {
        digitalWrite(LED,1);  
        delay(1000);
        digitalWrite(LED,0);  
        delay(1000);
    }
    return 0;
}