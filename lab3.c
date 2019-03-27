
#pragma warning(disable : 4996)
 
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
 
#define SIZE 100
#define ISOP(x) (x == '(' || x == '+' || x == '-' || x == '*' || x == '/' || x == ')')
 
const char *errs[] =
{
    "File names not defined in command line!"
    , "Input file not exists!"
    , "Output file can't be created!"
    , "Dividing by zero!"
    , "Incorrect placement of brackets!"
};
 
void error(int);
int gorner(char *);
int priority(char);
 
int main(int argc, char *argv[])
{
    FILE *fIn = NULL;
    if (!(fIn = fopen(argv[1], "r"))) error(2);
    char c, c_ = ' ', buf[SIZE] = { 0 }, *b = buf, operStack[SIZE] = { 0 }, *o = operStack;
    int numStack[SIZE] = { 0 }, *n = numStack;
    *o++ = '(';
    while (!feof(fIn))
    {
        c = fgetc(fIn);
        if (isdigit(c)) *b++ = c;
        else if (isdigit(c_))
        {
            *b = 0;
            b = buf;
            *n++ = gorner(buf);
        }
        if (ISOP(c))
        {
            if (c == '(') *o++ = c;
            else if (c == ')')
            {
                while (priority(*--o))
                {
                    int num2 = *--n;
                    int num1 = *--n;
                    switch (*o)
                    {
                    case '+': num1 += num2; break;
                    case '-': num1 -= num2; break;
                    case '*': num1 *= num2; break;
                    case '/':
                        if (!num2) error(4);
                        num1 /= num2;
                        break;
                    }
                    *n++ = num1;
                }
                o--;
            }
            else while (priority(c) <= priority(*(o - 1)) && priority(*(o - 1)))
            {
                int num2 = *--n;
                int num1 = *--n;
                switch (*--o)
                {
                case '+': num1 += num2; break;
                case '-': num1 -= num2; break;
                case '*': num1 *= num2; break;
                case '/':
                    if (!num2) error(4);
                    num1 /= num2;
                    break;
                }
                *n++ = num1;
            }
            if (c != '(' && c != ')') *o++ = c;
        }
        else if (c == ';')
        {
            while (o != operStack + 1)
            {
                int num2 = *--n;
                int num1 = *--n;
                switch (*--o)
                {
                case '+': num1 += num2; break;
                case '-': num1 -= num2; break;
                case '*': num1 *= num2; break;
                case '/':
                    if (!num2) error(4);
                    num1 /= num2;
                    break;
                }
                *n++ = num1;
            }
            printf("= %d\n", *--n);
            n = numStack;
            o = operStack;
            *o++ = '(';
        }
        c_ = c;
    }
    fclose(fIn);
    getchar();
    return 0;
}
 
void error(int errNum)
{
    printf("%s\nPress any key to exit...", errs[errNum - 1]);
    getchar();
    exit(errNum - 1);
}
 
int gorner(char *num)
{
    int res = 0;
    while (*num) res = res * 10 + *num++ - '0' ;
    return res;
}
 
int priority(char c)
{
    switch (c)
    {
    case '(': return 0; break;
    case '+': return 1; break;
    case '-': return 1; break;
    case '*': return 2; break;
    case '/': return 2; break;
    }
}
