#include "Chessboard.h"
#include "NoPieceFoundException.h"
#include <iostream> //initialize exception

Chessboard::Chessboard(){
	for (int i = 0; i < s_maxHeight; i++) {
		for (int j = 0; j < s_maxHeight; j++) {
			m_fields[i][j] = new Field(i + 1, 'a' + j);
		}
	}
}


Chessboard::~Chessboard(){
	for (int i = 0; i < s_maxHeight; i++) {
		for (int k = 0; k < s_maxWidth; k++) {
			delete m_fields[i][k];
		}
	}
	for (Piece* p : m_pieces) {
		delete p;
	}
	m_pieces.clear();
}


Field& Chessboard::findKnight(Colour col) const {
	char id = 's';
	if (col == black) {
		id += 'A' - 'a';
	}
	return findPiece(id);
}

Field& Chessboard::findKing(Colour col) const{
	char id = 'k';
	if (col == black) {
		id += 'A' - 'a';
	}
	return findPiece(id);
}

Field& Chessboard::findPiece(char id) const {
	for (int i = 0; i < s_maxHeight; i++) {
		for (int j = 0; j < s_maxWidth; j++) {
			if (m_fields[i][j]->getPiece() != NULL && m_fields[i][j]->getPiece()->draw() == id)
				return *m_fields[i][j];
		}
	}
	throw NoPieceFoundException();
}

void Chessboard::initialize(std::ifstream *file) {
	//entfernt alle evtl. Figuren vom Schachbrett
	Piece* ptr = NULL;
	for (int i = 0; i < s_maxHeight; i++) {
		for (int k = 0; k < s_maxWidth; k++) {
			m_fields[i][k]->setPiece(ptr);
		}
	}

	std::string s;
	std::getline(*file, s);
	char info[3];
	unsigned short i = 0;
	for (char& c : s) {
		if (c == ',' || c == ' ') {
			if (i != 0) {
				std::cout << "loading failure: failed reading file" << std::endl;
				break;
			}
			continue;
		}

		info[i++] = c;
		if (i == 3) {
			if (0 > info[1] - 'a' || info[1] - 'a' >= s_maxWidth || 0 > info[2] - '1' || info[2] - '1' >= s_maxHeight) {
				std::cout << "loading failure: piece position out of range" << std::endl;
				break;
			}
			switch (info[0]) {
			case 's': ptr = new Knight(white, (int)info[2], (char)info[1]);
				break;
			case 'S': ptr = new Knight(black, (int)info[2], (char)info[1]);
				break;
			case 'k': ptr = new King(white, (int)info[2], (char)info[1]);
				break;
			case 'K': ptr = new King(black, (int)info[2], (char)info[1]);
				break;
			case 'b': ptr = new Pawn(white, (int)info[2], (char)info[1]);
				break;
			case 'B': ptr = new Pawn(black, (int)info[2], (char)info[1]);
				break;
			}
			m_fields[std::abs(info[2] - '8')][info[1] - 'a']->setPiece(ptr);
			addPiece(ptr);
			i = 0;
		}
	}
}

Field* Chessboard::getField(unsigned short number, char character) const {
	unsigned short charIndex = character - 'a';
	unsigned short numIndex = number - 1;
	if (0 <= numIndex && numIndex < s_maxHeight && 0 <= charIndex && charIndex < s_maxWidth) {
		return m_fields[numIndex][charIndex];
	}
	return NULL;
}

std::string Chessboard::draw() const {
	//Show Chessboard Row Number
	unsigned int edgecounter = s_maxHeight;
	std::stringstream board;
	for (int i = 0; i < s_maxHeight; i++) {
		board << edgecounter << " |  ";		// left edge of field
		edgecounter--;
		for (int j = 0; j < s_maxWidth; j++) {
			board << m_fields[i][j]->draw();
			board << ' ';
		}
		board << std::endl;
	}

	// Show Chessboard Coloumn Letter
	char key = 'A';
	board << "    ";
	for (int j = 0; j < s_maxWidth; j++){
		board << "__";
	}
	board << "_\n" << "    |";
	for (int j = 0; j < s_maxWidth; j++){
		board << key << "|";
		key++;
	}
	return board.str();
}

void Chessboard::addPiece(Piece* piece) {
	m_pieces.push_back(piece);
}

bool Chessboard::positionAvailable(Field* f, Colour currentColour) const {
	return f != NULL && (f->getPiece() == NULL || f->getPiece()->getColour() != currentColour);
}
