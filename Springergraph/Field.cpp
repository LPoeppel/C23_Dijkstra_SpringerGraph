#include "Field.h"
#include "Piece.h"

Field::Field(unsigned short row, char coloumn) : Node(std::to_string(row) + coloumn)
{
	m_row = row;
	m_coloumn = coloumn;
	if (m_coloumn == 'a' || m_coloumn == 'c' || m_coloumn == 'e' || m_coloumn == 'g') {
		if (m_row % 2) { m_colour = white; }
		else if (!(m_row % 2)) { m_colour = black; }
	}
	else if (m_coloumn == 'b' || m_coloumn == 'd' || m_coloumn == 'f' || m_coloumn == 'h') {
		if (m_row % 2) { m_colour = black; }
		else if (!(m_row % 2)) { m_colour = white; }
	}
}


Field::~Field()
{
}

char Field::draw() const {
	if (m_piece == NULL) {
		if (m_colour == white) { return 'o'; }
		else if (m_colour == black) { return 'x'; }
	}
	return m_piece->draw();
}

std::string Field::toString() const
{
	std::stringstream output;
	output << "Feld " << m_row << m_coloumn << " (" << m_colour << ")";
	return output.str();
}

void Field::setPiece(Piece *piece) {
	m_piece = piece; 
	if (piece != NULL) {
		piece->setField(*this); 
	}

}


