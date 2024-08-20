import socket
 
def main():
    # udp 通信地址，服务器的IP+端口号
    udp_addr = ('192.168.3.4', 8888)
    # 创建socket实例 SOCK_DGRAM代表是UDP
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
 
    # 发送数据到指定的ip和端口
    for i in range(10):
        udp_socket.sendto(("Hello,I am a UDP socket for: " + str(i)) .encode('utf-8'), udp_addr)
        print("send %d message" % i)
        # 1024表示本次接收的最大字节数 recv_data 是接收到的数据 ip_port是这串数据的发送方IP和端口
        recv_data, ip_port = udp_socket.recvfrom(1024)   
        print(recv_data,ip_port)
    # 5. 关闭套接字
    udp_socket.close()
 
if __name__ == '__main__':
    print("udp client ")
    main()