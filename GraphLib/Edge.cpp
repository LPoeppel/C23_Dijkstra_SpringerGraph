#include "Edge.h"


//---------------------------------------------------------------------------------------------------------------------

Edge::Edge(Node& srcNode, Node& dstNode) : srcNode(srcNode), dstNode(dstNode)
{
	this->srcNode.addOutEdge(this);
	this->dstNode.addInEdge(this);

    // f�gt die Edge (this) in m_outgoingEdges des Source-Node ein.
    // f�gt die Edge (this) in m_incomingEdges des Destination-Node ein.

    // Hinweis: die Funktionen Node::getOutEdges() und Node::getInEdges() verwenden!

    // TEST:
    // Erstellen Sie in main.cpp eine Edge und pr�fen Sie, ob die Edge
    // korrekt in m_outgoingEdges bzw. m_incomingEdges eingef�gt wurde!
}


//---------------------------------------------------------------------------------------------------------------------

Edge::Edge(const Edge& rOther) : srcNode(rOther.srcNode), dstNode(rOther.dstNode)
{
	this->srcNode.addOutEdge(this);
	this->dstNode.addInEdge(this);

    // macht das Selbe wie 'Edge(Node& rSrc, Node& rDst)'
}


//---------------------------------------------------------------------------------------------------------------------

Edge::~Edge()
{
	srcNode.removeOutEdge(this);
	dstNode.removeInEdge(this);

    // - entfernt die Edge (this) aus m_outgoingEdges im Source-Node
    // - entfernt die Edge (this) aus m_incomingEdges im Destination-Node

    // TEST:
    // Erstellen Sie in main.cpp drei Edges, die jeweils den selben Source- und Destination-Node haben.
    // L�schen Sie eine Edge wieder!
    // Pr�fen Sie, ob die gel�schte Edge aus m_outgoingEdges bzw. m_incomingEdges entfernt wurde!

    // Hinweis: arbeiten Sie mit 'new' und 'delete'!
}


//---------------------------------------------------------------------------------------------------------------------

bool Edge::isConnectedTo(const Node& rNode) const
{
	return &rNode == &srcNode || &rNode == &dstNode;

    // - gibt true zur�ck, wenn rNode entweder m_rSrc oder m_rDst ist.
    // Hinweis: Adressen vergleichen, um zu gucken, ob es wirklich das selbe Objekt ist!
}


//---------------------------------------------------------------------------------------------------------------------

std::string Edge::toString() const
{
    std::string result;
    result = srcNode.getID() + " -> " + dstNode.getID();
    return result;
}


//---------------------------------------------------------------------------------------------------------------------
