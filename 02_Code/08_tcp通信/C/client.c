#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
			
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define  SERVER_IP   "192.168.3.4"  //要连接的服务器IP
#define  SERVER_PORT 8888            //要连接的服务器IP端口

int main()
{
	//1.创建套接字
	int sockfd = socket(AF_INET,SOCK_STREAM,0);		
	if(sockfd == -1)
	{
		perror("socket");
		return -1;	//返回现在执行的函数(结束函数) 
	}
	
	//2. 连接服务器
	struct sockaddr_in srvaddr;                //IPV4地址结构体
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;              
	srvaddr.sin_port = htons(SERVER_PORT);           //端口号   5001~65535
	srvaddr.sin_addr.s_addr = inet_addr(SERVER_IP);  //链接服务器的IP地址
	
	if (-1 == connect(sockfd, (struct sockaddr*)&srvaddr, sizeof(srvaddr))) {
		perror("connect");
		return -1;
	}
	
	//3.收发数据
	char buf[1024];
	int  ret;
	while (1) {
		ret = read(sockfd, buf, sizeof(buf));
		if (ret == -1) {
			perror("read");
			break;
		}else if (0 == ret) {
			printf("server close!\n");
			break;
		}
		printf("recv: %s\n", buf);
		if (strncmp(buf,"exit",4) == 0)
			break;
        ret = write(sockfd, buf, sizeof(buf));
		if (-1 == ret) {
			perror("write");
			break;
		}
	}
	
	//4.关闭套接字
	close(sockfd); 
	
	return 0;
}
