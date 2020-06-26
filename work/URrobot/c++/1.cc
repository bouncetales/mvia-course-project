#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<iostream>
#include <string.h>
#include <opencv2/opencv.hpp>
#include<time.h>
#include<unistd.h>
#include <fcntl.h>
#include <fstream>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
using namespace std;
using namespace cv;
#define ESC 27
typedef unsigned char BYTE;
 #define DWORD unsigned long
typedef BYTE * PBYTE;
double GetDouble(PBYTE pData);
DWORD GetDword(PBYTE pData);
bool RecvAll(int &sock, char*buffer, int size);
vector<Point> datatovector(string data,vector<Point>points);
int line(double m_dCurPos[]); 
double x,y,z,u,v,w;
char cmd1[1024];
char triangle3[100];
char triangle2[100];
char triangle1[100];

char rectangle4[100];
char rectangle3[100];
char rectangle2[100];
char rectangle1[100];

char circle2[100];
char circle1[100];

int rs=1;//recieve flag
int Line=0;
int triangle=3;
int Rectangle=4;
int Circle=2;
    int socket_fd = socket(AF_INET, SOCK_STREAM,0);
int main()
{
	vector<Point> contours1;//data to contours1
contours1=datatovector("robot.txt",contours1);//data to vector
    int socket_fd = socket(AF_INET, SOCK_STREAM,0);
//int flags = fcntl(socket_fd, F_GETFL, 0); 
//fcntl(socket_fd, F_SETFL, flags & ~O_NONBLOCK);
	int nLen =1060;//recieve data length
	char* accept_buf = new char[nLen];
	memset(accept_buf, 0, nLen);
    if(socket_fd == -1)
    {
        cout<<"socket 创建失败："<<endl;
        exit(-1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(30003);
    addr.sin_addr.s_addr = inet_addr("192.168.232.129");
    inet_pton(AF_INET, "192.168.232.129", &addr.sin_addr);
    int res = connect(socket_fd,(struct sockaddr*)&addr,sizeof(addr));
    if(res == -1)
    {
        cout<<"链接失败："<<endl;
        exit(-1);
    }
    cout<<"链接成功"<<endl;

	//cout<<"please input the position:";
	//cin>>x;
	//cin>>y;
	//cin>>z;
	//cin>>u;
	//cin>>v;
	//cin>>w;
//const char*  cmd1 = "movel(p[-210/1000,-246.51/1000,0.200,0.471,5.1122,0.8371])\r\n";
//sprintf(cmd1,"movej(p["
		//"%lf/1000, %lf/1000, %lf/1000, %lf, %lf, %lf"
		//"])\r\n",
		//x,y,z,u,v,w);//tcp position 
   // write(socket_fd,cmd1,strlen(cmd1));//write command

     int rec =  recv(socket_fd, accept_buf, nLen, MSG_WAITALL);//recieve data
	double ComPos[6];   //define command position
	double TCP[30]; //store TCP position 
       ComPos[0]=x/1000;   
	ComPos[1]=y/1000;
	ComPos[2]=z/1000;
	ComPos[3]=u;
	ComPos[4]=v;
	ComPos[5]=w;
		for (int i = 0; i < 6; i++)
	{
		TCP[i] = GetDouble((PBYTE)(accept_buf + 444 + i * 8));
	}

while(1){
	     int rec =  recv(socket_fd, accept_buf, nLen, MSG_WAITALL);
		sleep(0.9);//suppend the rate of recieve,assure the cocrection
	double m_dCurPos[6];  //Current Position
	DWORD dwPackLen;
	dwPackLen = GetDword((PBYTE)accept_buf);
	int n;
	double data2[30];
	double programstate[8];
	for (n = 0; n < 6; n++)
	{
		data2[n] = GetDouble((PBYTE)(accept_buf + 444 + n * 8));
	}
	for (n = 0; n < 1; n++)
	{
		programstate[0] = GetDouble((PBYTE)(accept_buf + 1052+ n * 8));
	}
	//cout<<programstate[0]<<endl;
	for (n = 0; n < 6; n++) {    //transform the TCP position 
		m_dCurPos[n] = data2[n];
		if(fabs(m_dCurPos[n])<0.001) //delete the small number 
		m_dCurPos[n]=0;
		//if(RecvAll(socket_fd, accept_buf, nLen))//if the number of data  enough and datahead corect output		
		//if(n<=2)
		//cout<<m_dCurPos[n]<<endl;
		//if(n>2)
		//cout<<0-m_dCurPos[n]<<endl;
				}
if(contours1[0].x==2&&Line==0&&programstate[0]==1){  //Paiting Line judge if it is Line and robot is moving and Line is 0 
Line++;
   sprintf(cmd1,"movep(p[""%lf, %lf, %lf, %lf, %lf, %lf""])\r\n",
	m_dCurPos[0],m_dCurPos[1],m_dCurPos[2]+0.3,m_dCurPos[3],m_dCurPos[4],m_dCurPos[5]);//tcp position 
    write(socket_fd,cmd1,strlen(cmd1));//write command

cout<<"Painting Line:"<<Line<<endl;
}

if(contours1[0].x==3&&programstate[0]==1) //Paiting Triangle
{ 
   sprintf(triangle3,"movep(p[""%lf, %lf, %lf, %lf, %lf, %lf""])\r\n",      //record the track point
		TCP[0],TCP[1]+0.2,TCP[2],TCP[3],TCP[4],TCP[5]);//tcp position 
   sprintf(triangle2,"movep(p[""%lf, %lf, %lf, %lf, %lf, %lf""])\r\n",
		TCP[0],TCP[1]+0.2,TCP[2]+0.2,TCP[3],TCP[4],TCP[5]);//tcp position 
   sprintf(triangle1,"movep(p[""%lf, %lf, %lf, %lf, %lf, %lf""])\r\n",
		TCP[0],TCP[1],TCP[2],TCP[3],TCP[4],TCP[5]);//tcp position
if(triangle==3){
    write(socket_fd,triangle3,strlen(triangle3));//write command
	triangle--;
	cout<<triangle3<<endl;		
		}
else if(fabs(m_dCurPos[1]-TCP[1]-0.2)<0.003&&programstate[0]==1&&triangle==2)
	{
    write(socket_fd,triangle2,strlen(triangle2));//write command
	triangle--;
	cout<<triangle2<<endl;
	}
else if(fabs(m_dCurPos[1]-TCP[1]-0.2)<0.003&&fabs(m_dCurPos[2]-TCP[2]-0.2)<0.003&&programstate[0]==1&&triangle==1)
	{
    write(socket_fd,triangle1,strlen(triangle1));//write command
	triangle--;
	cout<<triangle1<<endl;
	}	
}//painting triangle over

if(contours1[0].x==4&&programstate[0]==1) //Paiting rectangle
{
   sprintf(rectangle4,"movep(p[""%lf, %lf, %lf, %lf, %lf, %lf""])\r\n",      //record the track point
		TCP[0],TCP[1]+0.2,TCP[2],TCP[3],TCP[4],TCP[5]);//tcp position 
   sprintf(rectangle3,"movep(p[""%lf, %lf, %lf, %lf, %lf, %lf""])\r\n",
		TCP[0],TCP[1]+0.2,TCP[2]+0.2,TCP[3],TCP[4],TCP[5]);//tcp position 
   sprintf(rectangle2,"movep(p[""%lf, %lf, %lf, %lf, %lf, %lf""])\r\n",
		TCP[0],TCP[1],TCP[2]+0.2,TCP[3],TCP[4],TCP[5]);//tcp position
   sprintf(rectangle1,"movep(p[""%lf, %lf, %lf, %lf, %lf, %lf""])\r\n",
		TCP[0],TCP[1],TCP[2],TCP[3],TCP[4],TCP[5]);//tcp position
if(Rectangle==4){
    write(socket_fd,rectangle4,strlen(rectangle4));//write command
	
	Rectangle--;
	cout<<rectangle4<<endl;	
		}
else if(fabs(m_dCurPos[1]-TCP[1]-0.2)<0.003 && programstate[0]==1 && Rectangle==3)
      {
write(socket_fd,rectangle3,strlen(rectangle3));//write command
	Rectangle--;
	cout<<rectangle3<<endl;
     }
else if( fabs(m_dCurPos[2]-TCP[2]-0.2)<0.003 && fabs(m_dCurPos[1]-TCP[1]-0.2)<0.003 && programstate[0]==1 && Rectangle==2)
     {    write(socket_fd,rectangle2,strlen(rectangle2));//write command
	Rectangle--;
	cout<<rectangle2<<endl;
     }
else if(fabs(m_dCurPos[2]-TCP[2]-0.2)<0.003 && fabs(m_dCurPos[1]-TCP[1])<0.003 && programstate[0]==1 && Rectangle==1)
     {    write(socket_fd,rectangle1,strlen(rectangle1));//write command
	Rectangle--;
	cout<<rectangle1<<endl;
	
     }

}//painting rectangle over
if(contours1[0].x==5&&programstate[0]==1) //Paiting circle
{
if(Circle==2){
	Circle--;
   sprintf(circle2,"movec(p[""%lf, %lf, %lf, %lf, %lf, %lf""],p[""%lf, %lf, %lf, %lf, %lf, %lf""])\r\n",TCP[0],TCP[1]+0.2,TCP[2],TCP[3],TCP[4],TCP[5],TCP[0],TCP[1]+0.2,TCP[2]+0.2,TCP[3],TCP[4],TCP[5]);//tcp position 
 write(socket_fd,circle2,strlen(circle2));//write command
	cout<<circle2<<endl;
}

if(fabs(m_dCurPos[2]-TCP[2]-0.2)<0.003 && fabs(m_dCurPos[1]-TCP[1]-0.2)<0.003&&Circle==1){
	Circle--;
   sprintf(circle1,"movec(p[""%lf, %lf, %lf, %lf, %lf, %lf""],p[""%lf, %lf, %lf, %lf, %lf, %lf""])\r\n",TCP[0],TCP[1],TCP[2]+0.2,TCP[3],TCP[4],TCP[5],TCP[0],TCP[1],TCP[2],TCP[3],TCP[4],TCP[5]);//tcp position 
 write(socket_fd,circle1,strlen(circle1));//write command
	cout<<circle1<<endl;
}

}

memset(accept_buf, 0, nLen);
}
cout<<"end"<<endl;
    close(socket_fd);

    return 0;
}



double GetDouble(PBYTE pData)
{
	double t;
	PBYTE p = (PBYTE)&t;
	int i;
	for (i = 0; i < 8; i++)
	{
		p[i] = pData[7 - i];
	}
	return t;
}

DWORD GetDword(PBYTE pData)
{
	DWORD t;
	PBYTE p = (PBYTE)&t;
	int i;
	for (i = 0; i < 4; i++)
	{
		p[i] = pData[3 - i];
	}
	return t;
}
bool RecvAll(int &sock, char*buffer, int size)
{
    while (size>0)//剩余部分大于0
    {
        int RecvSize= recv(sock, buffer, size, 0);
        if(RecvSize==-1)
            return false;
        size = size - RecvSize;
        buffer+=RecvSize;
    }
    return true;
} 




vector<Point> datatovector(string data,vector<Point>points)
{
int i=0;
 ifstream f1;
f1.open(data);     
string str;
vector<float> tmp;
while(getline(f1, str))       
{	
	istringstream input(str);    
	float a;
	while(input >> a)
		tmp.push_back(a);
	i++;
}

for(int j=0,k=1,l=0;j<tmp.size();j+=2,k+=2){
points.push_back(Point(tmp[j],tmp[k]));
}
return points;
 }


