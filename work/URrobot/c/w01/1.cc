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
	int i;
	int k;
	//创建套接字
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	int sock1 = socket(AF_INET, SOCK_STREAM, 0);
	int sock2 = socket(AF_INET, SOCK_STREAM, 0);
	int sock3 = socket(AF_INET, SOCK_STREAM, 0);
	//服务器的ip为本地，端口号1234
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("192.168.232.129");
	serv_addr.sin_port = htons(30003);

	//向服务器发送连接请求
	connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	connect(sock1, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    connect(sock2, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    connect(sock3, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	//发送并接收数据
	char movel[1024]="movel(p[0, -0.27, 0.13, 3.14165, 0., 0.])\n";
	char movel1[1024]="movel(p[0, -0.47, 0.13, 3.14165, 0., 0.])\n";
	char movel2[1024]="movel(p[0, -0.47, 0.13, 3.14165, 0., 0.])\n";
	char movel3[1024]="movel(p[0, -0.47, 0.13, 3.14165, 0., 0.])\n";

	send(sock, movel, sizeof(movel),0);
	sleep(2);
	send(sock1, movel1, sizeof(movel1),0);
	//read(sock, buffer, sizeof(buffer) - 1);
	//printf("Serve send: %s\n", buffer,buffer1);

	//断开连接
	close(sock);

	return 0;
}


