#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
 
int gorner(char*, unsigned);
char * invertgorner(unsigned,unsigned );
char * cc(char * , unsigned ,unsigned);
 
int main(int argc, char* argv[] )
{
if (argc < 3){
                    fprintf(stderr,"please write the name files!\n");
                    exit(1);
                  }
   
int fd_in = open(argv[1],O_RDONLY);
if (fd_in == -1)
{
    fprintf(stderr,"error! file with this name does not exist!\n ");
        exit(1);
}
int fd_out = open(argv[2],O_CREAT|O_RDWR,0666);
   
char * p = (char *) mmap(0,255,PROT_READ,MAP_SHARED,fd_in , 0);
if (p == MAP_FAILED) {
    perror ("mmap");
    exit(1);   
}
close(fd_in);
ftruncate(fd_out,sizeof(char) *255 * 5 );
char * file_out =(char *) mmap(0,sizeof(char) *255,PROT_WRITE,MAP_SHARED,fd_out,0);
char * f = file_out;
 
char *num = (char *) malloc(sizeof(char) * 255);
char  *n = num;
char * buf = (char *) malloc(sizeof(char) * 255);
unsigned base_in = 0;
unsigned base_out=2;
int len = 0;
unsigned flag =0;
 
while(*p!=')')
{
        if (*p == '(') {flag = 1; p++;}
        if (flag == 0) *n++=*p++;
        else base_in = base_in*10 + *p++ -'0';
}
for(base_out ;base_out <= 16;base_out*=2)
    {
      sprintf(file_out,"%s(%u)=%s(%u); ",num,base_in,cc(num,base_in,base_out),base_out);
    sprintf(buf,"%s(%u)=%s(%u); ",num,base_in,cc(num,base_in,base_out),base_out);
    file_out+=strlen(buf);
    len+=strlen(buf)+1;
    *file_out++='\n';
    if(base_out == 8)
        {
            base_out = 10;
            sprintf(file_out,"%s(%u)=%s(%u);",num,base_in,cc(num,base_in,base_out),base_out);
            sprintf(buf,"%s(%u)=%s(%u);",num,base_in,cc(num,base_in,base_out),base_out);
        file_out+=strlen(buf);
        *file_out++='\n';
    len+=strlen(buf)+1;
 
            base_out = 8;
 
        }
}
 
ftruncate(fd_out,len);
close(fd_out); 
munmap(file_out,0x100);
munmap(p,0x100);
return 0;
}
 
int gorner(char * num , unsigned base)
{
int res = 0;
while(*num) res =isdigit(*num) ? (res * base + (*num++) - '0') : (res * base + toupper(*num++))-'A'+10;
return res;
}
 
char * invertgorner(unsigned num, unsigned base)
{
    unsigned n = num;
    char * r =  malloc (sizeof(char)* 256);
    while (n)
    {
        r++;
        n /= base;
    }
    while (num)
    {
        *--r = (((num % base) < 10) ? ((num % base) + '0') : ((num % base) - 10 + 'A'));
        num /= base;
    }
    return r;
}
 
 
char * cc(char * num, unsigned base_in, unsigned base_out)
{
    if (base_in == 10)return invertgorner(gorner(num, base_in), base_out);
    return invertgorner(gorner(num, base_in), base_out);
}
