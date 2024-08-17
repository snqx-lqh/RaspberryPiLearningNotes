#include <wiringPi.h>
#include <stdio.h>

#define LED 1
#define KEY 0

int main(int argc,char **argv)
{
    int key_value = 0;

    if(wiringPiSetup() < 0) //当使用这个函数初始化树莓派引脚时，程序使用的是wiringPi 引脚编号表。
        return 1;
    
    pinMode(KEY,INPUT);  //设置引脚为输入模式
    pinMode(LED,OUTPUT); //设置引脚为输出模式
    
    while (1)
    {
        key_value = digitalRead(KEY); //读取引脚电平
        if(key_value == 0)
        {
            digitalWrite(LED,0);      //设置引脚电平为0
        }else
        { 
            digitalWrite(LED,1);      //设置引脚电平为1
        }  
    }
    return 0;
}