#pragma once
#include "Graph.h"
#include "InvalidNodeIdException.h"
#include "NoPieceFoundException.h"

class Chessboard;

using namespace std;
class KnightGraph : public Graph
{
public:
	KnightGraph(Chessboard&);
	void changeChessboard(Chessboard*);
	deque<Edge*> shortestPath();
private:
	void fillGraph(Chessboard&);
	const Chessboard& m_board;
};

