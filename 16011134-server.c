#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAXLINE 1024

int main(void)
{
  int rfd, wfd, num = 0;    //file descriptors
  char buf[MAXLINE];  //buf
  
  mkfifo("/tmp/myfifo_r", S_IRUSR|S_IWUSR);    //write pipe open
  mkfifo("/tmp/myfifo_w", S_IRUSR|S_IWUSR);    //read pipe open
  //if error at opening read pipe, terminate program
  if((rfd = open("/tmp/myfifo_r", O_RDWR) ) == -1) 
  {
    perror("rfd error");
    return 0;
  }
  //if error at opening write pipe, terminate program
  if(  (wfd = open("/tmp/myfifo_w", O_RDWR) ) == -1) 
  {
    perror("wfd error");
    return 0;
  }
  
  while(1)
  {
    memset(buf, 0x00, MAXLINE);          //empty R/W buff
    //if error at reading from pipe, terminate program 
    if(  read(rfd, buf, MAXLINE)  < 0)     
    {
      perror("Read Error::");
      return 1;
    }
    num = atoi(buf);
    printf("%d+%d = %d\n", num, 1, num+1);
    lseek(wfd, 0, SEEK_SET);          //cursor at beginning of buff
    write(wfd, buf, MAXLINE);          //echo what read from buff
  }
  return 0;
  
}
