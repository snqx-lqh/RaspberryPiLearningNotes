#!/usr/bin/python
# -*- coding:utf-8 -*-
import RPi.GPIO as GPIO
import time

LED = 18

GPIO.setmode(GPIO.BCM)    #采用BCM编号方式
GPIO.setup(LED,GPIO.OUT)  #设置输出模式

try:
    while True:
        GPIO.output(LED,GPIO.HIGH)
        time.sleep(1)
        GPIO.output(LED,GPIO.LOW)
        time.sleep(1)
except:
    print("except")

GPIO.cleanup()