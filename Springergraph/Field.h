#pragma once
#include <istream>
#include <fstream>
#include <sstream>
#include "Colour.h"
#include "Node.h"

class Piece;

class Field : public Node{
public:

	Field(unsigned short, char);
	virtual ~Field();

	char draw() const;
	std::string toString() const;
	void setPiece(Piece*);

	Piece* getPiece() const { return m_piece; }
	char getColoumn() const { return m_coloumn; }
	unsigned short getRow() const { return m_row; }
	enum Colour getColour() const { return m_colour; }


private:
	Piece* m_piece = NULL;
	unsigned short m_row;
	char m_coloumn;
	enum Colour m_colour;
};

