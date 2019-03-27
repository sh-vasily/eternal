#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
 
int main (int argc, char * argv[])
{
int fd = open(argv[1],O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
 dup2(fd,1);
 close(fd);
 int pipefd[2];
 pipe(pipefd);
if (fork() == 0)
{
  close (pipefd[0]);
 
  dup2(pipefd[1], 1);
  dup2(pipefd[1],2);
 
  close(pipefd[1]);
 printf("My pid = %d\n", getpid());
 printf("Parents pid = %d\n", getppid());  
 execl("/bin/ps","ps","-aux",NULL);
 }
 
else
{
  char buffer[1024];
 
  close(pipefd[1]);
  while(read(pipefd[0],buffer,sizeof(buffer)) != 0)
      printf("%s\n",buffer);
}
 
  return 0;
}
