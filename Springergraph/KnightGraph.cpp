#include "KnightGraph.h"
#include "Chessboard.h"
#include <iostream>



KnightGraph::KnightGraph(Chessboard& board) : m_board(board)
{
	fillGraph(board);
}

void KnightGraph::changeChessboard(Chessboard *board)
{
	// Graphen leeren
	std::list<Node*>::const_iterator iterator;
	while (!nodes.empty()) {
		iterator = nodes.begin();
		remove(*iterator);
	}
	// Graphen fuellen
	fillGraph(*board);
}

void KnightGraph::fillGraph(Chessboard &board)
{
	for (unsigned short height = 1; height < board.s_maxHeight + 1; height++) {
		for (char width = 'a'; width < board.s_maxWidth + 'a'; width++) {
			try {
				Field* tmp = board.getField(height, width);
				if (tmp == NULL) {
					throw InvalidNodeIdException("Field not found.");
				}
				addNode(new Field(*tmp));
			}
			catch (const InvalidNodeIdException& ex) {
				std::cout << "error while creating node: " << ex.getError() << endl;
			}
		}
	}
	for (unsigned short currentHeight = 1; currentHeight < board.s_maxHeight + 1; currentHeight++) {
		for (char currentWidth = 'a'; currentWidth < board.s_maxWidth + 'a'; currentWidth++) {
			short addHeight = 2;
			short addWidth = 1;
			for (short j = 0; j < 2; j++) { // Wechseln zwischen horizontaler und vertikaler Bewegung.
				for (short i = 0; i < 2; i++) { // Wechseln zwischen der Bewegung nach oben und unten.
					addHeight *= -1;
					for (short k = 0; k < 2; k++) { // Wechseln zwischen der Bewegung nach links und rechts.
						addWidth *= -1;
						short newHeight = currentHeight + addHeight;
						char newWidth = currentWidth + addWidth;
						if (board.positionAvailable(board.getField(newHeight, newWidth), white)) {
							try {
								Node* source = findNode(std::to_string(currentHeight) + currentWidth);
								Node* destination = findNode(std::to_string(newHeight) + newWidth);
								if (source == NULL || destination == NULL) {
									throw InvalidNodeIdException("Node not found");
								}
								addEdge(new Edge(*source, *destination));
							}
							catch (const InvalidNodeIdException&) {
								std::cout << "error while creating edge: " << currentHeight << currentWidth << " -> " << newHeight << newWidth << endl;
							}
						}
					}
				}
				addHeight = 1;
				addWidth = 2;
			}
		}
	}
}

deque<Edge*> KnightGraph::shortestPath()
{
	return findShortestPathDijkstra(*findNode(m_board.findKnight(white).getID()), *findNode(m_board.findKing(black).getID()));
}
