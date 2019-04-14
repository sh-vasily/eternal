#pragma warning(disable:4996)

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define fInName argv[1]
#define fOutName argv[2]

#define COM 14
#define REG 26

#define R1 Reg[r1 - 'A']
#define R2 Reg[r2 - 'A']

#define M1 mentioned[r1 - 'A']
#define M2 mentioned[r2 - 'A']

char *errs[] = 
{
	"Error #1: input file with name %s not found"
	, "Error #2: output file with name %s can't be created"
	, "comment wasn't opened"
	, "comment wasn't closed"
	, "found inserted comment"
	, "command wasn't found"
	, "incorrect syntax"
	, "register redefinition"
	, "register wasn't defined"
	, "file is empty of commands"
};

const char* com[COM] =
{
	"IN", "OUT", "NOT", "AND", "OR", "NAND", "NOR", "EQV", "XOR", "IMP", "BIMP", "COIMP", "COBIMP", "COPY"
}, **cm = com;

FILE *fIn = NULL, *fOut = NULL;

unsigned short Reg[REG] = { 0 }, mentioned[REG] = { 0 };

void fileError(int, char*);
void fatalError(int);
char *invertedGorner(int, int);

int main(int argc, char *argv[])
{
	char r1 = '0', r2 = '0';
	if (!(fIn = fopen(fInName, "r"))) fileError(1, fInName);
	if (!(fOut = fopen(fOutName, "w"))) fileError(2, fOutName);
	char c, buf[10] = "", *b = buf;
	int inComment = 0, comNum = -1;
	while (!feof(fIn))
	{
		c = fgetc(fIn);
		if (c == '#') while (c != '\n' && c != EOF) c = fgetc(fIn);
		if (c == '{')
		{
			if (inComment) fatalError(3);
			inComment++;
		}
		if (c == '}')
		{
			if (!inComment) fatalError(1);
			inComment--;
		}
		if ((isalpha(c)) && !inComment) *b++ = toupper(c);
		if (c == ';' && !inComment)
		{
			*b = 0;
			b = buf;
			for (cm = com; cm - com < COM; cm++)
			if ((cm - com <= 2 && strstr(buf, *cm) == buf) || (cm - com > 2 && strstr(buf, *cm) == buf + 1)) break;
			if ((comNum = cm - com) == COM) fatalError(4);
			if (comNum >= 0 && comNum <= 2)
			{
				if (strlen(buf) != strlen(*cm) + 1) fatalError(5);
				r1 = *(buf + strlen(*cm));
			}
			else if (comNum >= 3 && comNum < COM)
			{
				if (strlen(buf) != strlen(*cm) + 2) fatalError(5);
				r1 = *buf;
				r2 = *(buf + strlen(*cm) + 1);
			}
			switch (comNum)
			{

			case 0:
				if (M1) fatalError(6);
				printf("Enter value of register %c: ", r1);
				scanf("%d", &R1);
				M1++;
				fprintf(fOut, "Read command IN %c\n", r1);
				break;
			case 1:
				if (!M1) fatalError(7);
				fprintf(fOut, "Read command OUT %c\n", r1);
				fprintf(fOut, "%c = %s(%d)", r1, invertedGorner(R1, 2), 2); 
				fprintf(fOut, " = %s(%d)", invertedGorner(R1, 8), 8);
				fprintf(fOut, " = %d(%d)", R1, 10);
				fprintf(fOut, " = %s(%d)\n", invertedGorner(R1, 16), 16);
				break;
			case 2:
				if (!M1) fatalError(7);
				R1 = ~R1;
				fprintf(fOut, "Read command NOT %c\n", r1);
				break;
			case 3:
				if (!M1 || !M2) fatalError(7);
				R1 = R1 & R2;
				fprintf(fOut, "Read command %c AND %c\n", r1, r2);
				break;
			case 4:
				if (!M1 || !M2) fatalError(7);
				R1 = R1 | R2;
				fprintf(fOut, "Read command %c OR %c\n", r1, r2);
				break;
			case 5:
				if (!M1 || !M2) fatalError(7);
				R1 = ~(R1 & R2);
				fprintf(fOut, "Read command %c NAND %c\n", r1, r2);
				break;
			case 6:
				if (!M1 || !M2) fatalError(7);
				R1 = ~(R1 | R2);
				fprintf(fOut, "Read command %c NOR %c\n", r1, r2);
				break;
			case 7:
				if (!M1 || !M2) fatalError(7);
				R1 = ~(R1 ^ R2);
				fprintf(fOut, "Read command %c EQV %c\n", r1, r2);
				break;
			case 8:
				if (!M1 || !M2) fatalError(7);
				R1 = R1 ^ R2;
				fprintf(fOut, "Read command %c XOR %c\n", r1, r2);
				break;
			case 9:
				if (!M1 || !M2) fatalError(7);
				R1 = ~R1 | R2;
				fprintf(fOut, "Read command %c IMP %c\n", r1, r2);
				break;
			case 10:
				if (!M1 || !M2) fatalError(7);
				R1 = ~(~R1 | R2);
				fprintf(fOut, "Read command %c BIMP %c\n", r1, r2);
				break;
			case 11:
				if (!M1 || !M2) fatalError(7);
				R1 = ~R2 | R1;
				fprintf(fOut, "Read command %c COIMP %c\n", r1, r2);
				break;
			case 12:
				if (!M1 || !M2) fatalError(7);
				R1 = ~(~R2 | R1);
				fprintf(fOut, "Read command %c COBIMP %c\n", r1, r2);
				break;
			case 13:
				if (!M1 || !M2) fatalError(7);
				R2 = R1;
				fprintf(fOut, "Read command %c COPY %c\n", r1, r2);
				break;
			}
		}
		if (c == EOF && inComment) fatalError(2);
	}
	if (comNum == -1) fatalError(8);
	fclose(fIn);
	fclose(fOut);
	getchar();
	return 0;
}

void fileError(int errNum, char *fileName)
{
	printf(errs[errNum - 1], fileName);
	getchar();
	exit(errNum - 1);
}

void fatalError(int errNum)
{
	printf(errs[errNum + 1]);
	fprintf(fOut, errs[errNum + 1]);
	getchar();
	exit(errNum + 1);
}

char *invertedGorner(int num, int base)
{
	int n = num;
	char res[256] = { 0 }, *r = res;
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
	return res;
}
