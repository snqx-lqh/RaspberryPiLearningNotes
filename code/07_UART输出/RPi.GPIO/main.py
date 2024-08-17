#!/usr/bin/python
# -*- coding:utf-8 -*-
import serial
import time

ser = serial.Serial("/dev/ttyS0",115200)

if not ser.isOpen():
    print("open failed")
else:
    print("open success: ")
    print(ser)

try:
    while True:
        count = ser.inWaiting()
        if count > 0:
            recv = ser.read(count)
            print(recv)
            ser.write(recv)
        time.sleep(0.05) 
except KeyboardInterrupt:
    if ser != None:
        ser.close()
