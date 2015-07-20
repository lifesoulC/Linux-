#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<socke.h>
#include <unistd.h> 
#include<linux/un.h> 
/*int socket(
        int domain,//地址族的类型；AF_UNIX非网络 AF_INET网络地址族，PF协议族           
		int type,//支持的数据格式： 流/报文
		          SOCK_STREAM:流 SOCK_DGRAM报文 
		int protocol)；//支持的协议，建议为0；
*/
/*sockaddr_un{
         sun_family:sa_family_t;
         sun_path;
     }
*/ 
int main()
{
	int fd;
	buf[100];
	int r;
	
	//建立socket
	fd = socket(AF_UNIX,SOCK_DGRAM,0); 
	if(fd == -1) printf("socket err:%m\n"),exit(-1);
	//构造本地文件地址 
	struct sockaddr_un addr = {0};
	addr.sun_family = AF_UNIX; 
	memcpy(addr.sun_path,"mysok",strlen("my.sock"));
	//把socket绑定在地址上
	/*int bind(int fd,//socket 描述符 
	      struct sockaddr*addr, 绑定地址 
		  size_t size); 地址长度 
	*/ 
	r = bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(r == -1) printf("bind err") ,exit(-1);
	
	//接收数据
	bzero(buf,sizeof(buf)); 
	r = read(fd,buf,sizeof(buf));
	buf[r] = 0;
	printf("%s\n",buf);
	
	//关闭
	close(fd);
	//删除socket 
	unlink("my.sock");
	
	
	
	
	
	
}
 
