#include "cScherbakovPolynom.h"

cScherbakovPolynom::cScherbakovPolynom() : first(nullptr) {  }

cScherbakovPolynom::cScherbakovPolynom(char* str) : first(nullptr)
{
	char *s = str, buf[100] = "", *b = buf;
	if (*s == '+' || *s == '-') *b++ = *s++;
	while (*s)
	{
		*b++ = *s++;
		if (!*s || *s == '+' || *s == '-')
		{
			*b = 0;
			b = buf;
			add(buf);
			if (*s) *b++ = *s++;
		}
	}
}

cScherbakovPolynom::cScherbakovPolynom(int c, unsigned d) : first(nullptr)
{
	if (c)
	{
		try
		{
			first = new cScherbakovNode(c, d);
		}
		catch (const bad_alloc& exc) { std::cout << exc.what(); }
	}
}

cScherbakovPolynom::cScherbakovPolynom(const cScherbakovMonom& m) : first(nullptr)
{
	if (m.getCoeff())
	{
		try
		{
			first = new cScherbakovNode(m);
		}
		catch (const bad_alloc& exc) { std::cout << exc.what(); }
	}
}

cScherbakovPolynom::cScherbakovPolynom(const cScherbakovNode& n) : first(nullptr)
{
	if (n.getCoeff())
	{
		try
		{
			first = new cScherbakovNode(n);
		}
		catch (const bad_alloc& exc) { std::cout << exc.what(); }
	}
}

cScherbakovPolynom::cScherbakovPolynom(const cScherbakovPolynom& p) : first(nullptr)
{
	if (p.getFirst())
	{
		try
		{
			first = new cScherbakovNode(*p.getFirst());
		}
		catch (const bad_alloc& exc) { std::cout << exc.what(); }
		cScherbakovNode* pPtr = p.getFirst();
		cScherbakovNode* tPtr = first;
		while (pPtr->getNext())
		{
			try
			{
				tPtr->setNext(new cScherbakovNode(*pPtr->getNext()));
			}
			catch (const bad_alloc& exc) { std::cout << exc.what(); }
			pPtr = pPtr->getNext();
			tPtr = tPtr->getNext();
		}
	}
}

cScherbakovPolynom& cScherbakovPolynom::operator=(const cScherbakovPolynom& p)
{
	if (first)
	{
		cScherbakovNode* runner1 = first;
		cScherbakovNode* runner2 = first->getNext();
		while (runner2)
		{
			delete runner1;
			runner1 = runner2;
			runner2 = runner2->getNext();
		}
		delete runner1;
	}
	first = nullptr;
	if (p.getFirst())
	{
		try
		{
			first = new cScherbakovNode(*p.getFirst());
		}
		catch (const bad_alloc& exc) { std::cout << exc.what(); }
		cScherbakovNode* pPtr = p.getFirst();
		cScherbakovNode* tPtr = first;
		while (pPtr->getNext())
		{
			try
			{
				tPtr->setNext(new cScherbakovNode(*pPtr->getNext()));
			}
			catch (const bad_alloc& exc) { std::cout << exc.what(); }
			pPtr = pPtr->getNext();
			tPtr = tPtr->getNext();
		}
	}
	return *this;
}

void cScherbakovPolynom::add(char* str)
{
	add(cScherbakovNode(str));
}

void cScherbakovPolynom::add(int c, unsigned d)
{
	add(cScherbakovNode(c, d));
}

void cScherbakovPolynom::add(const cScherbakovMonom& m)
{
	add(cScherbakovNode(m));
}

void cScherbakovPolynom::add(const cScherbakovNode& n)
{
	if (n.getCoeff())
	{
		if (!first)
		{
			try
			{
				first = new cScherbakovNode(n);
			}
			catch (const bad_alloc& exc) { std::cout << exc.what(); }
		}
		else
		{
			if (n.getDegree() > first->getDegree())
			{
				cScherbakovNode* newFirst = nullptr;
				try
				{
					newFirst = new cScherbakovNode(n);
				}
				catch (const bad_alloc& exc) { std::cout << exc.what(); }
				newFirst->setNext(first);
				first = newFirst;
			}
			else if (n.getDegree() == first->getDegree())
			{
				first->setCoeff(first->getCoeff() + n.getCoeff());
				if (!first->getCoeff())
				{
					cScherbakovNode* newFirst = first->getNext();
					delete first;
					first = newFirst;
				}
			}
			else
			{
				cScherbakovNode* runner = first;
				while (runner->getNext() && runner->getNext()->getDegree() > n.getDegree()) runner = runner->getNext();
				if (!runner->getNext())
				{
					cScherbakovNode* newLast = nullptr;
					try
					{
						newLast = new cScherbakovNode(n);
					}
					catch (const bad_alloc& exc) { std::cout << exc.what(); }
					runner->setNext(newLast);
				}
				else if (n.getDegree() > runner->getNext()->getDegree())
				{
					cScherbakovNode* tmp = runner->getNext();
					cScherbakovNode* elemToAdd = nullptr;
					try
					{
						elemToAdd = new cScherbakovNode(n);
					}
					catch (const bad_alloc& exc) { std::cout << exc.what(); }
					runner->setNext(elemToAdd);
					elemToAdd->setNext(tmp);
				}
				else if (n.getDegree() == runner->getNext()->getDegree())
				{
					runner->getNext()->setCoeff(runner->getNext()->getCoeff() + n.getCoeff());
					if (!runner->getNext()->getCoeff())
					{
						cScherbakovNode* tmp = runner->getNext()->getNext();
						delete runner->getNext();
						runner->setNext(tmp);
					}
				}
			}
		}
	}
}

