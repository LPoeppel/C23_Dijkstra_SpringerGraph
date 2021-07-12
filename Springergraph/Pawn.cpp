#include "Pawn.h"

unsigned short Pawn::s_counter = 0;


Pawn::Pawn(Colour colour) : Piece(colour) {
	m_id = this->s_counter;
	this->s_counter++;
}

Pawn::Pawn(Colour colour, int i, char c) : Piece(colour, i, c) 
{
	m_id = this->s_counter;
	this->s_counter++;
}

Pawn::~Pawn()
{
}

char Pawn::draw() const{
	if (getColour()) { return 'B'; }
	else { return 'b'; } 
}