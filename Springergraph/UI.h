#include <fstream>
#include <iomanip>
#include <string>
#include <iostream>
#include <filesystem>
#include <map>
#include "NoPieceFoundException.h"
#include <deque>
#include "KnightGraph.h"


class Chessboard;

using namespace std;
namespace fs = std::filesystem;

class UI
{
	string current_file = "empty";


public:
	UI();
	~UI();

	char menu();
	unsigned int getUInt(unsigned int) const;
	unsigned int showFiles(map<int, string>&);
	void showShortestPath(KnightGraph*);
	void initalizeChessboard(Chessboard*);
	void showChessboard(Chessboard *board);
	bool checkInitalisation();
	void output(char);
	void writeFile(KnightGraph*);

};

