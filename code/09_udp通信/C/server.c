#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define  SERVER_IP   "192.168.3.18"
#define  SERVER_PORT 8888 

#define BUF_SIZE 1024

void Server_recvform_sendto(int fd)
{
	int byte = 0, cnt = 0;
	char buf[BUF_SIZE] = {0};
	socklen_t len = sizeof(struct sockaddr_in);
	struct sockaddr_in clientaddr;
	
	if(fd <= 0) 
	{
		perror("socket fd value err");
		return ;
	}
	
	while(1)
	{
		memset(buf, 0, BUF_SIZE );
        //读取client数据,有数据更新才读取，否则阻塞 clientaddr会把客户端连接时候的地址端口信息保存
		byte = recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr *)&clientaddr, &len);	
        //客户端关闭时，读取数据个数为0
		if(byte == 0)							
		{
			printf("sockfd:%d read over\n", fd);
			break;
		}
		if(byte < 0)
		{
			perror("read failed");	
			break;
		}
		printf("client IP:%s, port:%d, datalen:%d, info:%s\n", inet_ntoa(clientaddr.sin_addr), clientaddr.sin_port, byte, buf );
		
		memset(buf, 0, BUF_SIZE );
		sprintf(buf, "server send cnt:%d\n", ++cnt);
        //往刚刚连接到自己的client发送信息
		sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
	}
	close(fd);
}

int main(int argc, void *argv[] )
{
	int listenfd;
	struct sockaddr_in serveraddr; //服务端IP地址信息
	
    //1、创建套接字
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(listenfd < 0)
	{
		perror("Create socket fail.");
		return -1;
	}	

	//2、绑定套接字
    memset( (void*)&serveraddr,0,sizeof(struct sockaddr_in) );
    serveraddr.sin_family 		= AF_INET;
	serveraddr.sin_port			= htons(SERVER_PORT);
	serveraddr.sin_addr.s_addr 	= inet_addr(SERVER_IP);
	
	if(bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in))<0)	//绑定
	{
		perror("bind error.");
		return -1;
	}
	//3、服务器接收和发送数据
	Server_recvform_sendto(listenfd);
	
	return 0;
}
