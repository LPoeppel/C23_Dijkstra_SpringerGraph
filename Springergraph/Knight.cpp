#include "Knight.h"

unsigned short Knight::s_counter = 0;


Knight::Knight(Colour colour) : Piece(colour) {
	m_id = this->s_counter;
	this->s_counter++;
}

Knight::Knight(Colour colour, int i, char c) : Piece(colour, i, c) {
	m_id = this->s_counter;
	this->s_counter++;
}

Knight::~Knight()
{
}

void Knight::move(Field target) {
	
}

char Knight::draw() const{
	if (getColour()) { return 'S'; }
	else { return 's'; }
}
