#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE     1024
#define SERVER_IP   "192.168.3.4"	//IP号之间不能有空格
#define SERVER_PORT 8888

void Client_recvfrom_sendto(int socketfd, struct sockaddr_in *addr)
{
	int byte = 0, cnt = 0;
	unsigned char data[BUF_SIZE];
	socklen_t len = sizeof(struct sockaddr_in);
	struct sockaddr_in serveraddr;
	
	while(1)
	{
		memset(data, 0, BUF_SIZE );
		sprintf(data, "client send data cnt:%d\n", ++cnt);
		//往服务器地址发送信息
		sendto(socketfd, data, strlen(data), 0, (struct sockaddr *)addr, sizeof(*addr));
		
		memset(data, 0, BUF_SIZE );
		//读取server数据,有数据更新才读取，否则阻塞
		byte = recvfrom(socketfd, data, BUF_SIZE, 0, (struct sockaddr *)&serveraddr, &len);
		if(byte == 0)
		{
			perror("read over");
			break;
		}
		if(byte < 0)
		{
			perror("read failed");
			break;
		}
		printf("server-->client datelen:%d info:%s\r\n",byte, data);	
 
	}	
	return;
}

int main(int argc, void *argv[] )
{
	int socketfd = -1;
	struct sockaddr_in servaddr;
	
	//1、创建套接字
	if( (socketfd = socket(AF_INET, SOCK_DGRAM, 0) ) ==  -1)	
	{
		perror("socket create failed!");
		return -1;
	}

	//2、设置要连接的服务器相关信息
	memset(&servaddr, 0, sizeof(servaddr) );
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	servaddr.sin_port = htons(SERVER_PORT);

	//3、服务端接收和发送信息
	Client_recvfrom_sendto(socketfd, &servaddr);
	return 0;	
}
