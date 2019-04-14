#include <iostream>

using std::ostream;
using std::istream;
using std::exception;

class dividing_by_zero : public exception
{
	
public:

	const char* what() const { return "Dividing by zero!"; }

};