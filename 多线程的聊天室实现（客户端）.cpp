#include<time.h>  
#include<stdio.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<string.h>  
  
#define LISTENQ 5  
#define MAXLINE 512  
#define MAXMEM 10  
#define NAMELEN 20  
  
int listenfd,connfd[MAXMEM];//�ֱ��¼�������˵��׽��������ӵĶ���ͻ��˵��׽���  
  
void quit();//�������رպ���  
void rcv_snd(int n);//���������ղ�ת����Ϣ����  
  
int main()  
{  
    pthread_t thread;  
    struct sockaddr_in servaddr,cliaddr;  
    socklen_t len;  
    time_t ticks;  
    char buff[MAXLINE];  
  
//����socket���������������˵��׽���  
    printf("Socket...\n");  
    listenfd=socket(AF_INET,SOCK_STREAM,0);  
    if(listenfd<0)  
    {  
        printf("Socket created failed.\n");  
        return -1;  
    }  
  
//����bind����ʹ�÷������˵��׽������ַʵ�ְ�  
    printf("Bind...\n");  
    servaddr.sin_family=AF_INET;  
    servaddr.sin_port=htons(6666);  
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);  
    if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)  
    {  
        printf("Bind failed.\n");  
        return -1;  
    }  
  
//����listen��������һ�����������׽��ֱ�Ϊ�����������׽���  
//�ڴ˹��������tcp��������������  
    printf("listening...\n");  
    listen(listenfd,LISTENQ);  
  
//����һ���̣߳��Է�����������й����رգ�  
    pthread_create(&thread,NULL,(void*)(&quit),NULL);  
  
//��¼���еĿͻ��˵��׽�����������-1Ϊ���У�  
    int i=0;  
    for(i=0;i<MAXMEM;i++)  
    {  
        connfd[i]=-1;  
    }  
  
    while(1)  
    {  
        len=sizeof(cliaddr);  
        for(i=0;i<MAXMEM;i++)  
        {  
            if(connfd[i]==-1)  
            {  
                break;  
            }  
        }  
  
//����accept��listen���ܵ����Ӷ�����ȡ��һ������  
        connfd[i]=accept(listenfd,(struct sockaddr*)&cliaddr,&len);  
  
        ticks=time(NULL);  
        sprintf(buff,"% .24s \r \n",ctime(&ticks));  
        printf("%s Connect from: %s,port %d\n\n",buff,inet_ntoa(cliaddr.sin_addr.s_addr),ntohs(cliaddr.sin_port));  
  
//��Ե�ǰ�׽��ִ���һ���̣߳��Ե�ǰ�׽��ֵ���Ϣ���д���  
        pthread_create(malloc(sizeof(pthread_t)),NULL,(void*)(&rcv_snd),(void*)i);  
  
    }  
    return 0;  
}  
  
void quit()  
{  
    char msg[10];  
    while(1)  
    {  
        scanf("%s",msg);  
        if(strcmp("quit",msg)==0)  
        {  
            printf("Byebye...\n");  
            close(listenfd);  
            exit(0);  
        }  
    }  
}  
  
void rcv_snd(int n)  
{  
    char* ask="Your name please��";  
    char buff[MAXLINE];  
    char buff1[MAXLINE];  
    char buff2[MAXLINE];  
    char name[NAMELEN];  
    time_t ticks;  
    int i=0;  
    int retval;  
  
//��ȡ�˽��̶�Ӧ���׽����û�������  
    write(connfd[n],ask,strlen(ask));  
    int len;  
    len=read(connfd[n],name,NAMELEN);  
     if(len>0)  
     {  
         name[len]=0;  
     }  
  
//�ѵ�ǰ�û��ļ����֪�����û�  
    strcpy(buff,name);  
    strcat(buff,"\tjoin in\0");  
    for(i=0;i<MAXMEM;i++)  
    {  
        if(connfd[i]!=-1)  
        {  
            write(connfd[i],buff,strlen(buff));  
        }  
    }  
  
//���ܵ�ǰ�û�����Ϣ������ת�������е��û�  
    while(1)  
    {  
        if((len=read(connfd[n],buff1,MAXLINE))>0)  
        {  
            buff1[len]=0;  
  
//����ǰ�û���������ϢΪ��bye��ʱ����ǰ�û��˳�  
             if(strcmp("bye",buff)==0)  
             {  
                 close(connfd[n]);  
                 connfd[n]=-1;  
                 pthread_exit(&retval);  
             }  
  
             ticks=time(NULL);  
             sprintf(buff2,"%.24s\r\n",ctime(&ticks));  
             write(connfd,buff2,strlen(buff2));  
  
             strcpy(buff,name);  
             strcat(buff,"\t");  
             strcat(buff,buff2);  
             strcat(buff,buff1);  
  
            for(i=0;i<MAXMEM;i++)  
            {  
                 if(connfd[i]!=-1)  
                 {  
                      write(connfd[i],buff,strlen(buff));  
                 }  
            }  
        }  
  
    }  
}  
