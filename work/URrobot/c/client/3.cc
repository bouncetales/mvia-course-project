/*client_tcp.c*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main(){
	//创建套接字
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	//服务器的ip为本地，端口号1234
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("192.168.232.129");
	serv_addr.sin_port = htons(30003);
	
	//向服务器发送连接请求
	connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	//发送并接收数据
	char buffer[40];
    // buffer=('movej([0.244,-2.25,-0.89,-3.19,0,0],a=0.1,v=0.1,t=0,r=0)\n');
	printf("Please write:");
	scanf("%s", buffer);
	write(sock, buffer, sizeof(buffer));
	read(sock, buffer, sizeof(buffer) - 1);
	printf("Serve send: %s\n", buffer);

	//断开连接
	close(sock);

	return 0;
}

