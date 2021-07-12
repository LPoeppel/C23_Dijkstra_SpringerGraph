#include "Graph.h"
#include "InvalidNodeIdException.h"
#include <fstream>
#include <algorithm>
#include <limits>
#include <unordered_map>
#include <set>
#include <iostream>


//---------------------------------------------------------------------------------------------------------------------

Node* Graph::findNode(const std::string& id)
{
	for (Node* node : nodes) {
		if (node->getID() == id)
			return node;
	}
    return NULL;

    // - soll eine Node mit der gegebenen id in m_nodes suchen
    // - gibt den Pointer auf die Node zurück, wenn sie gefunden wurde.
    // - gibt NULL zurück, falls keine Node mit der id gefunden wurde.

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend ein paar Nodes im Graph suchen.
    // Prüfen Sie, ob die Node gefunden wurde und geben Sie die ID auf der Kommandozeile aus!
}


//---------------------------------------------------------------------------------------------------------------------

Node& Graph::addNode(Node* pNewNode)
{
	Node* existingNode = findNode(pNewNode->getID());
	if (existingNode == NULL) { // There is no node with the new nodes ID in the graph.
		nodes.push_back(pNewNode);
	} else if (existingNode != pNewNode) { // The new node is not existing in the graph, but its ID is already used.
		throw InvalidNodeIdException("\"" + pNewNode->getID() + "\"");
	}
	// If the node is already in the graph, the node is only returned.
	return *pNewNode;

    // Bitte diese Zeile entfernen, wenn Sie die Funktion implementieren:
    // return *new Node("");

    // Überprüfen Sie, ob schon ein Node mit der gegeben id im Graph vorhanden ist!
    // Falls ja:
    //  - Exception werfen
    // Falls nein:
    //  - die neue Node 'pNewNode' in m_nodes einfügen
    //  - Referenz auf die neue Node zurück geben

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes in main.cpp erstellen
    // Testen Sie mit der Funktion 'findNode', ob die hinzugefügten Nodes im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

Edge& Graph::addEdge(Edge* pNewEdge)
{
	Node* existingSrcNode = findNode(pNewEdge->getSrcNode().getID());
	// New node is added to the graph. If there is an issue with it, an exception is trown insted of adding to the graph.
	addNode(&(pNewEdge->getSrcNode()));
	try {
		addNode(&(pNewEdge->getDstNode()));
	}
	catch (InvalidNodeIdException ex) { // Issue with the destination node.
		if (existingSrcNode == NULL) { // If the source node was added to the graph before it must be removed.
			nodes.remove(&(pNewEdge->getSrcNode())); // Source node is just removed from the list. It should NOT be deleted here.
		}
		throw ex;
	}
	edges.push_back(pNewEdge);
	return *pNewEdge;

    // bitte diese Zeile entfernen, wenn Sie die Funktion implementieren:
    // return *new Edge(*new Node(), *new Node());

    // - die neue Edge 'pNewEdge' in m_edges einfügen
    // - Referenz auf die neue Edge zurück geben

	// - Testen Sie ob der Source- und Destination-Node von 'pNewEdge' schon im Graph vorhanden ist.
	// -> fügen Sie diese Nodes hinzu, falls nicht (nutzen Sie dafür Graph::addNode)

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // Testen Sie mit der Funktion 'findEdges', ob die hinzugefügten Edges im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

Graph::~Graph()
{
	std::list<Node*>::const_iterator iterator;
	while (!nodes.empty()) {
		iterator = nodes.begin();
		remove(*iterator);
	}

    // - soll alle Edges im Graph löschen (delete)
    // - soll alle Nodes im Graph löschen (delete)
}


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Node* rNode)
{
	std::list<Edge*>::const_iterator iterator;
	while (!rNode->getInEdges().empty()) {
		iterator = rNode->getInEdges().begin();
		remove(*iterator);
	}
	while (!rNode->getOutEdges().empty()) {
		iterator = rNode->getOutEdges().begin();
		remove(*iterator);
	}

	nodes.remove(rNode);
	delete rNode;

    // - alle Edges, die mit rNode verbunden sind, müssen entfernt werden!
	// - finden sie den Pointer mit der Adresse von 'rNode' in m_nodes.
    // 		- der Pointer auf rNode soll aus m_nodes entfernt werden!
    // 		- der Pointer auf rNode muss mit 'delete' freigegeben werden!

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend einzelne Nodes wieder löschen.
    // Testen Sie mit der Funktion 'findNode', ob die gelöschten Nodes noch im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Edge* rEdge)
{
	edges.remove(rEdge);
	delete rEdge;

    // - der Pointer auf rEdge muss aus m_edges entfernt werden!
    // - der Pointer auf rEdge muss mit 'delete' freigegeben werden!

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend einzelne Edges wieder löschen.
    // Testen Sie mit der Funktion 'findEdges', ob die gelöschten Edges noch im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

std::vector<Edge*> Graph::findEdges(const Node& srcNode, const Node& dstNode)
{
    std::vector<Edge*> tmp;
	for (Edge* edge : edges) {
		if (&(edge->getSrcNode()) == &srcNode && &(edge->getDstNode()) == &dstNode)
			tmp.push_back(edge);
	}
	return tmp;

    // - findet alle edges, mit srcNode als Source-Node und dstNode als Destination-Node.
    // - füge die Zeiger der Edges in den vector 'tmp' ein.


    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend ein paar Edges im Graph suchen.
    // Prüfen Sie, ob Edges gefunden wurden und geben Sie die gefunden Edges auf der Kommandozeile aus!
}

//---------------------------------------------------------------------------------------------------------------------

std::deque<Edge*> Graph::findShortestPathDijkstra(const Node& rSrcNode, const Node& rDstNode) {
	// Contains the distance to the source node about every node in the graph.
	std::unordered_map<const Node*, double> distance;
	// Contains the choosen path about every node in the graph.
	std::unordered_map<const Node*, Edge*> prevWay;
	// Contains unexplored Nodes
	std::set<const Node*> unexploredNodes;

	for (Node* n : nodes) {
		// For every node in the graph the distance is maximum and there is no previous node.
		distance[n] = DBL_MAX;
		prevWay[n] = NULL;
		// Adds every node in the graph to the unexplored nodes.
		unexploredNodes.emplace(n);
	}
	distance[&rSrcNode] = 0; // Distance of the start-node is 0.

	while (!unexploredNodes.empty()) {
		const Node* current = *unexploredNodes.begin(); // Currently visited node.
		// Search the shortest distance to the start of all unexplored nodes.
		double minDistance = distance[current];
		for (const Node* nextNode : unexploredNodes) {
			if (minDistance > distance[nextNode]) {
				current = nextNode;
				minDistance = distance[nextNode];
			}
		}
		if (current == &rDstNode)
			break; // Destination is reached.
		
		unexploredNodes.erase(current); // Node is now explored.
		
		// Visit every nearby node.
		for (Edge* e : current->getOutEdges()) {
			const Node* dstCurrent = &(e->getDstNode()); // Next node.
			if (unexploredNodes.find(dstCurrent) == unexploredNodes.end()) {
				continue; // If the next node is already explored, it is skipped.
			}
			// Set the distance of the next node if it is shorter.
			double newDistance = distance[current] + e->getWeight();
			double oldDistance = distance[dstCurrent];
			if (newDistance < oldDistance) {
				distance[dstCurrent] = newDistance;
				prevWay[dstCurrent] = e;
			}
		}
	}

	// Put the path in a deque to return it.
	std::deque<Edge*> tmp; 
	Edge* path = prevWay[&rDstNode]; // Start at destination.
	while (path != NULL) { // Source node has no previous path.
		tmp.push_front(path); 
		path = prevWay[&(path->getSrcNode())];
	}
	return tmp;

/*
Ein häufiges Anwendungsproblem für Graphen-Anwendungen besteht darin, 
den Pfad zwischen verschiedenen Nodes zu finden, die direkt oder indirekt über Edges miteinander verbunden sind.
Um den optimalsten Pfad(den mit den geringsten Kantengewichten) zu finden, gibt es den Dijkstra-Algorithmus!
Pseudocode (Quelle: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
>>>
function Dijkstra(Graph, source):

      create vertex set Q

      for each vertex v in Graph:             // Initialization
          dist[v] ← INFINITY                  // Unknown distance from source to v
          prev[v] ← UNDEFINED                 // Previous node in optimal path from source
          add v to Q                          // All nodes initially in Q (unvisited nodes)

      dist[source] ← 0                        // Distance from source to source

      while Q is not empty:
          u ← vertex in Q with min dist[u]    // Source node will be selected first
          remove u from Q

          for each neighbor v of u:           // where v is still in Q.
              alt ← dist[u] + length(u, v)
              if alt < dist[v]:               // A shorter path to v has been found
                  dist[v] ← alt
                  prev[v] ← u

      return dist[], prev[]
<<<

Betrachten Sie den Pseudocode und setzen Sie ihn in C++ um.
Sortieren Sie am Ende das Ergebnis in die richtige Reihenfolge um 
und geben sie die kürzeste Route zwischen rSrcNode und rDstNode als Liste von Edges zurück.

TEST:
Testen Sie diese Funktion, indem Sie einen Graph in main.cpp erstellen
und sich die kürzesteste Route zwischen 2 Nodes zurückgeben lassen.
*/

}




//---------------------------------------------------------------------------------------------------------------------

