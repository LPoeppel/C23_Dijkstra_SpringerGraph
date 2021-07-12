#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	King(Colour);
	King(Colour, int, char);
	~King();
	char draw() const;
private:
	static unsigned short s_counter;
};