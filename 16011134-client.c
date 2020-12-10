#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAXLINE 1024

int main(void)
{
  int rfd, wfd;    //file descriptors
  char buf[MAXLINE];  //buf
  
  if(  (rfd = open("/tmp/myfifo_w", O_RDWR) ) < 0)  //write pipe open
  {                          //if error, terminate program
    perror("read open error");
    return 0;
  }

  if(  (wfd = open("/tmp/myfifo_r", O_RDWR) ) < 0)  //read pipe open
  {                          //if error, terminate program
    perror("write open error");
    return 0;
  }
  
  while(1)
  {
    printf("> ");
    fflush(stdout);          //empty print buff
    memset(buf, 0x00, MAXLINE);    //empty buff
    if(read(0, buf, MAXLINE) < 0)  //if none read from keyboard, terminate program
    {
      printf("error\n");
      return 1;
    }
    if(strncmp(buf, "quit\n", 5) == 0)  //if input "quit" terminate program
      break;

    write(wfd, buf, strlen(buf));      //write at write pipe
  }

  close(wfd);          //close write pipe
  close(rfd);          //close read pipe
  return 0;
}
