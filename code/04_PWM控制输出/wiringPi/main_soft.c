#include <wiringPi.h>
#include <stdio.h>

#include <softPwm.h>

#define PWM 4

int main(int argc,char **argv)
{   
    if(wiringPiSetup() < 0) //当使用这个函数初始化树莓派引脚时，程序使用的是wiringPi 引脚编号表。
        return 1;
    
    pinMode(PWM,OUTPUT); //设置引脚为 输出模式
    //PWMfreq = 1 x 10^6 / (100 x range)  需要50hz 
    softPwmCreate(PWM , 0, 200);// 设置周期分为200份
    softPwmWrite(PWM , 50);

    while (1)
    {

    }
    return 0;
}

