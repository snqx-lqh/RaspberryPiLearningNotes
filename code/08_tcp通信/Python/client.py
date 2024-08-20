import socket

#  创建 socket 实例对象
client_socket = socket.socket()

#  客户端连接服务器, IP 地址和端口号放在元组中
client_socket.connect(('192.168.3.4', 8888))

# 获取命令行输入发送给客户端
while True:
    command = input("请输入: ")
    client_socket.send(command.encode())
    print(f"客户端发送: {command}")
    if command == 'quit':
        break

    # 接收服务器数据
    data = client_socket.recv(1024).decode("UTF-8")
    print(f"服务端: {data}")

#关闭连接
client_socket.close()
print("客户端关闭")

