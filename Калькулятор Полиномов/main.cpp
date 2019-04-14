#include "cScherbakovPolynom.h"
#include <fstream>

using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;

#define IS_OPERATION(c) (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')

int main()
{
	char oper = '~';
	cScherbakovPolynom p1, p2, res;
	ifstream fIn("in.txt");
	if (!fIn.is_open()) exit(1);
	ofstream fOut("out.txt");
	if (!fOut.is_open()) exit(2);
	char c;
	while (1)
	{
		fIn >> c;
		if (fIn.eof()) break;
		if IS_OPERATION(c)
		{
			if (c == '-' && !p1.getFirst()) oper = '~';
			else oper = c;
		}
		else if (c == '<')
		{
			if (oper == '~') fIn >> p1;
			else fIn >> p2;
		}
		else if (c == ';')
		{
			switch (oper)
			{
			case '+': res = p1 + p2; break;
			case '-': res = p1 - p2; break;
			case '*': res = p1 * p2; break;
			case '/': res = p1 / p2; break;
			case '%': res = p1 % p2; break;
			}
			if (oper == '~') fOut << '-' << p1 << " = " << -p1 << endl;
			else fOut << p1 << ' ' << oper << ' ' << p2 << " = " << res << endl;
			p1 = cScherbakovPolynom();
			oper = '~';
		}
	}
	cout << -p1;
	fIn.close();
	fOut.close();
	

	
	system("pause");
	return 0;
}
