#ifndef SOCK_EXC_H
#define SOCK_EXC_H

#include <string>
#include <iostream>

class BaseException
{
protected:

	std::string text;
	int code = 0;

public:

	virtual std::string what() = 0;

};

//class PKCSExceptions : public BaseException {
//public:
//	PKCSExceptions()
//	{
//		text = "Error. PKCS Exception.";
//		code = 1;
//	}
//
//	PKCSExceptions(std::string _text) { text = _text; }
//
//	std::string what() { return text; }
//	int errcode() { return code; }
//};

class RetVal final : public BaseException {
public:

	RetVal(int RV)
	{
		text = "Return value is not 0 (return value = " + std::to_string(RV) + ")";
		code = 2;
	}

	std::string what() { return text; }
	int errcode() { return code; }
};

#endif