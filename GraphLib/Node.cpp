#include "Node.h"

#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

// static initialization
int Node::totalInstances = 0;

Node::Node()
{
	totalInstances++;
	stringstream tmp;
	tmp << "Node_" << setw(4) << setfill('0') << totalInstances;
	id = tmp.str();
}