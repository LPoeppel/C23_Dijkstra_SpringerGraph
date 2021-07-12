#include "King.h"

unsigned short King::s_counter = 0;

King::King(Colour colour) : Piece(colour){
	m_id = this->s_counter;
	this->s_counter++;
}

King::King(Colour colour, int i, char c) : Piece(colour, i, c){
	m_id = this->s_counter;
	this->s_counter++;
}

King::~King()
{
}

char King::draw() const {
	if (getColour() == black) { return 'K'; }
	else { return 'k'; }
}
