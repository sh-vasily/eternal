#include "cScherbakovMonom.h"

int fromStringToNum(char *str)
{
	char* s = str;
	int result = 0;
	while (*s)
		result = result * 10 + *s++ - '0';
	return result;
}

cScherbakovMonom::cScherbakovMonom(char* str) : iScherbakovCoeff(0), uScherbakovDegree(0)
{
	if (*str == 'x')
	{
		iScherbakovCoeff = 1;
		char* s = str + 1;
		if (!*s) uScherbakovDegree = 1;
		else if (*s == '^') uScherbakovDegree = fromStringToNum(s + 1);
	}
	else if (isdigit(*str))
	{
		char* s = str;
		while (*s && isdigit(*s)) s++;
		if (!*s) iScherbakovCoeff = fromStringToNum(str);
		else
		{
			char buf[100] = "", *b = buf, *s1 = str;
			while (s1 != s) *b++ = *s1++;
			*b = 0;
			iScherbakovCoeff = fromStringToNum(buf);
			if (!*(s + 1)) uScherbakovDegree = 1;
			else if (*(s + 1) == '^') uScherbakovDegree = fromStringToNum(s + 2);
		}
	}
	else if (*str == '+' || *str == '-')
	{
		bool flag = *str == '+';
		char *s = str + 1;
		if (*s == 'x')
		{
			iScherbakovCoeff = 1;
			s++;
			if (!*s) uScherbakovDegree = 1;
			else if (*s == '^') uScherbakovDegree = fromStringToNum(s + 1);
		}
		else if (isdigit(*s))
		{
			char *s1 = s;
			while (s1 && isdigit(*s1)) s1++;
			if (!*s1) iScherbakovCoeff = fromStringToNum(s);
			else
			{
				char buf[100] = "", *b = buf, *s2 = s;
				while (s2 != s1) *b++ = *s2++;
				*b = 0;
				iScherbakovCoeff = fromStringToNum(buf);
				if (!*(s1 + 1)) uScherbakovDegree = 1;
				else if (*(s1 + 1) == '^') uScherbakovDegree = fromStringToNum(s1 + 2);
			}
		}
		if (!flag) iScherbakovCoeff = -iScherbakovCoeff;
	}
}

cScherbakovMonom cScherbakovMonom::operator-() const
{
	return cScherbakovMonom(-iScherbakovCoeff, uScherbakovDegree);
}

cScherbakovMonom cScherbakovMonom::operator+(const cScherbakovMonom& sum) const
{
	return cScherbakovMonom(iScherbakovCoeff + sum.getCoeff(), uScherbakovDegree);
}
cScherbakovMonom cScherbakovMonom::operator-(const cScherbakovMonom& sub) const
{
	return cScherbakovMonom(iScherbakovCoeff - sub.getCoeff(), uScherbakovDegree);
}

cScherbakovMonom cScherbakovMonom::operator*(const cScherbakovMonom& mul) const
{
	return cScherbakovMonom(iScherbakovCoeff * mul.getCoeff(), uScherbakovDegree + mul.getDegree());
}

cScherbakovMonom cScherbakovMonom::operator/(const cScherbakovMonom& div) const
{
	try
	{
		if (!div.getCoeff()) throw dividing_by_zero();
	}
	catch (const dividing_by_zero& exc) { std::cout << exc.what(); }
	if (uScherbakovDegree < div.getDegree()) return cScherbakovMonom();
	else return cScherbakovMonom(iScherbakovCoeff / div.getCoeff(), uScherbakovDegree - div.getDegree());
}

cScherbakovMonom cScherbakovMonom::operator%(const cScherbakovMonom& mod) const
{
	return *this - *this / mod * mod;
}

ostream& operator<<(ostream& stream, const cScherbakovMonom& m)
{
	if (!m.getCoeff()) return stream << '0';
	else if (abs(m.getCoeff()) != 1 || !m.getDegree()) stream << abs(m.getCoeff());
	if (m.getDegree()) stream << 'x';
	if (m.getDegree() != 1 && m.getDegree()) stream << '^' << m.getDegree();
	return stream;
}