#pragma once
#include <string>
class NoPieceFoundException
{
public:
	NoPieceFoundException() {}
	std::string getError() const {
		return "No piece found.";
	}

	~NoPieceFoundException() {}
};