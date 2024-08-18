## TCP通信

这篇文章，将介绍如何在树莓派中使用Socket套接字进行TCP通信，按道理，这个应该只要是Linux系统，都支持实现。

### 服务端实现流程

* 创建套接字 

* 绑定套接字 

* 设置监听套接字 

* 接收客户端的连接 

* 收数据 

## C语言实现

### 服务端

1、创建套接字

```c
int sockfd = socket(AF_INET,SOCK_STREAM,0);	
```

- `socket()` 函数用于创建一个新的套接字描述符（socket descriptor），该描述符用于在后续的套接字操作中唯一标识该套接字。
- `AF_INET` 指定地址族为IPv4。这意味着套接字将使用IPv4地址。
- `SOCK_STREAM` 指定套接字类型为流式套接字（TCP套接字）。这意味着该套接字将使用TCP协议进行通信，提供面向连接的、可靠的数据传输服务。
- 第三个参数`0`对于`AF_INET`和`SOCK_STREAM`来说通常可以设置为0，因为它指定了特定的协议，但在这种情况下，TCP是默认的协议，所以0是合适的。

2、绑定套接字

```c
struct sockaddr_in myaddr;                //IPV4地址结构体
memset(&myaddr, 0, sizeof(myaddr));
myaddr.sin_family = AF_INET;              
myaddr.sin_port = htons(8888);           //端口号   5001~65535
myaddr.sin_addr.s_addr = inet_addr("192.168.1.10");  //设置IP地址

if (-1 == bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr))) {
    perror("bind");	
    return -1;
}
```

* 这里，`sockaddr_in`结构体用于存储IPv4地址和端口号。使用`memset`函数是为了确保结构体中的所有未明确设置的字段都被初始化为0，这是一种良好的编程习惯，可以防止潜在的未定义行为。

* `sin_family`字段设置为`AF_INET`，表明这是一个IPv4地址。`sin_port`字段设置为8888，但需要注意的是，端口号是通过`htons()`函数转换的，这是为了确保端口号以网络字节序（大端序）存储，这在网络传输中是必需的。
* `inet_addr()`函数将点分十进制的IP地址字符串（"192.168.1.10"）转换为网络字节序的整数，并存储在`sin_addr.s_addr`中。
* 使用`bind()`函数将套接字`sockfd`绑定到前面设置的IP地址和端口上。`bind()`函数的第一个参数是套接字描述符，第二个参数是指向`sockaddr`结构体的指针（这里通过强制类型转换`(struct sockaddr*)&myaddr`实现），该结构体包含了要绑定的地址信息，第三个参数是该结构体的大小。如果`bind()`调用失败，将打印错误信息并返回-1。

3、设置监听

```c
listen(sockfd,5)
```

* `listen(sockfd, 5)`：这个函数尝试将`sockfd`套接字设置为监听状态，并指定最多可以有5个未处理的连接请求在队列中等待。

4、接收客户端的连接，并生成新的套接字。

```c
int connfd = accept(sockfd, NULL, NULL);
```

* 调用 `accept()` 函数：这个函数用于从服务器监听的套接字（`sockfd`）上接受一个连接请求。如果成功，它将返回一个新的套接字描述符（`connfd`），这个新的描述符用于与接受到的客户端进行通信。如果失败，它将返回-1，并设置全局变量 `errno` 以指示错误的原因。

5、接收数据

```c
int ret = read(connfd,buf,sizeof(buf));
```

* 您使用 `read` 函数从套接字 `connfd` 读取数据到 `buf` 中。这里需要注意的是，`read` 函数并不保证会读取您请求的字节数，特别是当对方发送的数据量小于您请求的量时。此外，`read` 函数也不会在字符串的末尾添加空字符（`\0`），因此，在将 `buf` 作为字符串打印之前，您需要确保它是正确终止的。

6、发送数据

```c
ret = write(connfd, buf, sizeof(buf));
```

* 将数据发送出去

