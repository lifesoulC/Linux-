#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<socke.h>
#include <unistd.h> 
#include<linux/un.h> 
/*int socket(
        int domain,//��ַ������ͣ�AF_UNIX������ AF_INET�����ַ�壬PFЭ����           
		int type,//֧�ֵ����ݸ�ʽ�� ��/����
		          SOCK_STREAM:�� SOCK_DGRAM���� 
		int protocol)��//֧�ֵ�Э�飬����Ϊ0��
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
	
	//����socket
	fd = socket(AF_UNIX,SOCK_DGRAM,0); 
	if(fd == -1) printf("socket err:%m\n"),exit(-1);
	//���챾���ļ���ַ 
	struct sockaddr_un addr = {0};
	addr.sun_family = AF_UNIX; 
	memcpy(addr.sun_path,"mysok",strlen("my.sock"));
	//��socket���ڵ�ַ��
	/*int bind(int fd,//socket ������ 
	      struct sockaddr*addr, �󶨵�ַ 
		  size_t size); ��ַ���� 
	*/ 
	r = bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(r == -1) printf("bind err") ,exit(-1);
	
	//��������
	bzero(buf,sizeof(buf)); 
	r = read(fd,buf,sizeof(buf));
	buf[r] = 0;
	printf("%s\n",buf);
	
	//�ر�
	close(fd);
	//ɾ��socket 
	unlink("my.sock");
	
	
	
	
	
	
}
 
