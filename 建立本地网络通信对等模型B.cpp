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
	//����socket 
	fd = socket(AF_UNIX,SOCK_DGRAM,0);
	//���ӵ�ָ���ĵ�ַ
	addr.sun_family = AF_UNIX;
	memcpy(addr.sun_fath,"my.sock",strlen("my.sock"));
	r = connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	//��������
	write(fd,"hello! maomaochong",
	strlen("hello!maomaochong"))�� 
	
	
	//�ر� 
	close(fd); 
} 
