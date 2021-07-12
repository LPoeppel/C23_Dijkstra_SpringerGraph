#pragma once
#include <string>
using namespace std;
class InvalidNodeIdException
{
public:
	InvalidNodeIdException(string error) : error(error) {}
	virtual string getError() const { return error; }
	~InvalidNodeIdException() {}
private:
	const string error;
};
