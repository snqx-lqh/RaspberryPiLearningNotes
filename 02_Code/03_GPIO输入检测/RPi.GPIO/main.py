#!/usr/bin/python
# -*- coding:utf-8 -*-
import RPi.GPIO as GPIO
import time

LED = 18
KEY = 17

GPIO.setmode(GPIO.BCM)    #采用BCM编号方式
GPIO.setup(LED,GPIO.OUT)  #设置输出模式
GPIO.setup(KEY, GPIO.IN, pull_up_down=GPIO.PUD_UP)  #设置输入模式，输入上拉，下拉是GPIO.PUD_DOWN

keyValue = 0

try:
    while True:
        keyValue = GPIO.input(KEY)
        if keyValue:
            GPIO.output(LED,GPIO.HIGH)
        else:
            GPIO.output(LED,GPIO.LOW)
except:
    print("except")

GPIO.cleanup()