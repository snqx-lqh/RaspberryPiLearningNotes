#!/usr/bin/python3
# -*- coding: utf-8 -*-
from luma.core.interface.serial import i2c, spi
from luma.core.render import canvas
from luma.oled.device import ssd1306

# 创建 SPI 设备，使用 SPI-0  这里的gpio_RST gpio_DC是BCM编码
serial = spi(device=0, port=0, gpio_RST=21, gpio_DC=20)

# 创建屏幕的驱动实例
device = ssd1306(serial)

# 开始往屏幕上绘图。draw 是 Pillow 的实例，它里面还有非常多的绘图 API。
with canvas(device) as draw:
  draw.rectangle(device.bounding_box, outline="white", fill="black")
  draw.text((30, 40), "Hello World!", fill="white")

# 这行是为了阻止程序退出，因为退出的时候会调用析构函数，清空屏幕。防止一闪而过，什么也看不到。
while (True):
  pass

