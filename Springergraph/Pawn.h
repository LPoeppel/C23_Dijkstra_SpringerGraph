#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(Colour);
	Pawn(Colour, int, char);
	~Pawn();
	char draw() const;
private:
	static unsigned short s_counter;

};

