#include "cScherbakovMonom.h"

using std::bad_alloc;

class cScherbakovNode
{

	cScherbakovMonom* cScherbakovMonomPointer;
	cScherbakovNode* next;

public:

	cScherbakovNode(char* str);
	cScherbakovNode(int c = 0, unsigned d = 0);
	cScherbakovNode(const cScherbakovMonom& m);
	cScherbakovNode(const cScherbakovNode& n);

	cScherbakovNode& operator=(const cScherbakovNode& n);

	void setCoeff(int c = 0) { cScherbakovMonomPointer->setCoeff(c); }
	void setDegree(unsigned d = 0){ cScherbakovMonomPointer->setDegree(d); }

	int getCoeff() const { return cScherbakovMonomPointer->getCoeff(); }
	unsigned getDegree() const { return cScherbakovMonomPointer->getDegree(); }

	bool getSign() const { return cScherbakovMonomPointer->getSign(); }

	cScherbakovMonom* getcScherbakovMonomPointer() const { return cScherbakovMonomPointer; }

	void setNext(cScherbakovNode* cScherbakovNodePtr) { next = cScherbakovNodePtr; }

	cScherbakovNode* getNext() const { return next; }

	cScherbakovNode operator-() const;

	cScherbakovNode operator+(const cScherbakovNode& sum) const;
	cScherbakovNode operator-(const cScherbakovNode& sub) const;
	cScherbakovNode operator*(const cScherbakovNode& mul) const;
	cScherbakovNode operator/(const cScherbakovNode& div) const;
	cScherbakovNode operator%(const cScherbakovNode& mod) const;

	friend ostream& operator<<(ostream& stream, const cScherbakovNode& n);

	~cScherbakovNode();

};