cScherbakovPolynom cScherbakovPolynom::operator-() const
{
	cScherbakovPolynom result;
	cScherbakovNode* runner = first;
	while (runner)
	{
		result.add(-*runner);
		runner = runner->getNext();
	}
	return result;
}

cScherbakovPolynom cScherbakovPolynom::operator+(const cScherbakovPolynom& sum) const
{
	cScherbakovPolynom result = *this;
	cScherbakovNode* runner = sum.getFirst();
	while (runner)
	{
		result.add(*runner);
		runner = runner->getNext();
	}
	return result;
}

cScherbakovPolynom cScherbakovPolynom::operator-(const cScherbakovPolynom& sub) const
{
	cScherbakovPolynom result = *this;
	cScherbakovNode* runner = sub.getFirst();
	while (runner)
	{
		result.add(-*runner);
		runner = runner->getNext();
	}
	return result;
}

cScherbakovPolynom cScherbakovPolynom::operator*(const cScherbakovPolynom& mul) const
{
	cScherbakovPolynom result;
	cScherbakovNode* runnerThis = first;
	cScherbakovNode* runnerMul = mul.getFirst();
	while (runnerThis)
	{
		while (runnerMul)
		{
			result.add(*runnerThis * *runnerMul);
			runnerMul = runnerMul->getNext();
		}
		runnerMul = mul.getFirst();
		runnerThis = runnerThis->getNext();
	}
	return result;
}

cScherbakovPolynom cScherbakovPolynom::operator/(const cScherbakovPolynom& div) const
{
	if (first->getDegree() < div.getFirst()->getDegree()) return cScherbakovPolynom();
	else if (first->getDegree() == div.getFirst()->getDegree()) return cScherbakovPolynom(first->getCoeff() / div.getFirst()->getCoeff(), 0);
	else
	{
		cScherbakovPolynom result, maincScherbakovPolynom = *this;
		while (maincScherbakovPolynom.getFirst() && maincScherbakovPolynom.getFirst()->getDegree() >= div.getFirst()->getDegree())
		{
			cScherbakovNode n(maincScherbakovPolynom.getFirst()->getCoeff() / div.getFirst()->getCoeff(), maincScherbakovPolynom.getFirst()->getDegree() - div.getFirst()->getDegree());
			if (!n.getCoeff())
			{
				maincScherbakovPolynom.add(-*maincScherbakovPolynom.getFirst());
				if (!maincScherbakovPolynom.getFirst()) break;
			}
			else
			{
				result.add(n);
				maincScherbakovPolynom = maincScherbakovPolynom - cScherbakovPolynom(n) * div;
				if (maincScherbakovPolynom.getFirst()->getDegree() == n.getDegree() + div.getFirst()->getDegree()) maincScherbakovPolynom.add(-*maincScherbakovPolynom.getFirst());
			}
		}
		return result;
	}
}

cScherbakovPolynom cScherbakovPolynom::operator%(const cScherbakovPolynom& mod) const
{
	return *this - *this / mod * mod;
}

ostream& operator<<(ostream& stream, const cScherbakovPolynom& p)
{
	stream << '<';
	cScherbakovNode* runner = p.getFirst();
	if (!runner) stream << '0';
	else while (runner)
	{
		if (runner == p.getFirst())
		{
			if (!runner->getSign()) stream << '-';
			stream << *runner;
			if (runner->getNext()) stream << ' ';
		}
		else
		{
			stream << (runner->getSign() ? '+' : '-') << ' ' << *runner;
			if (runner->getNext()) stream << ' ';
		}
		runner = runner->getNext();
	}
	return stream << '>';
}

istream& operator>>(istream& stream, cScherbakovPolynom& p)
{
	static char buf[1000] = "";
	char* b = buf, c;
	while ((c = (char)stream.get()) != '>') *b++ = c;
	*b = 0;
	p = cScherbakovPolynom(buf);
	return stream;
}

cScherbakovPolynom::~cScherbakovPolynom()
{
	if (first)
	{
		cScherbakovNode* runner = first->getNext();
		while (runner)
		{
			delete first;
			first = runner;
			runner = runner->getNext();
		}
		delete first;
	}
}