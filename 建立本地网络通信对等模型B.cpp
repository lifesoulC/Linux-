#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<linux/un.h>
#include<string.h>
#include<unistd.h>
int main()
{
	int fd;
	struct sockaddr_un addr{0};
	}; 
	//建立socket 
	fd = socket(AF_UNIX,SOCK_DGRAM,0);
	//链接到指定的地址
	addr.sun_family = AF_UNIX;
	memcpy(addr.sun_fath,"my.sock",strlen("my.sock"));
	r = connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	//发送数据
	write(fd,"hello! maomaochong",
	strlen("hello!maomaochong"))； 
	
	
	//关闭 
	close(fd); 
} 
