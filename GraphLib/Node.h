#ifndef NODE_H
#define NODE_H

#include <string>
#include <list>


// forward-deklaration
class Edge;


class Node
{
public:


	Node();

	Node(std::string id) : id(id) { totalInstances++; }
	
	virtual ~Node() { }
	
	std::string getID() const { return id; }

    const std::list<Edge*>& getOutEdges() const { return outgoingEdges; }
    const std::list<Edge*>& getInEdges()  const { return incomingEdges; }

	void addOutEdge(Edge* out) { outgoingEdges.push_back(out); }
	void addInEdge(Edge* in) { incomingEdges.push_back(in); }

	void removeOutEdge(Edge* out) { outgoingEdges.remove(out); }
	void removeInEdge(Edge* in) { incomingEdges.remove(in); }


private:

	std::string id;

    std::list<Edge*> outgoingEdges;
    std::list<Edge*> incomingEdges;

	static int totalInstances;

};


#endif
