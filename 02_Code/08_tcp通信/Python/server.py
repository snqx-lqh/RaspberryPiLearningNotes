"""
Socket 服务器 代码示例
"""
import socket

#创建socket实例对象
socket_server = socket.socket()

#为实例对象 绑定服务端的 IP 地址和端口号
socket_server.bind(("192.168.3.18", 8888))

#设置监听的最大连接数
socket_server.listen(100)

while True:
    #阻塞等待连接 , 函数返回连接的客户端 socket 对象 和 连接的地址
    client_socket, client_address = socket_server.accept()

    #服务器端与客户端进行交互
    while True:
        # 循环接收客户端数据, 1024是最大长度，并使用 UTF-8 解码
        data = client_socket.recv(1024).decode("UTF-8")

        # 向客户端发送接收到的消息
        client_socket.send(f"server rec: {data}".encode())
        print(f"client send: {data}")

        if data == 'quit':
            break

    # 关闭连接
    client_socket.close()
    print(f'client disconnect {client_address}')