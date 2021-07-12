#include "King.h"
#include "Knight.h"
#include "Pawn.h"

class Chessboard{
public:
	Chessboard();
	~Chessboard();

	void initialize(std::ifstream*);
	Field& findKnight(Colour) const;
	Field& findKing(Colour) const;
	Field* getField(unsigned short, char) const;
	std::string draw() const;
	void addPiece(Piece*);
	const static unsigned short s_maxHeight = 8;
	const static unsigned short s_maxWidth = 8;
	bool positionAvailable(Field*, Colour) const;

private:
	Field& findPiece(char id) const;
	Field* m_fields[s_maxHeight][s_maxWidth];
	std::list<Piece*> m_pieces;
};