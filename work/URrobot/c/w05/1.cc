/*client_tcp.c*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<time.h>
int main()
{

	//创建套接字
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	//printf("dd");
	//服务器的ip为本地，端口号1234
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("192.168.232.129");
	serv_addr.sin_port = htons(30003);

	//向服务器发送连接请求
	connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	//发送并接收数据
	char buffer[1024];
	char buffer1[1024];

	//movel([0, -0.47, 0.13, 3.14165, 0., 0.]);
	//time.sleep(3);
	// movel([0, -0.27, 0.13, 3.14165, 0., 0.]);
	sprintf(buffer,"movel(p[0, -0.47, 0.13, 3.14165, 0., 0.])\n",sleep(2),"movel(p[0, -0.27, 0.13, 3.14165, 0., 0.])\n");
	// sleep(10000);
	// sprintf(buffer,"movel(p[0, -0.27, 0.13, 3.14165, 0., 0.])\n");

	write(sock, buffer, sizeof(buffer));
	//write(sock, buffer1, sizeof(buffer1));
	//read(sock, buffer, sizeof(buffer) - 1);
	//printf("Serve send: %s\n", buffer,buffer1);

	//断开连接
	close(sock);

	return 0;
}

