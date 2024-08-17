#include <bcm2835.h>

#define PWM 18
#define PWM_CHANNEL 0

int main(int argc,char **argv)
{
    if(!bcm2835_init()) //初始化BCM相关的
        return 1;

    // 配置引脚为PWM输出模式
    bcm2835_gpio_fsel(PWM, BCM2835_GPIO_FSEL_ALT5);
    
    // 时钟分频设置为16. 19.2Mhz/16 = 1.2Mhz
    bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
    // 设置模式
    bcm2835_pwm_set_mode(PWM_CHANNEL, 1, 1);
    // 1.2MHz/1024 = 1171.875Hz,  设置计数值
    bcm2835_pwm_set_range(PWM_CHANNEL, 1024);
    bcm2835_pwm_set_data(PWM_CHANNEL, 256);

    while(1)
    {
         
    }
    
    bcm2835_close();
    return 0;
}

 