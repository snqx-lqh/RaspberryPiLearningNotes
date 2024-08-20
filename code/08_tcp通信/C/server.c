#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
			
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

 
#define  SERVER_IP   "192.168.3.18"
#define  SERVER_PORT 8888 

int main()
{
    //接收数据的Buff
	char RecBuf[1024];

	//1创建套接字
	int sockfd = socket(AF_INET,SOCK_STREAM,0);		 
	if(sockfd == -1)
	{
		perror("socket");
		return -1;	
	}
	
	//2绑定套接字
	struct sockaddr_in myaddr;                //IPV4地址结构体
	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;              
	myaddr.sin_port = htons(SERVER_PORT);           //端口号   5001~65535
	myaddr.sin_addr.s_addr = inet_addr(SERVER_IP);  //设置IP地址
	
	if (-1 == bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr))) {
		perror("bind");	
		return -1;
	}
	
	//3设置监听套接字
	if(listen(sockfd,5) == -1)
	{
		perror("listen");
		return -1;	//返回现在执行的函数(结束函数) 
	}
	
	while(1)
	{
        //4接受客户端的连接。并生成新的通信套接字
        int connfd = accept(sockfd,NULL,NULL);			//定义套接字
        if(connfd == -1)
        {
            perror("accpet!");
            return -1;	//返回现在执行的函数(结束函	
        }
        printf("accpet success!\n");
        //连接成功后，进入通信的循环
        while(1)
        {
            memset(RecBuf,0,sizeof(RecBuf));		//将 buf空间中的1024内容清空 
            int ret = read(connfd,RecBuf,sizeof(RecBuf));
            if(ret == -1)			//读取失败 
            {	
                perror("read!");
                break;
            }
            else if(ret == 0)		//写端口关闭 
            {
                printf("client close\n");
                break;
            }
            else
            {
                printf("recv : %s\n",RecBuf);
            } 
            if (0 == strncmp(RecBuf, "exit",4))	//判断是否退出
                break;
            
            //将读取到的数据又发送出来
            ret = write(connfd, RecBuf, sizeof(RecBuf));
            if (ret == -1) {
                perror("write");
                break;
            }
        }
		//关闭连接套接字 
	    close(connfd);
	}	
	close(sockfd);	
	return 0;
 } 
