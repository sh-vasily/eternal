#include "cScherbakovNode.h"

class cScherbakovPolynom
{

	cScherbakovNode* first;

public:

	cScherbakovPolynom();
	cScherbakovPolynom(char* str);
	cScherbakovPolynom(int c, unsigned d);
	cScherbakovPolynom(const cScherbakovMonom& m);
	cScherbakovPolynom(const cScherbakovNode& n);
	cScherbakovPolynom(const cScherbakovPolynom& p);

	cScherbakovPolynom& operator=(const cScherbakovPolynom& p);

	cScherbakovNode* getFirst() const { return first; }

	void add(char* str);
	void add(int c = 0, unsigned d = 0);
	void add(const cScherbakovMonom& m);
	void add(const cScherbakovNode& n);

	cScherbakovPolynom operator-() const;

	cScherbakovPolynom operator+(const cScherbakovPolynom& sum) const;
	cScherbakovPolynom operator-(const cScherbakovPolynom& sub) const;
	cScherbakovPolynom operator*(const cScherbakovPolynom& mul) const;
	cScherbakovPolynom operator/(const cScherbakovPolynom& div) const;
	cScherbakovPolynom operator%(const cScherbakovPolynom& mod) const;

	friend ostream& operator<<(ostream& stream, const cScherbakovPolynom& p);
	friend istream& operator>>(istream& stream, cScherbakovPolynom& p);

	~cScherbakovPolynom();

};