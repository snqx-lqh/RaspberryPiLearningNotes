#!/usr/bin/python3
# -*- coding: utf-8 -*-
import socket
 
def main():
    # udp 通信地址，服务器的IP+端口号
    udp_addr = ('192.168.3.18', 8888)
    # 创建socket实例 SOCK_DGRAM代表是UDP
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # 绑定端口
    udp_socket.bind(udp_addr)
    i = 0
    # 等待接收对方发送的数据
    while True:
        i = i + 1
        # 1024表示本次接收的最大字节数 recv_data 是接收到的数据 ip_port是这串数据的发送方IP和端口
        recv_data,ip_port = udp_socket.recvfrom(1024)  
        # 打印接收到的数据
        print("[From %s:%d]:%s" % (ip_port[0], ip_port[1], recv_data.decode("utf-8")))
        # 往发送方 ip_port 发送
        udp_socket.sendto(("Hello,I am a UDP socket for: " + str(i)) .encode('utf-8'),ip_port)
        print("send %d message" % i)
 
if __name__ == '__main__':
    print("udp server ")
    main()
 