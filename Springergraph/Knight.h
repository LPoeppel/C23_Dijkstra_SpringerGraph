#pragma once
#include "Piece.h"
#include "Field.h"

class Knight :	public Piece
{
public:
	Knight(Colour);
	Knight(Colour, int, char);
	~Knight();
	void move(Field);
	char draw() const;

private:
	static unsigned short s_counter;
};

