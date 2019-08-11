/*************************************************************************
	> File Name: poll.c
	> Author: 
	> Mail: 
	> Created Time: 2019年08月11日 星期日 22时23分54秒
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>

int main()
{
    int i =0 ;
    int fd=open("/sys/class/gpio/gpio7/value",O_RDONLY);
    if(fd<0)
    {
        perror("open '/sys/class/gpio/gpio7/value' failed!\n");  
        return -1;
    }
    struct pollfd fds[1];
    fds[0].fd=fd;
    fds[0].events=POLLPRI;
    while(1)
    {
      for(i = 0;i<=7;i++)
       {
        if(poll(fds,1,0)==-1)
        {
            perror("poll failed!\n");
            return -1;
        }
        if(fds[0].revents&POLLPRI)
        {
            if(lseek(fd,0,SEEK_SET)==-1)
            {
                perror("lseek failed!\n");
                return -1;
            }
            char buffer[16];
            int len;
            if((len=read(fd,buffer,sizeof(buffer)))==-1)
            {
                perror("read failed!\n");
                return -1;
            }
            buffer[len]=0;
            printf("%c",buffer);
        }
       }
        printf("\n");
        i = 0;
    }
    return 0;
}
