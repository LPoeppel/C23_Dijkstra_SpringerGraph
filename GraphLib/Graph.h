#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Edge.h"
#include <vector>
#include <deque>

class Graph
{

public:

	virtual ~Graph();


	Node& addNode(Node* pNewNode);
	
	Edge& addEdge(Edge* pNewEdge);

    void remove(Node* rNode);

    void remove(Edge* rEdge);


    const std::list<Node*>& getNodes() const { return nodes; }
    
    const std::list<Edge*>& getEdges() const { return edges; }

    Node* findNode(const std::string& id);

    std::vector<Edge*> findEdges(const Node& srcNode, const Node& dstNode);

	std::deque<Edge*> findShortestPathDijkstra(const Node& rSrcNode, const Node& rDstNode);


protected:

	std::list<Node*> nodes;
    std::list<Edge*> edges;

};


//---------------------------------------------------------------------------------------------------------------------

#endif
