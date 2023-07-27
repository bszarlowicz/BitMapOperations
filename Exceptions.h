#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <exception>
#include <string>

using namespace std;

/*
*Wyjątki
*/
namespace MyExceptionErrors {

	class WrongValueError : public runtime_error
	{
	public:
		WrongValueError() : runtime_error("Error. Incorrect value") {}
		WrongValueError(std::string msg) : runtime_error(msg.c_str()) {}
	};

}

#endif
