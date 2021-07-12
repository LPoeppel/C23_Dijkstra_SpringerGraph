#include <iostream>
#include <string>
#include "UI.h"
#include "Chessboard.h"
#include "KnightGraph.h"

// Project Springergraph Gruppe : Frank Schuetze s0549557  ; Lukas Poeppel ; Pascal Blesin


int main(int argc, char *argv[])
{
	char auswahl = 0;
	UI userinterface = UI();
	Chessboard board = Chessboard();
	KnightGraph graph = KnightGraph(board);

	do {
		auswahl = userinterface.menu();
		switch (auswahl) {
		case'1':
			userinterface.initalizeChessboard(&board);
			graph.changeChessboard(&board);
			break;
		case'2':
			userinterface.showChessboard(&board);
			break;
		case'3':
			userinterface.output('3');
			userinterface.showShortestPath(&graph);
			break;
		case'4':
			userinterface.writeFile(&graph);
			break;
		case'5':
			userinterface.output('5');
			break;
		default:
			userinterface.output('6');
		}
	} while (auswahl != '5');

	return 0;
}

