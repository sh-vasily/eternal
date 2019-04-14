#include "cScherbakovNode.h"

cScherbakovNode::cScherbakovNode(char* str) : next(nullptr)
{
	try
	{
		cScherbakovMonomPointer = new cScherbakovMonom(str);
	}
	catch (const bad_alloc& exc) { std::cout << exc.what(); }
}

cScherbakovNode::cScherbakovNode(int c, unsigned d) : next(nullptr)
{
	try
	{
		cScherbakovMonomPointer = new cScherbakovMonom(c, d);
	}
	catch (const bad_alloc& exc) { std::cout << exc.what(); }
}

cScherbakovNode::cScherbakovNode(const cScherbakovMonom& m) : next(nullptr)
{
	try
	{
		cScherbakovMonomPointer = new cScherbakovMonom(m);
	}
	catch (const bad_alloc& exc) { std::cout << exc.what(); }
}

cScherbakovNode::cScherbakovNode(const cScherbakovNode& n) : next(nullptr)
{
	try
	{
		cScherbakovMonomPointer = new cScherbakovMonom(*n.getcScherbakovMonomPointer());
	}
	catch (const bad_alloc& exc) { std::cout << exc.what(); }
}

cScherbakovNode& cScherbakovNode::operator=(const cScherbakovNode& n)
{
	setCoeff(n.getCoeff());
	setDegree(n.getDegree());
	return *this;
}

cScherbakovNode cScherbakovNode::operator-() const
{
	return cScherbakovNode(-*cScherbakovMonomPointer);
}

cScherbakovNode cScherbakovNode::operator+(const cScherbakovNode& sum) const
{
	return cScherbakovNode(*cScherbakovMonomPointer + *sum.getcScherbakovMonomPointer());
}

cScherbakovNode cScherbakovNode::operator-(const cScherbakovNode& sub) const
{
	return cScherbakovNode(*cScherbakovMonomPointer - *sub.getcScherbakovMonomPointer());
}

cScherbakovNode cScherbakovNode::operator*(const cScherbakovNode& mul) const
{
	return cScherbakovNode(*cScherbakovMonomPointer * *mul.getcScherbakovMonomPointer());
}

cScherbakovNode cScherbakovNode::operator/(const cScherbakovNode& div) const
{
	return cScherbakovNode(*cScherbakovMonomPointer / *div.getcScherbakovMonomPointer());
}

cScherbakovNode cScherbakovNode::operator%(const cScherbakovNode& mod) const
{
	return cScherbakovNode(*cScherbakovMonomPointer % *mod.getcScherbakovMonomPointer());
}

ostream& operator<<(ostream& stream, const cScherbakovNode& n)
{
	return stream << *n.getcScherbakovMonomPointer();
}

cScherbakovNode::~cScherbakovNode()
{
	delete cScherbakovMonomPointer;
}