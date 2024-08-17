#include <wiringPi.h>
#include <stdio.h>

#define PWM 26

int main(int argc,char **argv)
{   
    if(wiringPiSetup() < 0) //当使用这个函数初始化树莓派引脚时，程序使用的是wiringPi 引脚编号表。
        return 1;
    
    pinMode(PWM,PWM_OUTPUT); //设置引脚为PWM输出模式
    pwmSetMode (PWM_MODE_MS);
    pwmSetRange(1024);              // pwm脉宽范围 0~1024
    pwmSetClock(75);                // 250Hz，19.2MHz / 75 / 1024 = 250Hz
    pwmWrite(PWM,768);              // 设置占空比

    while (1)
    {

    }
    return 0;
}

// #define PWM1 1
// #define PWM2 23
// #define PWM3 24
// #define PWM4 26

// int main(int argc,char **argv)
// {   
//     if(wiringPiSetup() < 0) //当使用这个函数初始化树莓派引脚时，程序使用的是wiringPi 引脚编号表。
//         return 1;
    
//     pinMode(PWM1,PWM_OUTPUT); //设置引脚为PWM输出模式
//     pinMode(PWM2,PWM_OUTPUT); //设置引脚为PWM输出模式
//     pinMode(PWM3,PWM_OUTPUT); //设置引脚为PWM输出模式
//     pinMode(PWM4,PWM_OUTPUT); //设置引脚为PWM输出模式
//     pwmSetMode (PWM_MODE_MS);
//     pwmSetRange(1024);              // pwm脉宽范围 0~1024
//     pwmSetClock(75);                // 250Hz，19.2MHz / 75 / 1024 = 250Hz
//     pwmWrite(PWM1,512);              // 设置占空比
//     pwmWrite(PWM2,256);              // 设置占空比
//     pwmWrite(PWM3,768);              // 设置占空比
//     pwmWrite(PWM4,128);              // 设置占空比

//     while (1)
//     {

//     }
//     return 0;
// }

