#ifndef EDGE_H
#define EDGE_H

#include "Node.h"


class Edge
{
public:

    Edge(Node& srcNode, Node& dstNode);

    Edge(const Edge& rOther);

    virtual ~Edge();

    bool isConnectedTo(const Node& rNode) const;

	Node& getSrcNode() { return srcNode; }
	Node& getDstNode() { return dstNode; }

	std::string toString() const;

	virtual double getWeight() { return 1; }


private:

	Node& srcNode;
	Node& dstNode;

};

#endif
