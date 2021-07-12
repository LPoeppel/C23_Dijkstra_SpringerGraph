#include "Piece.h"

Piece::Piece(Colour c): m_colour(c){
}

Piece::Piece(Colour colour, int i, char c): m_colour(colour){
}

Piece::~Piece(){
}

Colour Piece::getColour() const{
	return m_colour;
}

Field* Piece::getField() const{
	return m_field;
}

void Piece::setField(Field& field) {
	m_field = &field;
}

std::string Piece::toString() const{
	std::stringstream output;
	output << "Peace " << draw() << " on field " << m_field->toString();
	return output.str();
}
