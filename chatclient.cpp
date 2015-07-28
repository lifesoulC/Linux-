#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<curses.h>
WINDOW *winfo,*wmsg;
int fd;
int r;
struct sockaddr_in dr;
int initSocket();

void initUI();
void destroy();
int main()
{
	fd = initSocket();
	if(fd == -1) exit(-1);
	printf("网络初始化成功！\n");
	initUI();
	if(fork())
	{
		//输入发送 
		char buf[256];
		while(1)
		{
		  mvwgetstr(wmsg,1,1,buf);
		  buf[r] = 0;
		  send(fd,buf,r,0);
		  wclear(wmsg);
		  box(wmsg,0,0);
		  refresh();
		  wrefresh(wmsg);			
		}

	}
	else
	{
		char buf[256];
		int line = 1;
		//接收显示 
		while(1)
		{
			r = recv(fd,buf,255,0);
			buf[r] = 0;
			mvwaddstr(winfo,line,1,buf);
			line++;
			if(line > (LINES-3))
			{
				wclear(winfo,0,0);
				line = 1;
				box(winfo,0,0); 
			}
			refresh();
			wrefresh(winfo);
		}
	}
	destroy();
}

void initUI()
{
	initscr();
	winfo = derwin(stdscr,(LINES-3),COLS,0,0);
	wmsg = derwin(stdscr,3,COLS,LINES-3);
	box(winfo,0,0);
	box(wmsg,0,0);
	refresh();
	wrefresh(winfo);
	wrefresh(wmsg);
}

int initSocket()
{
    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1) return -1;
	
	dr.sin_family = AF_INET;
	dr.sin_port = htons(9999);
	dr.sin_addr.s_addr = inet_addr("127.0.0.0");
	r = connect(fd,(struct sockaddr*)&dr,sizeof(de));
	if(r == -1)
	{
		close(fd);
		return -1;
	}
	return 0;
}

void destroy()
{
	getch();
	close(fd);
	endwin(); 
}








