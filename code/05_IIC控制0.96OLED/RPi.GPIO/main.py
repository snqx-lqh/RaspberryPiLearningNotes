#!/usr/bin/python3
# -*- coding: utf-8 -*-
from luma.core.interface.serial import i2c, spi
from luma.core.render import canvas
from luma.oled.device import ssd1306, ssd1325, ssd1331, sh1106
from time import sleep
"""
OLED luma 驱动库测试程序
功能：显示 hello world 和矩形外框持续10秒
"""
__version__ = 1.0
# 初始化端口
serial = i2c(port=1, address=0x3C)
# 初始化设备，这里改ssd1306, ssd1325, ssd1331, sh1106
device = ssd1306(serial)
print("当前版本：", __version__)
# 调用显示函数
with canvas(device) as draw:
    draw.rectangle(device.bounding_box, outline="white", fill="black")
    draw.text((30, 20), "Hello World", fill="white")

# 延时显示10s
sleep(10)

