#include "exceptions.h"

// '+' = true
// '-' = false

int fromStringToInt(char*);

class cScherbakovMonom
{

	int iScherbakovCoeff;
	unsigned uScherbakovDegree;

public:

	cScherbakovMonom(int c = 0, unsigned d = 0) : iScherbakovCoeff(c), uScherbakovDegree(c ? d : 0) {  }
	cScherbakovMonom(char* str);
	
	void setCoeff(int c = 0) { iScherbakovCoeff = c; }
	void setDegree(unsigned d = 0) { uScherbakovDegree = d; }

	int getCoeff() const { return iScherbakovCoeff; }
	unsigned getDegree() const { return uScherbakovDegree; }
	
	bool getSign() const { return iScherbakovCoeff >= 0; }

	cScherbakovMonom operator-() const;

	cScherbakovMonom operator+(const cScherbakovMonom& sum) const;
	cScherbakovMonom operator-(const cScherbakovMonom& sub) const;
	cScherbakovMonom operator*(const cScherbakovMonom& mul) const;
	cScherbakovMonom operator/(const cScherbakovMonom& div) const;
	cScherbakovMonom operator%(const cScherbakovMonom& mod) const;
	
	friend ostream& operator<<(ostream& stream, const cScherbakovMonom& m);

};