#include "UI.h"
#include "Chessboard.h"

char UI::menu()
{
	char auswahl;

	cout << "USERINTERFACE" << "\n\n"
		<< "| " << "1" << " | " << setw(36) << left << "Initialize Chessboard" << "| " << "\n"
		<< "| " << "2" << " | " << setw(36) << left << "Show Chessboard" << "| " << "\n"
		<< "| " << "3" << " | " << setw(36) << left << "Show shortest path" << "| " << "\n"
		<< "| " << "4" << " | " << setw(36) << left << "Write shortest path to file" << "| " << "\n"
		<< "| " << "5" << " | " << setw(36) << left << "Exit" << "| " << endl;


	cout << "\nSelect : " << flush;
	cin >> auswahl;
	

	return auswahl;
}


unsigned int UI::getUInt(unsigned int max) const {
	unsigned int i;
	while (!(cin >> i) || i <= 0 || i > max) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Wrong input ! Please select a number beetween 1 and " << max << endl;
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	return i;
}

unsigned int UI::showFiles(map<int, string>& files)
{
	// c++ 17 standart
	filesystem::path p = "files/";
	unsigned int i = 0;
	string file;


	cout << "\nFiles :\n" << endl;


	for (const auto & entry : fs::directory_iterator(p))
	{
		i++;
		cout << "| " << i << " | " << setw(36) << left << entry.path().filename() << "| " << endl; // display files
		fs::path path = entry.path().filename();
		file = path.u8string(); // filename to string
		files[i] = file; // into map
	
		
	}
	if (i == 0)
	{
		cout << "No files found." << endl;
	}

	   
	return i;
}




void UI::initalizeChessboard(Chessboard *board)
{
	map<int, string> filenames;
	filesystem::path p = "files/";
	unsigned int auswahl;
	unsigned int anzahl;
	ifstream file;
	
	anzahl = showFiles(filenames);
	cout << "\nSelect file: ";
	auswahl = getUInt(anzahl);

	file.open(p / filenames[auswahl]);
		board->initialize(&file);

	cout << "Initalisation succsessfully done.\n" << endl;
	current_file = filenames[auswahl];
	file.close();
}

void UI::showChessboard(Chessboard *board)
{
	cout << "Current Chessboard :\n" << endl;
	cout << board->draw();
	cout << "\n\nKeys :" << endl;

	cout << "| o | " << " White empty field " << endl;
	cout << "| x | " << " Black empty field " << endl;
	cout << "| s | " << " White Knight " << endl;
	cout << "| S | " << " Black Knight " << endl;
	cout << "| b | " << " White Pawn " << endl;
	cout << "| B | " << " Black Pawn " << endl;
	cout << "| k | " << " White King " << endl;
	cout << "| K | " << " Black King" << "\n" <<  endl;
	   	 
}

bool UI::checkInitalisation()
{
	if (current_file == "empty")
	{
		return false;
	}
	
	return true;
}

void UI::output(char auswahl)
{
	
	if (auswahl == '3')
	{
		
	}
	else if (auswahl == '5')
	{
		cout << "Exit" << endl;
	}
	else if (auswahl == '6')
	{	
		cout << "Invalid input\n" << endl;
	}
}

void UI::writeFile(KnightGraph* graph)
{
	try 
	{
		
		
		if (!checkInitalisation())
		{
			throw "Please initialize Cheesboard first!\n";
		}

		deque<Edge*> shotestpath = graph->shortestPath();
		deque<Edge*>::iterator ItEdge;
		stringstream shortestpathOutput;
		Edge* tempedge;
		unsigned int counter = 0;
		
		for (ItEdge = shotestpath.begin(); ItEdge != shotestpath.end(); ItEdge++) //shortestPathToStringStream
		{
			counter++; 
			tempedge = *ItEdge;
			shortestpathOutput << tempedge->toString();
			shortestpathOutput << "\n";

		}
		if (counter == 0)
		{
			shortestpathOutput << "No possble path found.";
		}
		else
		{
			shortestpathOutput << "\n" << counter << " turns to reach to King." << endl;
		}

		stringstream outputfilename;
		
		outputfilename << "OutputFiles/ShortestPath_" << current_file;	

		//write into file
		ofstream write; 
		write.open(outputfilename.str(), ios::trunc); //Inhalt wird jedesmal ueberschrieben.
		write << shortestpathOutput.str();
		write.close();


		cout << "Shortest path for " << '"' << current_file << '"' << " successfully stored into : " << '"' << outputfilename.str() << '"' <<  "\n" << endl;


		
	}
		catch (const char* error)
		{
			cout << "Expetion: " << error << endl;
		}

}



void UI::showShortestPath(KnightGraph *graph)
{
	try
	{
		deque<Edge*> path = graph->shortestPath();

		if (path.empty()) {
			cout << "No path found. Please initalize new file.\n" << endl;
		}
		else {
			cout << "Shortest path for " << current_file << ":\n" << endl;
			double distance = 0;
			for (Edge* e : path)
			{
				cout << e->toString() << endl;
				distance += e->getWeight();
			}
			cout << "\n" << distance << " turns to reach to King.\n" << endl;
		}


		
	}
	catch(const char* error) {
			cout << error << endl;
		}
	catch (NoPieceFoundException ex)
	{
		cout << ex.getError() << endl;
	}

}


UI::UI()
{
}


UI::~UI()
{
}
