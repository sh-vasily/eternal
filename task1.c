#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include<ctype.h>
 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
 
int gorner(char*, unsigned);
char * invertgorner(unsigned,unsigned );
char * cc(char * , unsigned ,unsigned);
 
 
int main(int argc, char * argv[])
{
    if (argc < 3){
                    fprintf(stderr,"please write the name files!\n");
                    exit(1);
                  }
    int  fd_in = open(argv[1],O_RDONLY);
    unsigned fd_out = open(argv[2],O_CREAT|O_RDWR,S_IRWXU|S_IROTH);
    char * buf = malloc(sizeof(char) * 256);
    char * buf2 = malloc(sizeof(char) * 256);
    char *b = buf;
    char  symb;
    int i = 0 ;
    unsigned flag = 0;
   int   num = 0;
    unsigned base_in = 0;
    unsigned base_out = 2;
    if (fd_in == -1)
{
    fprintf(stderr,"error! file with this name does not exist!\n ");
        exit(1);
}
   do
{
    read (fd_in,&symb,sizeof(char));
    if (symb =='(') flag = 1;
    else if((symb!=')' ) && (symb!= ';')) {
    if  (flag== 0) *b++ = symb;
    else base_in = base_in * 10 +  symb - '0'; }
}
    while(symb != ';');
 
 
    for(base_out ;base_out <= 16;base_out*=2)
    {
      sprintf(buf2,"%s(%u)=%s(%u)\n",buf,base_in,cc(buf,base_in,base_out),base_out);
      write(fd_out,(void *) buf2, strlen(buf2));
    if(base_out == 8)
        {
            base_out = 10;
            sprintf(buf2,"%s(%u)=%s(%u)\n",buf,base_in,cc(buf,base_in,base_out),base_out);
             write(fd_out,(void *) buf2, strlen(buf2));
            base_out = 8;
 
        }
    }
 
    close(fd_in);
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
