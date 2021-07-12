#pragma once
#include <sstream>
#include <iomanip>
#include "Colour.h"
#include "Field.h"

class Piece
{
public:

	Piece(Colour);
	Piece(Colour, int, char);
	virtual ~Piece();

	Field* getField() const;
	void setField(Field&);
	Colour getColour() const;
	std::string toString() const;

	virtual char draw() const = 0;

protected:
	const Colour m_colour;
	Field* m_field = NULL;
	unsigned short m_id;
	static unsigned short s_counter;
};

